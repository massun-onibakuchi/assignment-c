#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define winMessage "勝ち"
#define lossMessage "負け"

int *prompt(char *buffer)
{
    char *buf[32]; // NULL文字入れて32文字以内
    printf("input >\n ");
    fgets(buf, 32, stdin); // 空白も含めて入力
    printf("% s\n", buf);  // 配列bufに記憶されたデータを文字列として表示
    return buf;
}

int main(void)
{
    while (1)
    {
        char buffer[32];
        int hand = prompt(buffer);
        printf("あなた:%d\n", hand);
        int comHand = genHand();
        printf("コンピュータ:%d\n", comHand);
        if (hand == 3)
        {
            printf("お手つきです\n");
            return 0;
        }

        if (comHand == hand)
        {
            printf("あいこ\n");
        }
        else
        {
            char *message;
            if (comHand == 0)
            {
                message = (hand == 2) ? winMessage : lossMessage;
            }
            if (comHand == 1)
            {
                message = (hand == 0) ? winMessage : lossMessage;
            }
            if (comHand == 2)
            {
                message = (hand == 1) ? winMessage : lossMessage;
            }
            printf("あなたの%sです\n", message);
            break;
        }
    }
}
