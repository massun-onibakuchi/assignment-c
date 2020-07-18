#include <stdio.h>

int main(void)
{
    char *words[11] = {"I ",
                       "you ",
                       "do ",
                       "have ",
                       "pen ",
                       "apple ",
                       "a/an ",
                       "? "};
    int i;
    char numChar[32], *cpWords[11];

    //選択肢の単語を番号と共に表示
    for (i = 0; words[i] != (char *)0; i++)
    {
        printf("(%d)%s ", i, words[i]);
    }

    // printf("(%d) %c", 1, *(words[1] + 0)); 
    // printf("(%d) %s", 1, *(words + 1));   

    printf("\n");
    printf("Input number>\n");
    scanf("%s", numChar);

    // 入力された番号に従って、配列wordsに記憶されたポインタを、ポインタ配列cpWordsにコピーする
    for (i = 0; numChar[i] != '\0'; i++)
    {
        // '0'は(int)48なのでその分を引いて帳尻を合わせることで
        // numChar[i]-48は0,1,2,,,と0からのインデックスとなる.
        //ポインタを代入
        cpWords[i] = words[numChar[i]-48];
    }

    // cpWordsに格納されたポインタをもとに文字列を表示
    for (i = 0; cpWords[i] != (char *)0; i++)
    {
        printf("%s", cpWords[i]);
    }
    printf("\n");
}
