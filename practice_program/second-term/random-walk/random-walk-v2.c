#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define TIME 50    /* time */
#define TRIALS 100000  /* number of trials */
#define PROB_RIGHT 0.4 /* number of random values */
#define PROB_LEFT 0.4  /* number of random values */
#define PROB_STAY 0.2  /* number of random values */

/* ランダムウオーク */

int trial();
int rnd_step();

int main()
{
    FILE *fd; 
    //TIME後の位置x
    int posi;
    /* 2次元配列
    インデックス0に position<0の時のカウントを格納
    インデックス1に position>=0の時のカウントを格納
    */
    int result[2][TIME + 1];

    /* initialize the array */
    for (int i = 0; i < TIME + 1; i++)
    {
        result[0][i] = 0; 
        result[1][i] = 0; 
    }

    //一人の試行*TRIALS回行う
    for (int i = 0; i < TRIALS; i++)
    {
        posi = trial();
        // 最終的な位置posiに対してカウントをインクリメント
        if (posi < 0)
            result[0][-posi] += 1;
        else
            result[1][posi] += 1;
    }

    fd = fopen("../rand_walk_50.csv", "w");

    for (int i = 0; i < 2; i += 1)
    {
        for (int k = 0; k < TIME + 1; k++)
        {
            // カラム 位置x その観測数/試行回数 としてcsv形式で出力
            fprintf(fd, "%d,%f\n", (i == 1) ? k : -k, result[i][k] / (float)TRIALS);
            // printf("%d, %d ,%f\n", (i == 1) ? k : -k, result[i][k], result[i][k] / (float)TRIALS);
            // fprintf(fd, "%d,%f\n", (i == 1) ? k : -k, result[i][k]);
        }
    }

    fclose(fd);
    return 0;
}

/** 
 * ランダムウオークで最終的に到着する位置xを返す
 */
int trial()
{
    int step = 0;
    int posi = 0;
    for (int i = 0; i < TIME; i++)
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
