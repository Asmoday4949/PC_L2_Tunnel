#include "tunnel.h"

int start()
{
    pthread_t carThreads[GENERATOR_MAX_CARS];
    pthread_t displayThread;

    initCondTunnel(&condTunnel);

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
                //printf("Car spawned with id = %d\n", carsCounter);
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

void initCondTunnel(COND_TUNNEL* condTunnel)
{
    condTunnel->carsInTunnel = 0;
    condTunnel->carsOnSouth = 0;
    condTunnel->carsOnNorth = 0;
    pthread_mutex_init(&condTunnel->mutCarsInTunnel, NULL);
    pthread_cond_init(&condTunnel->condCarsInTunnel, NULL);
}

void* car(void* idCar)
{
    int id = *((int*)idCar);
    enum Path path = definePath();
    int iEntrance = -1;
    int iTunnel = -1;

    if(path)
    {
        pthread_mutex_lock(&mutSouthEntrance);
    }
    else
    {
        pthread_mutex_lock(&mutNorthEntrance);
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
        pthread_mutex_unlock(&mutSouthEntrance);
    }
    else
    {
        pthread_mutex_unlock(&mutNorthEntrance);
    }
    // jusque là c'est bon

    pthread_mutex_lock(&(condTunnel.mutCarsInTunnel));
	while(condTunnel.carsInTunnel >= TUNNEL_MAX_CARS && (path && condTunnel.carsOnSouth >= TUNNEL_MAX_CARS_PER_WAY || !path && condTunnel.carsOnNorth >= TUNNEL_MAX_CARS_PER_WAY))
	{
	    pthread_cond_wait(&(condTunnel.condCarsInTunnel), &(condTunnel.mutCarsInTunnel));
	}

	condTunnel.carsInTunnel++;


    //boucle à changer


    i = 0;
    while(iTunnel == -1)
    {
        if(path)
        {
            pthread_mutex_lock(&mutSouthWay);
        }
        else
        {
            pthread_mutex_lock(&mutNorthWay);
        }
        if(path && southWay[i] == -1)
        {
            iTunnel = i;
            southWay[i] = id;

            pthread_mutex_unlock(&mutSouthEntrance);
            southEntrance[iEntrance] = -1;
            pthread_mutex_unlock(&mutSouthEntrance);

            condTunnel.carsOnSouth++;
        }
        else if(!path && northWay[i] == -1)
        {
            iTunnel = i;
            northWay[i] = id;

            pthread_mutex_unlock(&mutNorthEntrance);
            northEntrance[iEntrance] = -1;
            pthread_mutex_unlock(&mutNorthEntrance);

            condTunnel.carsOnNorth++;
        }
        if(path)
        {
            pthread_mutex_unlock(&mutSouthWay);
        }
        else
        {
            pthread_mutex_unlock(&mutNorthWay);
        }

        i++;
    }

    pthread_mutex_unlock(&(condTunnel.mutCarsInTunnel));

    sleep(TIME_IN_TUNNEL);

    //libération
    if(path)
    {
        pthread_mutex_lock(&mutSouthWay);
        southWay[iTunnel] = -1;
        condTunnel.carsOnNorth--;
        pthread_mutex_unlock(&mutSouthWay);;
    }
    else
    {
        pthread_mutex_unlock(&mutNorthWay);
        northWay[iTunnel] = -1;
        condTunnel.carsOnNorth--;
        pthread_mutex_unlock(&mutNorthWay);
    }

    condTunnel.carsInTunnel--;
    //pthread_cond_broadcast(&(condTunnel.condCarsInTunnel));

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
        printArrayLength(northEntrance, GENERATOR_MAX_CARS);

        rc();

        //tunnel
        printWall(TUNNEL_DEFAULT_LENGTH);
        rc();
        printArray(northWay, TUNNEL_MAX_CARS);
        printArrayLength(northWay, TUNNEL_MAX_CARS);
        rc();
        printRoadMark(TUNNEL_DEFAULT_LENGTH);
        rc();
        printArray(southWay, TUNNEL_MAX_CARS);
        printArrayLength(southWay, TUNNEL_MAX_CARS);
        rc();
        printWall(TUNNEL_DEFAULT_LENGTH);

        rc();

        printf("south entrance : ");
        printArray(southEntrance, GENERATOR_MAX_CARS);
        printArrayLength(southEntrance, GENERATOR_MAX_CARS);
        rc();
        sleep(REFRESH_RATE_DISPLAY); //Every 100ms
    }


    return NULL;
}

void printArrayLength(int* array, int size)
{
    int length = getArrayLength(array, size, NOTVALID);

    printf("(%d)", length);
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
