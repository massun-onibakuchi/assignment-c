#include <stdio.h>
// 別の方法;
// http://zhi-ma.hatenablog.com/entry/2013/10/11/183906
// ＊＊＊＊＊＊うまくいかない＊＊＊＊＊＊
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
    // (ビルトイン関数を使えばよいが，)
    // length:= 変数in の長さ
    int length = strLength(in);
    // outに変数inの要素を逆順に代入
    for (i = 0; in[i] != '\0'; i++)
    {
        *(out + i) = *(in + length - 1 - i);
        // 下と同義
        // out[i] = in[length - 1 - i];
    }
}

int dev_rev(char *in_out)
{
    int i;
    char cpWords[32];
    int length = strLength(in_out);
    // cpWordにコピーする


    // in_outに変数cpWordsの要素を逆順に代入
    for (i = 0; in_out[i] != '\0'; i++)
    {
        *(in_out + i) = cpWords[length - 1 - i];
    }
}

// 文字列の長さを返す
int strLength(char *str)
{
    int length = 0;
    while (str[length] != '\0')
    {
        length++;
    }
    return length;
}
