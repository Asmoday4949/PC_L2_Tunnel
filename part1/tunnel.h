#ifndef TUNNEL_H_INCLUDED
#define TUNNEL_H_INCLUDED

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "../tools.h"

#define MAX_CARS_TUNNEL 20
#define COUNT_GEN_CARS 50
#define TUNNEL_DEFAULT_LENGTH 25

// Array of cars
int southEntrance[COUNT_GEN_CARS];
int southWay[MAX_CARS_TUNNEL];
int northEntrance[COUNT_GEN_CARS];
int northWay[MAX_CARS_TUNNEL];

/*
MAIN FUNCTION
*/
int start();

/*
Thread function, each car thread represent a car
*/
void* car(int *idCar);

/*
thread for displaying the tunnel and the car
*/
void* display(void* data);
//AESTHIC PURPOSE
void printWall(int size);
void printRoadMark(int size);

/*
function to define north or south way
*/
int definePath();



#endif // TUNNEL_H_INCLUDED
