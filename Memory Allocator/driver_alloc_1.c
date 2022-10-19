#include "mem.h"
#include <stdio.h>

int main() {
    Initialize_Memory_Allocator(1600);
    Mem_Dump();
   
    char *p = Mem_Alloc(1);
     printf("\n FIN");
    if (p == NULL) {
        printf("Allocation failed\n");
        exit(0);
    }
    p[0] = 'c';
    Mem_Dump();
     printf("\n FIN dump");
    Free_Memory_Allocator();
    return 0;
}
