#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int g_data = 10;  // Data Segment

int main() {
    int l_stack = 20;            // Stack Segment
    int *p_heap = malloc(100);   // Heap Segment

    printf("PID   : %d\n", getpid());
    printf("Text  : %p (Code)\n", main);
    printf("Data  : %p (Global)\n", &g_data);
    printf("Heap  : %p (Dynamic)\n", p_heap);
    printf("Stack : %p (Local)\n", &l_stack);
    printf("----------------------------------\n");

    free(p_heap);
    return 0;
}