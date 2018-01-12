#include "tunnel.h"

int start()
{
    pthread_t threads[COUNT_GEN_CARS];

    initArray(northEntrance, COUNT_GEN_CARS, NOTVALID);
    initArray(northWay, MAX_CARS_TUNNEL, NOTVALID);
    initArray(southEntrance, COUNT_GEN_CARS, NOTVALID);
    initArray(southWay, MAX_CARS_TUNNEL, NOTVALID);

    //definePath();
    int i;
    for(i = 0;i < COUNT_GEN_CARS; i++)
    {
        // To be continued ...
        //if(pthread_create())
    }

    return 0;
}

void* car(int* idCar)
{

}

void display()
{

}

int definePath()
{
    srand(time(NULL));
    return rand()%2;
}
