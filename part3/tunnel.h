#ifndef TUNNEL_H_INCLUDED
#define TUNNEL_H_INCLUDED

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "../tools.h"

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

// mutex for protecting the arrays
pthread_mutex_t mutSouthEntrance;
pthread_mutex_t mutSouthWay;
pthread_mutex_t mutNorthEntrance;
pthread_mutex_t mutNorthWay;

//conditions
typedef struct
{
	int carsInTunnel;
	int carsOnSouth;
	int carsOnNorth;
	pthread_mutex_t mutCarsInTunnel;
	pthread_cond_t condCarsInTunnel;
} COND_TUNNEL;

COND_TUNNEL condTunnel;

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
INIT FUNCTION
*/
void initCondTunnel(COND_TUNNEL* condTunnel);

/*
Thread function, each car thread represent a car
*/
void* car(void *idCar);

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
