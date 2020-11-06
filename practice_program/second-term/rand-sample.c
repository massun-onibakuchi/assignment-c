#include <stdio.h>
#include <stdlib.h>
#define MAXTIME 200
#define A 3.5
#define X0 0.3

// static double alpha = 0.2; /* global variable */

int main(int argc, char *argv[])
{
    float x = X0;
    int time;
    FILE *fd;

for (int i = 0; i < 20; i++)
{
    x = (float)rand() / (RAND_MAX + 1.0);
    printf("%f \n ", x);
}


    return 0;
}
