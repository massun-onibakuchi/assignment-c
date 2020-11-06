#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 10              /* number of random values */
#define TRIALS 1000 * 100 /* number of random values */
#define PROB_RIGHT 0.4    /* number of random values */
#define PROB_LEFT 0.4     /* number of random values */
#define PROB_STAY 0.2     /* number of random values */

int main()
{
    int i, index, hist[N];
    int posi;
    FILE *fd;
    int *array = (int *)malloc(sizeof(int) * 2 * N);

    int hist2 = rand_walk();

    /* output results to the file */
    fd = fopen("rand-hist.d", "w");
    for (i = 0; i < 10; i++)
        fprintf(fd, "%d %d\n", i, hist[i]);
    fclose(fd);

    return 0;
}

int trial()
{
    int index;
    // int hist2[2][N];
    float x;
    int posi;
    FILE *fd;

    for (int i = 0; i < N; i++)
    {
        x = (float)rand() / (RAND_MAX + 1.0) * 3; /* generates a random value [0, 3) */
        printf("x=%f\n", x);
        index = floor(x) - 1; /* an integer less than or equal to x. i.e -1 or 0 or 1 */
        posi += index;
    }
    return posi;
}

int rand_walk()
{
    FILE *fd;
    float prob_dist[2][N];
    int hist[2][N];

    for (int i = 0; i < TRIALS; i++)
    {
        int posi = trial();
        if (posi < 0)
            hist[0][-posi]++;
        else
            hist[1][posi]++;
    }

    fd = fopen("rand-hist.d", "w");

    for (int i = 0; i < 2; i++)
    {
        for (int k = 0; k < N; k++)
        {
            // prob_dist[i][k] = hist[i][k] / N;
            fprintf(fd, "%d %d\n", (i - 1) * k, hist[i][k] / N);
        }
    }

    fclose(fd);
}

// int calc_prob()
// {
//     int hist = count();
//     float prob_dist[2][N];
//     for (int i = 0; i < 2; i++)
//     {
//         for (int k = 0; k < N; k++)
//         {
//             prob_dist[i][k] = hist[i][k] / N;
//         }
//     }
// }

// int *calc_prob(int *hist)
// {
//     count(hist);
//     float prob_dist[2][N];
//     for (int i = 0; i < 2; i++)
//     {
//         for (int k = 0; k < N; k++)
//         {
//             prob_dist[i][k] = &hist[i][k] / N;
//         }
//     }
// }
