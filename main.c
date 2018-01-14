#include <stdio.h>
#include <stdlib.h>

// Choose the program to compile with this define
// PART1 --> Semaphores without restrictions per way
// PART2 --> Semaphores with restrictions per way
// PART3 --> Monitors version of the previous part
#define PART1

#if defined(PART1)
    #include "part1/tunnel.h"
#elif defined(PART2)
    #include "part2/tunnel.h"
#elif defined(PART3)
    #include "part3/tunnel.h"
#endif

int main()
{
    start();

    return 0;
}
