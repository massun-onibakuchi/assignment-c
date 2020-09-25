#include <stdio.h>
double bbp();

int main(void)
{
    // a_kを第何項まで計算するのかを表す
    int n;
    double pi = 0.0;

    // a_kを第何項まで計算するのかを入力
    printf("digits >\n");
    scanf("%d", &n);

    // 一般項a_kを回して和を計算
    for (int k = 0; k <= n; k++)
    {
        pi += bbp(k);
    }

    // 結果の出力
    printf(" π=%.15f\n", pi);
    //10進数で15桁
    printf("double = %ld bytes \n", sizeof(double));

    return 0;
}

// bbpの第k項を計算する
// 引数k:=項
double bbp(int k)
{
    // coefficient:= 1／16　のk乗
    double coefficient = 1.0;
    for (int i = 0; i < k; i++)
    {
        coefficient /= 16.0;
    }

    // 各項を計算する
    double denominater = 8.0 * k + 1.0;
    double num1 = 4.0 / denominater;
    double num2 = 2.0 / (denominater + 3.0);
    double num3 = 1.0 / (denominater + 4.0);
    double num4 = 1.0 / (denominater + 5.0);

    // 最終的なa_kの結果
    double result = coefficient * (num1 - num2 - num3 - num4);
    printf("bbp()%.15f\n", result);
    return result;
}
