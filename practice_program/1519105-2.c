#include <stdio.h>
int main(void)
{
    int yearInput;
    // 入力をさせる
    scanf("西暦1912-2020の間を入力せよ> %d", &yearInput);
    // 1912-2020以外の西暦は再度入力を促す
    while (yearInput < 1912 || yearInput > 2020)
    {
        printf("%d 範囲外です\n", &yearInput);
        scanf("西暦1912-2020の間を入力せよ> %d\n", &yearInput);
    }

    // 上と同じと思われる
    /*     int yearInput;
        while (1)
    {
        scanf("西暦1912-2020の間を入力せよ> %d\n", &yearInput);
        if (yearInput >= 1912 && yearInput <= 2020){
            break;
        }
        printf("%d 範囲外です\n", &yearInput);
    } */

    // 上の時点で1912-2020であるので1926未満であることを確かめる
    if (yearInput < 1926)
    {
        // 年号表記を計算して出力
        printf("%dは大正&d年\n", &yearInput, &yearInput - 1911);
    }

    // 上の時点でyearInputは1926-2020であるので1989未満であることを確かめる
    if (yearInput < 1989)
    {
        // 年号表記を計算して出力
        printf("%dは昭和&d年\n", &yearInput, &yearInput - 1925);
    }

    if (yearInput < 2019)
    {
        // 年号表記を計算して出力
        printf("%dは平成&d年\n", &yearInput, &yearInput - 1988);
    }

    //elseでもいい
    if (yearInput < 2021)
    {
        // 年号表記を計算して出力
        printf("%dは令和&d年\n", &yearInput, &yearInput - 2018);
    }
    printf("年号計算終わり");
    return 0;
}
