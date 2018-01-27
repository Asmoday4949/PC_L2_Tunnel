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

int getArrayLength(int* array, int size, int badValue)
{
    int length = 0;
    int i;
    for(i = 0;i < size; i++)
    {
        if(array[i] > badValue)
        {
            length += 1;
        }
    }

    return length;
}

void shiftArrayElements(int* array, int size, enum ShiftDirection direction)
{
    if(direction == LEFT)
    {
        int tmp = array[0];
        int i;
        for(i = 0;i < size-1; i++)
        {
            array[i] = array[i+1];
        }
        array[size-1] = tmp;
    }
    else if(direction == RIGHT)
    {
        int tmp = array[size-1];
        int i;
        for(i = size-2;i >= 0; i--)
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

void clearConsole()
{
    // Compatibility for Windows and Linux
    #if defined(_WIN32)
        system("cls");
    #elif defined(__linux__)
        system("clear");
    #endif // defined
}

void sleep(int ms)
{
    #if defined(_WIN32)
        Sleep(ms);
    #elif defined(__linux__)
       usleep(ms*1000);
    #endif

}
