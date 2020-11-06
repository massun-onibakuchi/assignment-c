#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define TRIALS 100000      /* number of trials */
#define PROB_RIGHT 0.4 /* number of random values */
#define PROB_LEFT 0.4  /* number of random values */
#define PROB_STAY 0.2  /* number of random values */

/**@description ランダムウオーク */

struct data
{
    int time;
    int trials;
    int *plus;
    int *minus;
};

int trial();
int rnd_step();
int gen_data();

int main()
{
    FILE *fd = fopen("../rand_walk_10.csv", "w");
    // FILE *fd1 = fopen("../rand_walk_30.csv", "w");
    // FILE *fd2 = fopen("../rand_walk_50.csv", "w");

    gen_data(fd, 10, TRIALS);
    // gen_data(fd1, 30, TRIALS);
    // gen_data(fd2, 50, TRIALS);

    fclose(fd);
    // fclose(fd1);
    // fclose(fd2);
    return 0;
}

int gen_data(FILE *fd, int time, int trials)
{
    struct data *data = (struct data *)malloc(sizeof(struct data));

    trial(data, time, trials);

    for (int k = 0; k < time + 1; k++)
    {
        // カラム 位置x その観測数/試行回数 としてcsv形式で出力
        fprintf(fd, "%d,%f\n", k, data->plus[k] / (float)TRIALS);
        fprintf(fd, "%d,%f\n", -k, data->minus[k] / (float)TRIALS);
        // printf("plus[%d],%f\n", k, data->plus[k] / (float)TRIALS);
        // printf("minus[%d],%f\n", -k, data->minus[k] / (float)TRIALS);
    }
    return 0;
}

/** 
 * ランダムウオークで最終的に到着する位置xを返す
 */
int trial(struct data *data, int time, int trials)
{
    // struct data *data = (struct data *)malloc(sizeof(struct data));
    int *plus = (int *)malloc(sizeof(int) * (time + 1));
    int *minus = (int *)malloc(sizeof(int) * (time + 1));
    data->plus = plus;
    data->minus = minus;

    for (int i = 0; i < time + 1; i++)
    {
        plus[i] = 0;
        minus[i] = 0;
    }

    //trials回試行
    for (int i = 0; i < trials; i++)
    {
        //一回の試行 time秒までランダムウオークする
        int step = 0;
        int posi = 0;
        for (int i = 0; i < time; i++)
        {
            step = rnd_step();
            posi += step;
        }
        // 最終的な位置posiに対してカウントをインクリメント
        (posi < 0) ? data->minus[-posi]++ : data->plus[posi]++;
        // if (posi < 0)
        //     data->minus[-posi] += 1;
        // else
        //     data->plus[posi] += 1;
    }

    // printf("結果　plus\n");
    // for (int i = 0; i < time + 1; i++)
    // {
    //     // printf("plus[%d]5以下であるべき beofre %d\n", i, plus[i]);
    //     printf("plus[%d] 和がtimeに等しい %d\n", i, plus[i]);
    //     printf("minus[%d] 和がtimeに等しい %d\n", i, minus[i]);
    //     // printf("plus[%d] 5以下であるべき after %d\n", i, plus[i]);
    // }
    return 0;
}

/** 
 * 乱数を用いて決定されるstepを返す
 * @return -1 or 0 or 1
 */
int rnd_step()
{
    float rnd = 0.0;
    rnd = (float)rand() / (RAND_MAX + 1.0); /* generates a random value [0, 1) */
    if (rnd < PROB_LEFT)
        return -1;
    if (rnd < PROB_STAY + PROB_LEFT)
        return 0;
    else
        return 1;
}
