#include <stdio.h>
#include <string.h>

int main(void)
{
    //　標準入力での文字列を格納
    char string[31];
    printf("Input strings>\n");
    scanf("%s", string);

    // "end"と一致ならば，return  して終了
    if (!strcmp(string, "end"))
    {
        printf("endゆえに終了\n");
        return 0;
    }

    //  flag が立っている 1 なら，数字が文字列に存在することを表す
    int flag = 0;
    int length = strlen(string);

    // ループで各文字を回って,文字が数字であるなら，出力してflagを立てる
    for (int idx = 0; idx <= length; idx++)
    {

        // '0'-'9'の数字であるならば，出力する．flagを1にする
        if (string[idx] >= '0' && string[idx] <= '9')
        {
            printf("%c", string[idx]);
            flag = 1;
        }
    }

    if (flag == 0)
    {
        printf("数字を含まない文字列である．%s\n", string);
    }

    return 0;
}
