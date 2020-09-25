#include <stdio.h>

int main(void)
{
    // char[]の宣言　127文字まで格納できる
    char string[127] = "\0";

    /* stringの初めの文字が '=' ではない　かつ　'!'ではない
    ということを評価する 
     */
    while (string[0] != '=' && string[0] != '!')
    {

        // ヌル文字が出るまでループを回し,
        // 文字に対応する文字コードを出力する
        int i = 0;
        // ヌル文字であるか評価
        while (string[i] != '\0')
        {
            printf("%d　", string[i]);
            i++;
        }

        // ユーザーに入力をさせる
        printf("\nInput strings>\n");
        scanf("%s", string);
    }
    printf("終わり\n");
    return 0;
}
