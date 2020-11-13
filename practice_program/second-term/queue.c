#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXLOOP 1000 /* 時刻の最大値 */
#define MAXLIST 100  /* 順番待ちリストの長さの最大値 */

double expdev(double);

static int visit[MAXLOOP]; /* 客の訪問の有無：visit[t] 時刻tで訪問あるならvisit[t]の値は1, それ以外は0 */
static int list[MAXLIST];  /* 客の順番待ちリスト: 客は訪問した者から1,2,3,..と番号付けされる */

int main(int argc, char *argv[])
{
    int time = 0;
    int i, itemp, itemp2;
    int current_p = 0; /* 現在サービス中の客番号. 0のときはだれにも対応してない */
    int end_time = -1;
    int new_person = 1;       /* 新しくやって来た客に付ける番号. 1から始まる. */
    double ave_arrival = 4.0; /* 客の平均到着間隔 */
    double ave_work = 8.0;    /* 一つの処理にかかる平均時間 */
    char buf;

    /* random seed */
    if (argc > 1)
        sscanf(argv[1], "%d", &i);
    srand(i); /* 乱数系列を設定する */

    /* times of visiting people */
    itemp2 = 0;
    do
    {
        itemp = (int)(expdev(ave_arrival));
        itemp2 += itemp;
    } while (itemp2 < MAXLOOP && (visit[itemp2] = 1)); /* もし最大時刻を超えなければvisitに1を設定 */

    /* MAIN LOOP */
    while (1)
    {

        /* current process finished */
        if (end_time <= time)
            current_p = 0;

        /* new commer added to the list */ /* 順番待ちリストの最後に客番号を入れる */
        if (visit[time] > 0)
        {
            for (i = 0; list[i] > 0; i++)
                ;
            list[i] = new_person;
            new_person++;
        }

        /* a process starts */
        /* もし実行中のサービスがなくて誰かが待っているならば、サービスを実行する */
        if (current_p == 0 && list[0] > 0)
        {
            /* processing */
            current_p = list[0];
            end_time = time + (int)(expdev(ave_work)); /* 始めたサービスの終了時刻を計算する */
            /* printf("end time=%d\n", end_time); */

            /* 順番待ちリストをつめる */
            i = 0;
            do
            {
                list[i] = list[i + 1];
                i++;
            } while (list[i + 1] > 0);
            list[i] = 0;
        }

        printf("\n[T=%d]\n", time);
        printf("Waiting   : ");
        for (i = 0; list[i] > 0; i++)
            printf("%d ", list[i]);
        printf("\n");

        printf("Processing: ");
        if (current_p > 0)
            printf("%d", current_p);
        printf("\n");

        /* post-procedures */
        time++;

        /* next? */
        printf("\nNext(Enter) or (Q)uit?");
        scanf("%c", &buf);
        if (buf == 'q' || buf == 'Q')
            break;
    }
    return 0;
}

// 変換法で指数分布に従う乱数生成
double expdev(double ave) /* 指数分布の平均値 (ave = 1/alpha) */
{
    double x, r;
    // 一様な乱数生成
    r = (double)rand() / (RAND_MAX + 1.0); /* generates a random value [0, 1) */
    //指数分布の分布関数の逆関数で変換し，指数分布に従う乱数xを生成．
    return -ave * log(1 - r);
}