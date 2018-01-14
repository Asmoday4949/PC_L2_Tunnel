#include "tunnel.h"

int start()
{
    pthread_t threads[GENERATOR_MAX_CARS];
    pthread_t display;

    initArray(northEntrance, GENERATOR_MAX_CARS, NOTVALID);
    initArray(northWay, TUNNEL_MAX_CARS, NOTVALID);
    initArray(southEntrance, GENERATOR_MAX_CARS, NOTVALID);
    initArray(southWay, TUNNEL_MAX_CARS, NOTVALID);

    /*
    // Crash, why ? don't know ... :P
    if(pthread_create(&display, NULL, display, NULL) != 0)
    {
        exit(-1);
    }
    */

    bool running = true;
    clock_t clockStart = clock();
    clock_t clockEnd;
    double timeSec = 0;
    int carsCounter = 0;

    // Spawn one car every x seconds (x defined by GENERATOR_SPAWNER_TIME)
    do
    {
        clockEnd = clock();
        timeSec = getElapsedTime(&clockStart, &clockEnd);

        if(timeSec >= GENERATOR_SPAWNER_TIME)
        {
            if(pthread_create(&threads[carsCounter], NULL, car, &carsCounter) != 0)
            {
                exit(-1);
            }

            #if defined(DEBUG)
                printf("Car spawned with id = %d\n", carsCounter);
            #endif

            running = ++carsCounter < GENERATOR_MAX_CARS;
            clockStart = clock();
        }
    }
    while(running);

    int i;
    for(i = 0; i < GENERATOR_MAX_CARS; i++)
    {
        pthread_join(threads[i], NULL);
    }
    return 0;
}

void* car(void* idCar)
{
    int id = *((int*)idCar);
    int path = definePath();
    clock_t clockStart = clock();
    clock_t clockEnd;

    if(path)
    {

    }
    else
    {

    }

    return NULL;
}

void* display(void* data)
{
    printf("north entrance : ");

    printArray(northEntrance, GENERATOR_MAX_CARS);

    rc();rc();

    //tunnel
    printWall(TUNNEL_DEFAULT_LENGTH);
    rc();
    printArray(northWay, TUNNEL_MAX_CARS);
    rc();
    printRoadMark(TUNNEL_DEFAULT_LENGTH);
    rc();
    printArray(southWay, TUNNEL_MAX_CARS);
    rc();
    printWall(TUNNEL_DEFAULT_LENGTH);

    rc();rc();

    printf("south entrance : ");
    printArray(southEntrance, GENERATOR_MAX_CARS);
    rc();

    return NULL;
}

void printWall(int size)
{
    int i;
    for(i = 0; i < size; i++)
    {
        printf("=");
    }
}

void printRoadMark(int size)
{
    int i;
    for(i = 0; i < size; i++)
    {
        printf("-");
    }
}

int definePath()
{
    srand(time(NULL));
    return rand()%2;
}
