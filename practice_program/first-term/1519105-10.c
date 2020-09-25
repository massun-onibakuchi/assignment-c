#include <stdio.h>
// 別の方法
// http://zhi-ma.hatenablog.com/entry/2013/10/11/183906
int rev(char *in, char *out);
int dev_rev(char *in_out);
int strLength(char *str);
int main(void)
{
    char in[32], out[32];
    printf("Input >\n");
    scanf("%s", in);

    // 逆順にする
    rev(in, out);
    printf("out :%s\n", out);

    //逆順にする
    dev_rev(out);
    printf("out :%s\n", out);
    return 0;
}

int rev(char *in, char *out)
{
    int i;
    int strlength = 0;
    while (in[strlength] != '\0')
    {
        strlength++;
    }
    for (i = 0; in[i] != '\0'; i++)
    {
        // outに変数inの要素を逆順に代入
        *(out + i) = *(in + strlength - 1 - i);
        // 下と同義
        // out[i] = in[strlength - 1 - i];
    }
}

int dev_rev(char *in_out)
{
    int i;
    int last = 0;
    char cpWords[32];
    while (in_out[last] != '\0')
    { 
        // in_outを変数cpWordsにコピー
        cpWords[last] = in_out[last];
        last++;
    }
    for (i = 0; in_out[i] != '\0'; i++)
    {
        // in_outに変数cpWordsの要素を逆順に代入
        *(in_out + i) = cpWords[last - 1 - i];
    }
}
