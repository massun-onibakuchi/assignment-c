#include <stdio.h>
int main(void)
{
    int inputNum;
    // test用
    // inputNum = 28;

    // 適切な数値を入れてくれるまで繰り替えす
    while (1)
    {
        scanf("%d", &inputNum);
        if (inputNum > 1)
        {
            break;
        }
        printf("%d範囲外です\n", inputNum);
    }
    int num = inputNum;

    //for バージョン
    int modNum;
    printf("%d 入力した数: \n", num);
    /*  for (modNum = 2; mod <= n; modNum++)
     よりも以下の方が効率的 
     */
    for (modNum = 2; num != 1; modNum++)
    {
        //modNumとnumが互いに素になるまで割り，
        // 一回ごとにmodNum素因数を出力
        while (num % modNum == 0)
        {
            num /= modNum;
            printf("%d　", modNum);
        }
    }

    // whileバージョン
    /* 
    > 28なら
    2*2*7と「＊』を挟んで返す
     */
    int mod = 2;
    num = inputNum;

    // 最後だけprintfで「x」を入力しないようにするため
    // num == modとなったら終わらせる
    while (num != mod)
    {
        // modと互いに素になるまでnumを割り，
        // 一回ごとにmodNum素因数を出力
        if (num % mod == 0)
        {
            num /= mod;
            printf("%dx", mod);
        }
        else
        {
            mod++;
        }
    }

    printf("%d\n", mod);

    printf("\n計算終わり\n");
    return 0;
}
