/* Runge-Kutta Method */
#include <stdio.h>
#define MAXTIME 200
#define A 3.5
#define X0 0.3

float func(float a, float t, float v);

// static double alpha = 0.2; /* global variable */

int main(int argc, char *argv[])
{
    float x=X0;
    int time;
    FILE *fd;

    if (argc > 1) sscanf(argv[1], "%f", &x);
    printf("x=%f\n", x);

    fd = fopen("./../logistic.csv", "w");
    // /Users/masudashouta/ethereum/clang_docker/practice_program
    for (time = 0; time < MAXTIME; time++)
    {
        x = func(A, time, x);
        fprintf(fd, "%d,%f\n", time, x);
        printf("t=%d ,x=%f\n", time,x);
    }
    fclose(fd);

    return 0;
}

float func(float a, float t, float x)
{
    return a * x * (1 - x);
}