#include "mem.h"
#include <stdio.h>

int main() {
    Initialize_Memory_Allocator(1600);
    Mem_Dump();
   
    int *p1 = Mem_Alloc(8);
    int *p2 = Mem_Alloc(16);
    int *p3 = Mem_Alloc(24);
    int *p4 = Mem_Alloc(32);
    int *p5 = Mem_Alloc(40);
    int *p6 = Mem_Alloc(48);
    int *p7 = Mem_Alloc(56);
    int *p8 = Mem_Alloc(64);
    int *p9 = Mem_Alloc(72);
    Mem_Dump();

    printf("Free P7\n");
    Mem_Free(p7);
    Mem_Dump();

    printf("Free P6\n");
    Mem_Free(p6);
    Mem_Dump();

    printf("Free P8\n");
    Mem_Free(p8);
    Mem_Dump();

    printf("Free P4\n");
    Mem_Free(p4);
    Mem_Dump();
   
    printf("Free P5\n");
    Mem_Free(p5);
    Mem_Dump();
    Free_Memory_Allocator();
    return 0;
}
