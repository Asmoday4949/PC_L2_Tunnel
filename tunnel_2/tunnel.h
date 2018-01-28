#ifndef TUNNEL_H_INCLUDED
#define TUNNEL_H_INCLUDED

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "tools.h"

// Used for printing debug info
//#define DEBUG

// Program macros
#define TUNNEL_MAX_CARS 20
#define TUNNEL_DEFAULT_LENGTH 25
#define TUNNEL_MAX_CARS_PER_WAY 12
#define GENERATOR_MAX_CARS 100
#define GENERATOR_SPAWNER_TIME 0.1
#define TIME_IN_TUNNEL 5000 //5sec
#define REFRESH_RATE_DISPLAY 100

// Enums
enum Path
{
    NORTH_WAY = 0,
    SOUTH_WAY = 1
};

// Semaphores for protecting the arrays
sem_t semSouthEntrance;
sem_t semSouthWay;
sem_t semNorthEntrance;
sem_t semNorthWay;

//semaphore which represent the tunnel and the 20 slots
sem_t semTunnel;

// Semaphores for the slots per way
sem_t semSouthWayCars;
sem_t semNorthWayCars;

// Array of cars
int southEntrance[GENERATOR_MAX_CARS];
int southWay[TUNNEL_MAX_CARS];
int northEntrance[GENERATOR_MAX_CARS];
int northWay[TUNNEL_MAX_CARS];

/*
MAIN FUNCTION
*/
int start();

/*
Thread function, each car thread represent a car
*/
void* car(void *idCar);

/*
thread for displaying the tunnel and the car
*/
void* display(void* data);
void printArrayLength(int* array, int size);
//AESTHIC PURPOSE
void printWall(int size);
void printRoadMark(int size);

/*
function to define north or south way
*/
int definePath();



#endif // TUNNEL_H_INCLUDED
