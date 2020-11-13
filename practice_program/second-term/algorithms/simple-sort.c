#include <stdio.h>
#define N 10 /* 個数を10個とする */
int main()
{
    int i, j, min, pos; /* min: ある範囲の最小値、pos: ある範囲の最小値の配列のインデックス */
    int d[N] = {20, 40, -10, 10, 0, 30, 20, 50, 100, 5};

    for (i = 0; i < N; i++)
        printf("%d ", d[i]); /* 配列dのすべての内容を表示する */
    printf("\n");

    for (i = 0; i < N; i++)
    {
        min = d[i];
        pos = i;
        for (j = i + 1; j < N; j++)
        {
            if (min > d[j])
            {
                pos = j;
                min = d[j];
            }
        }
        d[pos] = d[i];
        d[i] = min;
    }

    for (i = 0; i < N; i++)
        printf("%d ", d[i]);

    printf("\n");

    return 0;
}
