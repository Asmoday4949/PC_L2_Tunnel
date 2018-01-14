#ifndef TOOLS_H_INCLUDED
#define TOOLS_H_INCLUDED

#include <time.h>
#include <stdbool.h>

#define NOTVALID -1

void initArray(int* array, int size, int value);
void printArray(int* array, int size);
int getArrayLength(int* array, int size, int endValue);
void rc();

double getElapsedTime(clock_t* clockStart, clock_t* clockEnd);

#endif // TOOLS_H_INCLUDED
