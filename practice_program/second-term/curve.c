/* Runge-Kutta Method */
#include <stdio.h>
#define MAXLOOP 1000

/** 
 * dx/dt = -x - 2 * y
 * @param t time 
 * @param x position(x,y)
 * @param y position(x,y)
 */
double func_f(double t, double x, double y);

/** 
 *  dy/dt =2 * x - y
 * @param t time 
 * @param x position(x,y)
 * @param y position(x,y)
 */
double func_g(double t, double x, double y);

int main(int argc, char *argv[])
{
    double dt = 0.01;
    double kx1, kx2, kx3, kx4;
    double ky1, ky2, ky3, ky4;

    /* initial value */
    double x = 10;
    double y = 10;
    int i;
    FILE *fd;

    if (argc > 2)
    {
        sscanf(argv[1], "%lf", &x);
        sscanf(argv[2], "%lf", &y);
    }
    printf("(x,y) = (%f,%f) when t=0\n", x, y);

    fd = fopen("curve.d", "w");
    for (i = 0; i < MAXLOOP; i++)
    {
        //1
        kx1 = dt * func_f(dt * i, x, y);
        ky1 = dt * func_g(dt * i, x, y);
        //2
        kx2 = dt * func_f(dt * i + dt / 2.0, x + kx1 / 2.0, y + ky1 / 2.0);
        ky2 = dt * func_g(dt * i + dt / 2.0, x + kx1 / 2.0, y + ky1 / 2.0);
        //3
        kx3 = dt * func_f(dt * i + dt / 2.0, x + kx2 / 2.0, y + ky2 / 2.0);
        ky3 = dt * func_g(dt * i + dt / 2.0, x + kx2 / 2.0, y + ky2 / 2.0);
        //4
        kx4 = dt * func_f(dt * i + dt, x + kx3, y + ky3);
        ky4 = dt * func_g(dt * i + dt, x + kx3, y + ky3);

        x += (kx1 + kx2 * 2.0 + kx3 * 2.0 + kx4) / 6.0;
        y += (ky1 + ky2 * 2.0 + ky3 * 2.0 + ky4) / 6.0;
        fprintf(fd, "%f %f %f\n", dt * i, x, y);
    }
    fclose(fd);

    return 0;
}

double func_f(double t, double x, double y)
{
    return -x - 2 * y;
}
double func_g(double t, double x, double y)
{
    return 2 * x - y;
}