#include "tunnel.h"

int start()
{
    pthread_t threads[GENERATOR_MAX_CARS];
    pthread_t display;

    initArray(northEntrance, GENERATOR_MAX_CARS, NOTVALID);
    initArray(northWay, TUNNEL_MAX_CARS, NOTVALID);
    initArray(southEntrance, GENERATOR_MAX_CARS, NOTVALID);
    initArray(southWay, TUNNEL_MAX_CARS, NOTVALID);

    if(pthread_create(&display, NULL, display, NULL) != 0)
    {
        exit(-1);
    }

    //starting the car
    int i;
    for(i = 0;i < GENERATOR_MAX_CARS; i++)
    {
        if(pthread_create(&threads[i], NULL, car, &i) != 0)
        {
            exit(-1);
        }
    }


    for(i = 0; i < GENERATOR_MAX_CARS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}

void* car(int* idCar)
{
    int id = *idCar;
    int path = definePath();

    if(path)
    {

    }
    else
    {

    }
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
