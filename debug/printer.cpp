#include "./printer.h"

void printBits(size_t const size, void const *const ptr)
{
    unsigned char *b = (unsigned char *)ptr;
    unsigned char byte;
    int i, j;

    for (i = size - 1; i >= 0; i--)
    {
        for (j = 7; j >= 0; j--)
        {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    printf("\n");
}

void printArray(uint8_t* array, int arraySize){
    for(int i=0;i<arraySize;i++){
        printf("%d, ",array[i]);
    }
    printf("\n");
}