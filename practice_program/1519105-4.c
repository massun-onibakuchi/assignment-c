#include <stdio.h>
int main(void)
{
    // 変数の宣言
    // score[101]　100までの番号をインデックスとして対応する点数を格納
    int score[101];
    int i;
    int dataId;
    // int arrIdx;
    //　ファイルのId格納
    FILE *fd;
    fd = fopen("test.txt", "r");

    //全生徒の点数をデフォルト404として初期化
    // 以降の操作でデータとして存在しない生徒の点数は404となる
    for (i = 0; i <= 101; i++)
    {
        score[i] = 404;
    }

    while (fscanf(fd, "%d, %d\n", &dataId, &(score[dataId])) != EOF)
    {
        printf("dataId= %d ,score[dataId]=%d\n", dataId, score[dataId]);
        // i++;
    }
    // while (fscanf(fd, "%d: %d", &dataId, &score[dataId]) != EOF)
    // {
    //     printf("dataId= %d ,score[dataId]=%d\n", dataId, score[dataId]);
    //     // i++;
    // }

    // 全生徒の点数をscoreに格納する
    // for (i = 0; i < 101; i++)
    // {
    //     if (fscanf(fd, "%d: %d", &dataId, &score[dataId]) == EOF)
    //         break;
    //     printf("dataId= %d ,score[dataId]=%d\n", dataId, score[dataId]);
    // }
    // 小さいインデックス順（番号順）に対応する点数をプリントするが，
    // 404ならその点数データは存在しないのでプリントしない
    for (i = 1; i <= 101; i++)
    {
        if (score[i] != 404)
        {
            printf("%d:%d\n", i, score[i]);
        }
    }

    fclose(fd);
    printf("終わり\n");
    return 0;
}
