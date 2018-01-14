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

int getArrayLength(int* array, int size, int endValue)
{
    int length = 0;
    bool lengthFound = false;

    while(length < size && !lengthFound)
    {
        lengthFound = array[length] == endValue;

        if(!lengthFound)
        {
            length++;
        }
    }

    return length;
}

void rc()
{
    printf("\n");
}

double getElapsedTime(clock_t* clockStart, clock_t* clockEnd)
{
    return (double)(*clockEnd - *clockStart) / (CLOCKS_PER_SEC);
}
