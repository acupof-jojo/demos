Overview: Recreate the malloc and free function in C

Language: C

Main function file: mem_functions.c
Other important function files:
mem.h, mem_init.c

Test files:
all driver_alloc and driver_free files

Functions:
int Is_Free(BLOCK_HEADER *ptr): 
Checks whether or not the block passed in is free or not
Returns 0 if allocated, 1 if free

void Set_Free(BLOCK_HEADER *ptr):
Sets the block passed in to free

void Set_Allocated(BLOCK_HEADER *ptr):
Sets the block passed in to allocated

BLOCK_HEADER * Get_Next_Header(BLOCK_HEADER *ptr):
Returns the pointer to the next header after the block passed in

int Get_Padding(BLOCK_HEADER *ptr):
Returns the padding of the block passed in

int * Get_User_Pointer(BLOCK_HEADER *ptr):
Returns pointer to the user pointer

void* Mem_Alloc(int size):
MAIN FUNCTION
Allocate space in the heap
If a large enough free block is free, allocate the specified space in the heap, otherwise return null
Return a pointer to the payload if the space is successfully allocated

int Mem_Free(void *ptr):
MAIN FUNCTION
Free space in the heap
Return -1 if the input ptr was invalid, Return 0 if the specified pointer was freed
