#include "tunnel.h"

int start()
{
    pthread_t carThreads[GENERATOR_MAX_CARS];
    pthread_t displayThread;

    sem_init(&semNorthEntrance, 0, 1);
    sem_init(&semNorthWay, 0, 1);
    sem_init(&semSouthEntrance, 0, 1);
    sem_init(&semSouthWay, 0, 1);
    sem_init(&semTunnel, 0, TUNNEL_MAX_CARS);
    sem_init(&semSouthWayCars, 0, TUNNEL_MAX_CARS_PER_WAY);
    sem_init(&semNorthWayCars, 0, TUNNEL_MAX_CARS_PER_WAY);

    initArray(northEntrance, GENERATOR_MAX_CARS, NOTVALID);
    initArray(northWay, TUNNEL_MAX_CARS, NOTVALID);
    initArray(southEntrance, GENERATOR_MAX_CARS, NOTVALID);
    initArray(southWay, TUNNEL_MAX_CARS, NOTVALID);

    // Launch the display thread
    if(pthread_create(&displayThread, NULL, display, NULL) != 0)
    {
        exit(-1);
    }

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
            if(pthread_create(&carThreads[carsCounter], NULL, car, &carsCounter) != 0)
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

    // Waiting on the end of all the threads
    int i;
    for(i = 0; i < GENERATOR_MAX_CARS; i++)
    {
        pthread_join(carThreads[i], NULL);
    }

    pthread_join(displayThread, NULL);

    return 0;
}

void* car(void* idCar)
{
    int id = *((int*)idCar);
    enum Path path = definePath();
    int iEntrance = -1;
    int iTunnel = -1;

    if(path)
    {
        sem_wait(&semSouthEntrance);
    }
    else
    {
        sem_wait(&semNorthEntrance);
    }

    int i = 0;
    while(iEntrance == -1)
    {
        if(path && southEntrance[i] == -1)
        {
            iEntrance = i;
            southEntrance[i] = id;
        }
        else if(!path && northEntrance[i] == -1)
        {
            iEntrance = i;
            northEntrance[i] = id;
        }
        i++;
    }

    if(path)
    {
        sem_post(&semSouthEntrance);
    }
    else
    {
        sem_post(&semNorthEntrance);
    }

    sem_wait(&semTunnel);

    if(path)
    {
        sem_wait(&semSouthWayCars);
        sem_wait(&semSouthWay);
    }
    else
    {
        sem_wait(&semNorthWayCars);
        sem_wait(&semNorthWay);
    }

    i = 0;
    while(iTunnel == -1)
    {
        if(path && southWay[i] == -1)
        {
            iTunnel = i;
            southWay[i] = id;

            sem_wait(&semSouthEntrance);
            southEntrance[iEntrance] = -1;
            sem_post(&semSouthEntrance);
        }
        else if(!path && northWay[i] == -1)
        {
            iTunnel = i;
            northWay[i] = id;

            sem_wait(&semNorthEntrance);
            northEntrance[iEntrance] = -1;
            sem_post(&semNorthEntrance);
        }

        i++;
    }

    if(path)
    {
        sem_post(&semSouthWay);
    }
    else
    {
        sem_post(&semNorthWay);
    }

    sleep(TIME_IN_TUNNEL);

    if(path)
    {
        sem_wait(&semSouthWay);
        southWay[iTunnel] = -1;
        sem_post(&semSouthWay);
        sem_post(&semSouthWayCars);
    }
    else
    {
        sem_wait(&semNorthWay);
        northWay[iTunnel] = -1;
        sem_post(&semNorthWay);
        sem_post(&semNorthWayCars);
    }

    sem_post(&semTunnel);

    return NULL;
}

void* display(void* data)
{
    bool isDisplaying = 1;
    while(isDisplaying)
    {
        clearConsole();

        printf("north entrance : ");
        printArray(northEntrance, GENERATOR_MAX_CARS);

        rc();

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

        rc();

        printf("south entrance : ");
        printArray(southEntrance, GENERATOR_MAX_CARS);
        rc();
        sleep(REFRESH_RATE_DISPLAY); //Every 100ms
    }


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
