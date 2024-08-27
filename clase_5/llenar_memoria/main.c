#include <stdio.h>
#include <stdlib.h>

int main() {
    double block_size = 1024 * 1024;

    double mem_total = 0;
    void *puntero = NULL;

    while ((puntero = malloc(block_size)) != NULL) {
        mem_total += block_size;
        printf("Memoria total: %f\n",mem_total);
    }
    return 0;
}