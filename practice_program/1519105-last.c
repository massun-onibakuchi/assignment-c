#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define doYou "do you"
#define janken "janken"
#define who "who"
#define hello "hello"
#define I "I "
#define like "like"
#define eat "eat"
#define introduction "I am party Parrott"
#define confusedMessage "I am sorry. I don’t know"

int prompt(char *buffer)
{
    // char *buf[32]; // NULL文字入れて32文字以内
    printf("input >\n ");
    fgets(buffer, 32, stdin); // 空白も含めて入力
    // 配列bufに記憶されたデータを文字列として表示
    // return buffer;
}

int main(void)
{
    while (1)
    {
        enum QuestionType
        {
            doQuestion,
            whoQuestion,
            letJanken,
            helloQuestion,
            other
        };

        char wordsTable[3][10] = {doYou, who, janken, hello};

        enum QuestionType type = other;

        /* --------ユーザー入力------------------ */

        char buffer[32];
        prompt(buffer);
        printf("コンピュータ:%s\n", buffer);

        /* --------ユーザー入力------------------ */

        for (int i = 0; i < other; i++)
        {
            char *key = strstr(buffer, wordsTable[i]);
            // printf("wordTable[i]:%s\n", wordsTable[i]);
            if (key != NULL)
            {
                type = i;
                break;
            }
        }
        //key word: do you
        // printf("コンピュータ:%d\n", type);
        if (type == doQuestion)
        {
            respond(buffer);
        }

        if (type == whoQuestion)
        {
            printf("コンピュータ> %s", introduction);
        }

        //  じゃんけんする
        if (type == letJanken)
        {

        }

        if (type == helloQuestion)
        {
            printf("コンピュータ> %s", hello);
            printf("コンピュータ> %s", introduction);
        }

        if (type == other)
        {
            printf("コンピュータ> %s", confusedMessage);
        }
    }
}

int respond(char buffer)
{
    char wordsTable[2][10] = {like, eat};
    for (int i = 0; i < 2; i++)
    {
        char *key = strstr(buffer, wordsTable[i]);
        // printf("wordTable[i]:%s\n", wordsTable[i]);
        if (key != NULL)
        {
            printf("コンピュータ>%s%s", I, key);
            return;
        }
    }
    printf("コンピュータ>%s", confusedMessage);
}
