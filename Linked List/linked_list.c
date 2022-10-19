//Johanna Mejias
//Project 3
// do not include other libraries
#include <stdio.h>
#include <stdlib.h>

// ***************************************
// *** struct definitions ****************
// *** do not change these ***************
// ***************************************
typedef struct NODE {int data; struct NODE* next;} NODE; // nodes of the linked list
typedef struct LINKED_LIST {struct NODE *head;} LINKED_LIST; // struct to act as the head of the list


// ***************************************
// *** provided functions  ****************
// ***************************************

// this function returns a LINKED_LIST struct to
// act as the head of the linked list.
// do not change this function
LINKED_LIST Create_List(void) {LINKED_LIST list = {NULL}; return list;}

// call this function to verify malloc worked when you create new nodes
void Verify_Malloc(NODE *node) {if (node == NULL) {printf("Malloc Failed\n"); exit(1);} return;}

// do not change this function
// this function prints out all of the nodes in the linked list
void Print_List(FILE *out, LINKED_LIST list) {
    if (list.head == NULL) {printf("\n"); return;} //empty list
    NODE *current = list.head;
    while (current->next != NULL) {
        fprintf(out, "%d -> ",current->data);
        current = current->next;
    }
    fprintf(out, "%d\n",current->data);
    return;
}

// ******************************************************
// *** Complete the following functions  ****************
// ******************************************************

// this function returns the number 
// of elements in the linked list
int Size(LINKED_LIST list){
    int count = 0;
    struct NODE* current = list.head;
    while(current != NULL){
        count++;
        current = current->next;
    }
    return count;
}
// this function adds an element to
// the front of the list
void Push_Front(LINKED_LIST *list, int data){
    //create NODE
    struct NODE *new_node = malloc(sizeof(NODE));
    new_node->data = data;

    //fix pointers
    new_node->next = list->head;
    list->head = new_node;
    return;
}

// this function adds an element 
// to the end of the linked list 
void Push_Back(LINKED_LIST *list, int data) {

    if(list->head == NULL){ //list is empty
        Push_Front(list, data);
        return;
    }

    //find the last NODE
    struct NODE *current = list->head;
    while(current->next != NULL){
        current = current->next;
    }
    struct NODE *new_node = malloc(sizeof(NODE));
    new_node->data = data;

    //reset pointers
    new_node->next = NULL;
    current->next = new_node;

    return;
}


// if the list is not empty
// the value of the first element of the list is returned by reference in the parameter data
// the first element of the list is deleted
// returns 0 if the list is empty otherwise returns 1
// remember to free the deleted node
int Pop_Front(LINKED_LIST *list, int *data) {
    if(list->head == NULL){
        return 0;
    }
    *data = list->head->data;
    NODE *temp = list->head;
    list->head = list->head->next;
    free(temp);
    temp = NULL;
    return 1;
}


// if the list is not empty
// the value of the last element of the list is returned by reference in the parameter data
// the last element of the list is deleted
// returns 0 if the list is empty otherwise returns 1
// remember to free the deleted node
int Pop_Back(LINKED_LIST *list, int *data) {
    if(list->head == NULL){
      return 0;  
    }
    

    //only one node - change head
    if(list->head->next == NULL){  
        free(list->head);
        list->head = NULL;
        return 1;
    }

    //two or more nodes - find the next to last NODE
    NODE *current = list->head;
    while(current->next != NULL){
        if(current->next->next == NULL){
            *data = current->next->data;
            current->next = NULL;
        } else{
            current = current->next;
        }
        
    }
    free(current->next);

   return 1;
}

// this function returns the number 
// of times that the value of the parameter 
// data appears in the list
int Count_If(LINKED_LIST list, int data) {

    int count = 0;
    NODE *current = list.head;
    while(current != NULL ){
        if(current->data == data){
            count++;
        }
        current = current->next;
    }
    return count;

}

// delete the first node containing the data value
// return 1 if something was deleted otherwise 0
// remember to free the deleted node
int Delete(LINKED_LIST *list, int data) {
    //empty
    if(list->head == NULL){// list is empty
        return 0;
    }

    //first node / only node
    if(list->head->data == data){
        //printf("asdfasdf %d\n", (*head)->data); || test print
        //copy head pointer - to the node to be deleted
        NODE *del = list->head;
        list->head = list->head->next;
        free(del);
        return 1;
    }

    //search for node
    NODE *temp = list->head;
    NODE *prev =NULL;
    while(temp != NULL && temp->data != data){
        prev = temp;
        temp = temp->next;
    }

    //if key was not in list
    if(temp == NULL){
        return 0;
    }

    prev->next = temp->next;
    free(temp);

    return 1;
}

// return 1 if the list is empty otherwise returns 0
int Is_Empty(LINKED_LIST list) {
    if(list.head != NULL){
        return 0;
    }
    return 1;
}

// delete all elements of the list
// remember to free the nodes
void Clear(LINKED_LIST *list) {
    while(list->head != NULL){
        NODE *temp = list->head;
        list->head = list->head->next;
        free(temp);
    }

    return;
}


// if an element appears in the list 
// retain the first occurance but
// remove all other nodes with the same 
// data value
void Remove_Duplicates(LINKED_LIST *list) {
    //if list is empty
    if(list->head == NULL){
        return;
    }

    NODE *current = list->head;
    NODE *loc = NULL; //node after current
    NODE *temp = NULL; //node before loc

    while(current != NULL){
        temp = current;
        loc = current->next;
        while(loc != NULL){
            if(current->data == loc->data){
                temp->next = loc->next;
            } else{
                temp = loc;
            }
            loc = loc->next;
        }
        current = current->next;
    }

    return;
}

// modify main to completely test your functions 

//*
int main() {
    // create a linked list
    printf("creating linked list\n");
    LINKED_LIST list = Create_List();
   
    // add some data (hardcoded for testing)
    printf("hardcoding some data\n");
    NODE *first  = malloc(sizeof(NODE)); Verify_Malloc(first);
    NODE *second = malloc(sizeof(NODE)); Verify_Malloc(second);
    first->data  = 1;
    second->data = 2;
    list.head = first;
    first->next = second;
    second->next = NULL;

    // print the list
    printf("Testing Print_List\n");
    Print_List(stdout, list);
    
    // write a better test for Size
    printf("Testing Size\n");
    printf("size = %d\n",Size(list));
    
    // write a better test for Push_Front
    printf("Testing Push_Front\n");
    Push_Front(&list, 0);
    Print_List(stdout, list);
    
    // write a better test for Push_Back
    printf("Testing Push_Back\n");
    Push_Back(&list, 3);
    Print_List(stdout, list);
    
    // write a better test for Pop_Front
    printf("Testing Pop_Front\n");
    {
        int x; 
        int not_empty = Pop_Front(&list, &x);
        if (not_empty) {
            printf("Element popped was %d\n",x);
            Print_List(stdout,list);
            printf("size = %d\n",Size(list));
        }
        else 
            printf("List was empty\n");
    }
    
    // write a better test for Pop_Back
    printf("Testing Pop_Back\n");
    {
        int x; 
        int not_empty = Pop_Back(&list, &x);
        if (not_empty) {
            printf("Element popped was %d\n",x);
            Print_List(stdout,list);
            printf("size = %d\n",Size(list));
        }
        else 
            printf("List was empty\n");
    }
    
    // write a beter test for Count_If
    Push_Front(&list, 5);
    Push_Front(&list, 5);
    Print_List(stdout, list);
    printf("5 count = %d\n",Count_If(list, 5));
    
    // write a test for Delete 
    printf("Testing Delete\n");
    Print_List(stdout, list);
    Delete(&list, 1); 
    Print_List(stdout, list);

    // write a better test for Is_Empty
    printf("Testing Is_Empty\n");
    if (Is_Empty(list)) printf("List is Empty\n"); else printf("List is not empty\n");
    
    // write a better test for Clear
    Clear(&list);
    //Print_List(stdout, list);
    if (Is_Empty(list)) printf("List is Empty\n"); else printf("List is not empty\n");

    // write a better test for Remove_Duplicates
    Push_Back(&list, 1);
    Push_Back(&list, 1);
    Push_Back(&list, 1);
    Push_Back(&list, 2);
    Push_Back(&list, 2);
    Push_Back(&list, 3);
    Push_Back(&list, 3);
    Push_Back(&list, 3);
    Remove_Duplicates(&list);
    Print_List(stdout, list);
    return 0;
    
}
//*/

/*
// modify main to completely test your functions 
int main() {
    // Clearing screen but keeping scrollback buffer
    system("clear -x");

    // create a linked list
    printf("Creating linked list\n");
    LINKED_LIST list = Create_List();
   
    // add some data (hardcoded for testing)
    printf("Hardcoding some data\n");
    NODE *first  = malloc(sizeof(NODE)); Verify_Malloc(first);
    NODE *second = malloc(sizeof(NODE)); Verify_Malloc(second);
    first->data  = 1;
    second->data = 2;
    list.head = first;
    first->next = second;
    second->next = NULL;

    // Freeing memory
    free(first);
    free(second);

    // print the list
    printf("\nTesting Print_List\n");
    Print_List(stdout, list);

    // write a better test for Size
    printf("\nTesting Size\n");
    printf("size = %d\n",Size(list));
    printf("Testing empty list\n");
    LINKED_LIST list2 = Create_List();
    printf("size = %d\n", Size(list2));

    // write a better test for Push_Front
    printf("\nTesting Push_Front\n");
    Push_Front(&list, 0);
    Print_List(stdout, list);
    printf("Testing empty list\n");
    Push_Front(&list2, 3);
    Push_Front(&list2, 2);
    Push_Front(&list2, 1);
    Print_List(stdout, list2);
    
    // write a better test for Push_Back
    printf("\nTesting Push_Back\n");
    Push_Back(&list, 3);
    Print_List(stdout, list);
    printf("Testing empty list\n");
    LINKED_LIST list3 = Create_List();
    Push_Back(&list3, 1);
    Push_Back(&list3, 2);
    Push_Back(&list3, 3);
    Print_List(stdout, list3);

    // write a better test for Pop_Front
    printf("\nTesting Pop_Front\n");
    {
        int x; 
        int not_empty = Pop_Front(&list, &x);
        if (not_empty) {
            printf("Element popped was %d\n",x);
            Print_List(stdout,list);
            printf("size = %d\n",Size(list));
        }
        else 
            printf("List was empty\n");
    }
    printf("Testing empty list\n");
    LINKED_LIST list4 = Create_List();
    {
        int x; 
        int not_empty = Pop_Front(&list4, &x);
        if (not_empty) {
            printf("Element popped was %d\n",x);
            Print_List(stdout,list);
            printf("size = %d\n",Size(list));
        }
        else 
            printf("List was empty\n");
    }


    //test for Pop_Back
    printf("\nTesting Pop_Back\n");
    {
        int x; 
        int not_empty = Pop_Back(&list, &x);
        if (not_empty) {
            printf("Element popped was %d\n",x);
            Print_List(stdout,list);
            printf("size = %d\n",Size(list));
        }
        else 
            printf("List was empty\n");
    }
    printf("Testing empty list\n");
    {
        int x; 
        int not_empty = Pop_Back(&list4, &x);
        if (not_empty) {
            printf("Element popped was %d\n",x);
            Print_List(stdout,list);
            printf("size = %d\n",Size(list));
        }
        else 
            printf("List was empty\n");
    }

    //test for Count_If
    printf("\nTesting Count_If\n");
    Push_Front(&list, 5);
    Push_Front(&list, 5);
    Print_List(stdout, list);
    printf("5 count = %d\n",Count_If(list, 5));
    printf("Testing empty list\n");
    printf("count = %d\n", Count_If(list4, 9));
    printf("Testing non existent\n");
    printf("count = %d\n", Count_If(list3, 9));
    
    // write a test for Delete 
    printf("\nTesting Delete\n");
    Print_List(stdout, list);
    Delete(&list, 1); 
    Print_List(stdout, list);
    printf("Testing empty list\n");
    printf("Expect 0: %d\n", Delete(&list4, 9));
    printf("Testing non-existent\n");
    printf("Expect 0: %d\n", Delete(&list3, 9));
    Print_List(stdout, list3);


    // write a better test for Is_Empty
    printf("\nTesting Is_Empty\n");
    if (Is_Empty(list)) {
        printf("List is Empty\n"); 
    } else {
        printf("List is not empty\n");
    }
    printf("Testing empty list\n");
    printf("Expect 1: %d\n", Is_Empty(list4));
    
    // write a better test for Clear
    printf("\nTesting Clear\n");
    Clear(&list);
    if (Is_Empty(list)) {
        printf("List is Empty\n");
    } else {
        printf("List is not empty\n");
    }
    printf("List after Clear: ");
    Print_List(stdout, list);
    printf("Testing empty list\n");
    Clear(&list4);
    printf("No errors thrown\n");

    // write a better test for Remove_Duplicates
    printf("\nTesting Remove_Duplicates\n");
    Push_Back(&list, 1);
    Push_Back(&list, 1);
    Push_Back(&list, 1);
    Push_Back(&list, 2);
    Push_Back(&list, 2);
    Push_Back(&list, 3);
    Push_Back(&list, 3);
    Push_Back(&list, 3);
    Remove_Duplicates(&list);
    Print_List(stdout, list);
    printf("Testing empty list\n");
    Remove_Duplicates(&list4);
    printf("No errors thrown\n\n");

    // Clearing screen but keeping scrollback buffer
    system("clear -x");
    printf("Testing random nonsense. Scroll back up for organized tests of each method\n");

    // Everything
    printf("\nTesting random shit put together\n");
    LINKED_LIST list5 = Create_List();
    printf("Push_Front 5: ");
    Push_Front(&list5, 5);
    Print_List(stdout, list5);
    printf("Push_Back 6: ");
    Push_Back(&list5, 6);
    Print_List(stdout, list5);
    Remove_Duplicates(&list5);
    printf("Remove_Duplicates: ");
    Print_List(stdout, list5);
    printf("Push_Front 5: ");
    Push_Front(&list5, 5);
    Print_List(stdout, list5);
    printf("Push_Front 5: ");
    Push_Front(&list5, 5);
    Print_List(stdout, list5);
    printf("Push_Front 5: ");
    Push_Front(&list5, 5);
    Print_List(stdout, list5);
    printf("Push_Front 5: ");
    Push_Front(&list5, 5);
    Print_List(stdout, list5);
    printf("Delete 5: ");
    Delete(&list5, 5);
    Print_List(stdout, list5);
    printf("Delete 5: ");
    Delete(&list5, 5);
    Print_List(stdout, list5);
    printf("Push_Back 5: ");
    Push_Back(&list5, 5);
    Print_List(stdout, list5);
    printf("Push_Back 5: ");
    Push_Back(&list5, 5);
    Print_List(stdout, list5);
    printf("Push_Back 5: ");
    Push_Back(&list5, 5);
    Print_List(stdout, list5);
    printf("Push_Back 5: ");
    Push_Back(&list5, 5);
    Print_List(stdout, list5);
    printf("Count_If 5 (Expect 7): %d\n", Count_If(list5, 5));
    int data = 0;
    int *pData = &data;
    Pop_Front(&list5, pData);
    printf("Pop_Front: %d\n", *pData);
    Print_List(stdout, list5);
    Pop_Front(&list5, pData);
    printf("Pop_Front: %d\n", *pData);
    Print_List(stdout, list5);
    Pop_Front(&list5, pData);
    printf("Pop_Front: %d\n", *pData);
    Print_List(stdout, list5);
    Pop_Front(&list5, pData);
    printf("Pop_Front: %d\n", *pData);
    Print_List(stdout, list5);
    Pop_Back(&list5, pData);
    printf("Pop_Back: %d\n", *pData);
    Print_List(stdout, list5);
    Pop_Back(&list5, pData);
    printf("Pop_Back: %d\n", *pData);
    Print_List(stdout, list5);
    printf("Push_Back 5: ");
    Push_Back(&list5, 5);
    Print_List(stdout, list5);
    printf("Push_Back 5: ");
    Push_Back(&list5, 5);
    Print_List(stdout, list5);
    printf("Push_Back 5: ");
    Push_Back(&list5, 5);
    Print_List(stdout, list5);
    printf("Push_Back 5: ");
    Push_Back(&list5, 5);
    Print_List(stdout, list5);
    printf("Push_Back 6: ");
    Push_Back(&list5, 6);
    Print_List(stdout, list5);
    printf("Push_Front 6: ");
    Push_Front(&list5, 6);
    Print_List(stdout, list5);
    printf("Remove_Duplicates: ");
    Remove_Duplicates(&list5);
    Print_List(stdout, list5);
    Clear(&list5);
    printf("List after clear: ");
    Print_List(stdout, list5);
    printf("Is_Empty (Expect 1): %d\n", Is_Empty(list));

    printf("\n");

    return 0;
}
*/
