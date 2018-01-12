#include "tools.h"

void initArray(int* array, int size, int value)
{
    int i;
    for(i = 0;i < size; i++)
    {
        array[i] = value;
    }
}

void printArray(int* array, int size)
{
    int i;
    for(i = 0; i < size; i++)
    {
        if(array[i] >= 0)
        {
            printf("%d ", array[i]);
        }
    }
}

void rc()
{
    printf("\n");
}
