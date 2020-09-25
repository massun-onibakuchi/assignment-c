#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define winMessage "勝ち"
#define lossMessage "負け"

int doJanken(void);

/** 入力をプロンプトする 0,1,2をグチパに対応.それ以外なら3を返す
 * 0,1,2，3を返す
 */
int prompt()
{
    int hand;
    printf("(0)ぐー (1)チョキ (2)パー\n");
    scanf("%d", &hand);
    if (hand >= 3)
    {
        printf("Invalid hand:");
        return 3;
    }
    return hand;
}

/* コンピュータのグチパをらんダム生成する 0，1，2のいずれを返す */
int genHand(void)
{
    srand((unsigned)time(NULL));
    return rand() % 3;
}

/* ユーザーをコンピュータの手を引数にとりユーザーが勝ちか負けかを返す
勝ちなら"勝ち"
負けなら"負け"を返す */
char *judge(int comHand, int userHand)
{
    char *notif;

    if (comHand == 0)
        notif = (userHand == 2) ? winMessage : lossMessage;
    if (comHand == 1)
        notif = (userHand == 0) ? winMessage : lossMessage;
    if (comHand == 2)
        notif = (userHand == 1) ? winMessage : lossMessage;
    return notif;
}

int doJanken(void)
{
    int result = 0;
    while (result == 0)
    {
        int hand = prompt();
        int comHand = genHand();
        printf("あなたの手:%d\n", hand);
        printf("コンピュータの手:%d\n", comHand);

        // 0,1,2,以外の数字をユーザーが入れた場合終了
        if (hand == 3)
        {
            printf("お手つきです\n");
            return 0;
        }

        // あいこの時
        if (comHand == hand)
        {
            printf("あいこ\n");
        }
        else
        {
            // あいこではないとき
            char *message = judge(comHand, hand);
            printf("あなたの%sです\n", message);
            break;
        }
    }
}
