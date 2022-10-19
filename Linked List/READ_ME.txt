Overview: Implement Linked List in C

Language: C

Function:

int Size(LINKED_LIST list):
Returns the number of elements in the linked list

void Push_Front(LINKED_LIST *list, int data):
Adds an element to the front of the linked list

void Push_Back(LINKED_LIST *list, int data):
Adds an element to the end of the linked list

int Pop_Front(LINKED_LIST *list, int *data):
If the list is no empty, the value of the first element of the list is returned by reference in the parameter data
The first element of the list is deleted
Returns 0 if the list is empty, otherwise returns 1

int Pop_Back(LINKED_LIST *list, int *data):
Does that same as Pop_Front but to the element at the back of the list

int Count_If(LINKED_LIST list, int data):
returns the number of times the value in the parameter appears in the list

int Delete(LINKED_LIST *list, int data):
deletes the first node containing the data specificed in the parameters.
Return 1 if something was deleted, otherwise 0

int Is_Empty(LINKED_LIST list):
return 1 if the list is empty, otherwise 0

void Clear(LINKED_LIST *list):
Deletes all elements within the list

void Remove_Duplicates(LINKED_LIST *list):
If an element appears in the list, retain the first occurence but remove all other nodes with the same value

int main():
used for testing
