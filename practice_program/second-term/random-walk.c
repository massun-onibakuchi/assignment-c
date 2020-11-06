/**
 * @file random-walk.c
 * @brief ランダムウォークのモンテカルロ法
 **/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define TRIALS 100000  /* number of trials */
#define PROB_RIGHT 0.4 /* number of random values */
#define PROB_LEFT 0.4  /* number of random values */
#define PROB_STAY 0.2  /* number of random values */

/**
 * @struct Data
 * ランダムウォークの時間，試行回数，位置 
 */
struct Data
{
    int time;
    int trials;
    int *plus;
    int *minus;
};

int rnd_step();
int iterate_trial(struct Data *data, int time, int trials);
int trial(int time);
int gen_data(FILE *fd, int time, int trials);

int main()
{
    FILE *fd = fopen("../rand_walk_10.csv", "w");
    FILE *fd1 = fopen("../rand_walk_30.csv", "w");
    FILE *fd2 = fopen("../rand_walk_50.csv", "w");

    gen_data(fd, 10, TRIALS);
    gen_data(fd1, 30, TRIALS);
    gen_data(fd2, 50, TRIALS);

    fclose(fd);
    fclose(fd1);
    fclose(fd2);
    return 0;
}

/** 
 * 指定された時間と試行回数でランダムウォークをモンテカル法する
 * @param fd FILE
 * @param time ランダムウォークの時間
 * @param trials 試行回数
 */
int gen_data(FILE *fd, int time, int trials)
{
    //動的に割り当て
    struct Data *data = (struct Data *)malloc(sizeof(struct Data));
    
    //指定された時間と試行回数でランダムウォークをモンテカル法する
    iterate_trial(data, time, trials);

    // カラム 位置x その観測数/試行回数 としてcsv形式で出力
    // plusとminusのindex0が重複するのでposiが0の時は特別に処理する
    fprintf(fd, "%d,%f\n", 0, data->plus[0] / (float)TRIALS);
    for (int k = 1; k < time + 1; k++)
    {
        fprintf(fd, "%d,%f\n", k, data->plus[k] / (float)TRIALS);
        fprintf(fd, "%d,%f\n", -k, data->minus[k] / (float)TRIALS);
        // printf("plus[%d],%f\n", k, data->plus[k] / (float)TRIALS);
        // printf("minus[%d],%f\n", -k, data->minus[k] / (float)TRIALS);
    }
    return 0;
}

/** 
 * 指定された時間と試行回数でランダムウォークをモンテカル法する
 * @param data struct *Data
 * @param time ランダムウォークの時間
 * @param trials 試行回数
 */
int iterate_trial(struct Data *data, int time, int trials)
{
    int *plus = (int *)malloc(sizeof(int) * (time + 1));
    int *minus = (int *)malloc(sizeof(int) * (time + 1));
    data->plus = plus;
    data->minus = minus;

    for (int i = 0; i < time + 1; i++)
    {
        plus[i] = 0;
        minus[i] = 0;
    }

    //trials回 ランダムウォークを試行
    for (int i = 0; i < trials; i++)
    {
        // 一人のランダムウォークの試行で最終的に到着する位置x
        int posi = trial(time); 
        // 最終的な位置posiに対してカウントをインクリメント
        (posi < 0) ? data->minus[-posi]++ : data->plus[posi]++;
    }

    return 0;
}

/** 一人のランダムウォークの試行で最終的に到着する位置x
 * を返す
 * @param time 
 * @return posi 位置
 */
int trial(int time)
{
    int step = 0;
    int posi = 0;
    for (int i = 0; i < time; i++)
    {
        step = rnd_step();
        posi += step;
    }
    return posi;
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
