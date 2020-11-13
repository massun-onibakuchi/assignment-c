#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXNUM 1000 /* number of random values */
#define AVE 1.0     /* number of random values */

float inverse_F(float r);

int main(void)
{
    int i, index, histo[100] = {0}; /* reset histo array */
    float r, x;
    FILE *fd;

    for (i = 0; i < MAXNUM; i++)
    {
        x = inverse_F(AVE);
        index = floor(x * 10); /* index number */
        if (index > 100)
        {
            printf("%d", index);
            continue;
        }
        histo[index]++;
        printf("%d\n", index);
    }

    /* output the result to a file */
    fd = fopen("histo.d", "w");
    for (i = 0; i <= 100; i++)
        fprintf(fd, "%d %d\n", i, histo[i]);
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