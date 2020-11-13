#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXNUM 100 /* number of random values */
#define AVE 10.0     /* number of random values */

float inverse_F(float r);

int main(void)
{
    int i, index, histo[100] = {0}; /* reset histo array */
    float r, x;
    FILE *fd;

    for (i = 0; i < MAXNUM; i++)
    {
        r = (float)rand() / (RAND_MAX + 1.0) * 1.0; /* generate random values */
        x = inverse_F(AVE);
        index = floor(x * 10 + 10.5); /* index number */
        histo[index]++;               /* count the number */
    }

    /* output the result to a file */
    fd = fopen("histo.d", "w");
    for (i = 0; i <= 20; i++)
        fprintf(fd, "%f %d\n", 0.1 * (i - 10), histo[i]);
    fclose(fd);

    return 0;
}

float inverse_F(float ave)
{
    double x;
    double r;
    r = (double)rand() / (RAND_MAX + 1.0); /* generates a random value [0, 1) */
    x = -ave * log(1 - r);
    return x;
}