#ifndef TUNNEL_H_INCLUDED
#define TUNNEL_H_INCLUDED

#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include "../tools.h"

#define MAX_CARS_TUNNEL 20
#define COUNT_GEN_CARS 50

// Array of cars
int southEntrance[COUNT_GEN_CARS];
int southWay[MAX_CARS_TUNNEL];
int northEntrance[COUNT_GEN_CARS];
int northWay[MAX_CARS_TUNNEL];

int start();
void* car(int *idCar);
void display();

int definePath();



#endif // TUNNEL_H_INCLUDED
