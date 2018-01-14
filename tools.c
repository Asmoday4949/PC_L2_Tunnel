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
    printf("\n");
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

void shiftArrayElements(int* array, int size, enum Direction direction)
{
    if(direction == LEFT)
    {
        int tmp = array[0];

        for(int i = 0;i < size-1; i++)
        {
            array[i] = array[i+1];
        }
        array[size-1] = tmp;
    }
    else if(direction == RIGHT)
    {
        int tmp = array[size-1];

        for(int i = size-2;i >= 0; i--)
        {
            array[i+1] = array[i];
        }
        array[0] = tmp;
    }
}

void rc()
{
    printf("\n");
}

double getElapsedTime(clock_t* clockStart, clock_t* clockEnd)
{
    return (double)(*clockEnd - *clockStart) / (CLOCKS_PER_SEC);
}
