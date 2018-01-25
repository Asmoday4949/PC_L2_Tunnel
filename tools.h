#ifndef TOOLS_H_INCLUDED
#define TOOLS_H_INCLUDED

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#if defined(_WIN32)
    #include <windows.h>
#elif defined(__linux__)
    #include <unistd.h>
#endif // defined



#define NOTVALID -1

enum ShiftDirection
{
    RIGHT = 1,
    LEFT = -1
};

void initArray(int* array, int size, int value);
void printArray(int* array, int size);
int getArrayLength(int* array, int size, int endValue);
void shiftArrayElements(int* array, int size, enum ShiftDirection direction);
void rc();
void sleep(int ms);

double getElapsedTime(clock_t* clockStart, clock_t* clockEnd);

void clearConsole();

#endif // TOOLS_H_INCLUDED
