/* Runge-Kutta Method */
#include <stdio.h>
#define MAXLOOP 1000
#define GRAVITY 9.80665

double func(double t, double v);

static double alpha = 0.2; /* global variable */

int main(int argc, char *argv[])
{
    double dt = 0.01;
    double k1, k2, k3, k4;
    double v = 10.0; /* initial value */
    int i;
    FILE *fd;

    if (argc > 1) sscanf(argv[1], "%lf", &alpha);
    printf("alpha=%f\n", alpha);

    fd = fopen("v.d", "w");
    for (i = 0; i < MAXLOOP; i++) {
        k1 = dt * func(dt*i, v);
        k2 = dt * func(dt*i+dt/2.0, v+k1/2.0);
        k3 = dt * func(dt*i+dt/2.0, v+k2/2.0);
        k4 = dt * func(dt*i+dt, v+k3);

        v += (k1 + k2 * 2.0 + k3 * 2.0 + k4)/6.0;
        fprintf(fd, "%f %f\n", dt * i, v);
    }
    fclose(fd);

    return 0;
}

double func(double t, double v)
{
    return - alpha * v - GRAVITY;
}