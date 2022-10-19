//Johanna Mejias
//PROJ 4
//CS354
#include "mem.h"                      
extern BLOCK_HEADER* first_header;

//prints out block data
/*void Print_Block_Data(BLOCK_HEADER *ptr){
    //int block_size = 8 + ptr->payload + Get_Padding(*ptr);
    printf("Block_Size: %d\n", block_size);
    int alloc_bit = ptr->size_alloc % 2;
    printf("alloc_bit: %d\n", alloc_bit);
    printf("size_alloc: %d\n", ptr->size_alloc);
    printf("payload: %d\n", ptr->payload);
}*/

//return 0 if allocated, 1 if free
int Is_Free(BLOCK_HEADER *ptr){
    if(ptr->size_alloc % 2){
        return 0;
    }
    return 1;
}

//sets block to free
void Set_Free(BLOCK_HEADER *ptr){
    if(ptr->size_alloc % 2){
         ptr->size_alloc--;
         ptr->payload = ptr->size_alloc - 8;
         return;
    } else{
         return;
    }

}

//sets block to allocated
void Set_Allocated(BLOCK_HEADER *ptr){
    if(ptr->size_alloc % 2){
         return;
    } else{
        ptr->size_alloc++;
        return;
    }
}

//returns pointer to next header
BLOCK_HEADER * Get_Next_Header(BLOCK_HEADER *ptr){
    BLOCK_HEADER *next = (BLOCK_HEADER *)((unsigned long)ptr + (unsigned long)(ptr->size_alloc & 0xFFFFFFFE));
    return next;
}

//returns padding of block
int Get_Padding(BLOCK_HEADER *ptr){
    int padding = (ptr->size_alloc & 0xFFFFFFFE) - 8 - ptr->payload;
    //printf("\n size_alloc: %d, payload: %d", ptr->size_alloc , ptr->payload);
    //printf("pad: %d", padding);
    return padding;
}

//return pointer to user pointer
int * Get_User_Pointer(BLOCK_HEADER *ptr){
    return (void *)((unsigned long)ptr+8);
}

// return a pointer to the payload
// if a large enough free block isn't available, return NULL
void* Mem_Alloc(int size){
    // find a free block that's big enough
    
    BLOCK_HEADER *curr = first_header;
    
    while(1){
        if(curr->payload >= size && Is_Free(curr)){
            break;
        }
        curr = Get_Next_Header(curr);
        // return NULL if we didn't find a block
        if(curr->size_alloc == 1){ //last block has aloc size of 1
            return NULL;
        }
    }
    
    //printf("\nCURR ADDR: %p\n", curr);
    // allocate the block
    curr->payload = size;


    // split if necessary (if padding size is greater than or equal to 16 split the block)
    //printf("CURR: %p", curr);
    //printf("Get_Padding: %d", Get_Padding(curr));
    if(Get_Padding(curr) >= 16){
        //split here
        int free = Get_Padding(curr);
        curr->size_alloc = 0;
        while((curr->size_alloc + 8 + size) % 16){
            curr->size_alloc++;
        }
        BLOCK_HEADER *new_header = (BLOCK_HEADER *)(unsigned long)((unsigned long)curr + (unsigned long)(curr->size_alloc + size + 8));
        //printf("\naddr: %p", new_header);
        //printf("\nFREE22: %d", free);
        new_header->size_alloc = free - curr->size_alloc;
        new_header->payload = free - curr->size_alloc - 8;
        //printf("New Header ADDR: %p\n", new_header);
    }

    
    //pointer to new payload
    curr->size_alloc += (8 + size);
    Set_Allocated(curr); //allocate
    int * user = (void *)curr + (unsigned long)8;//user pointer

    return user;
}


// return 0 on success
// return -1 if the input ptr was invalid
int Mem_Free(void *ptr){
    // traverse the list and check all pointers to find the correct block 
    // if you reach the end of the list without finding it return -1
    BLOCK_HEADER *curr = first_header;
    BLOCK_HEADER *prev = curr; //previous block
    while(ptr != Get_User_Pointer(curr)){  //find ptr in question
        prev = curr;
        curr = Get_Next_Header(curr);
        if(curr->size_alloc == 1){
            return -1;
        }
    }
    BLOCK_HEADER *next = Get_Next_Header(curr); //next block
    
    Set_Free(curr);// free the block 
    // coalesce adjacent free blocks
    if(Is_Free(next)){ //block after
        curr->size_alloc += next->size_alloc;
        curr->payload += (next->payload + 8);
    }
    if(Is_Free(prev) && prev != curr){ //block before
        prev->size_alloc += curr->size_alloc;
        prev->payload += (curr->payload + 8);
        //Set_Free(prev);
    }

    return 0;
}

