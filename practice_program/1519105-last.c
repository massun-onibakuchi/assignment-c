#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define DOYOU "do you"
#define JANKEN "janken"
#define WHO "who"
#define HELLO "hello"
#define I "I "
#define LIKE "like"
#define EAT "eat"
#define INTRODUCTION "I am party Parrott"
#define CONFUSEDMESSAGE "I am sorry. I don’t know"

int doJanken(void);

int prompt(char *buffer)
{
    // char *buf[32]; // NULL文字入れて32文字以内
    printf("Input >\n ");
    fgets(buffer, 32, stdin); // 空白も含めて入力
    // 配列bufに記憶されたデータを文字列として表示
    // return buffer;
}

int respond(char *buffer)
{
    char wordsTable[2][10] = {LIKE, EAT};
    for (int i = 0; i < 2; i++)
    {
        char *key = strstr(buffer, wordsTable[i]);
        // printf("wordTable[i]:%s\n", wordsTable[i]);
        if (key != NULL)
        {
            printf("コンピュータ>%s%s\n", I, key);
            return 0;
        }
    }
    printf("コンピュータ>%s\n", CONFUSEDMESSAGE);
}

int main(void)
{
    // 入力された質問のタイプ
    enum QuestionType
    {
        doQuestion,
        whoQuestion,
        letsJanken,
        helloQuestion,
        other
    };

    //　検索キーワード
    char wordsTable[4][10] = {DOYOU, WHO, JANKEN, HELLO};

    enum QuestionType type;

    while (1)
    {

        /* --------------ユーザー入力------------------ */
        //ユーザー入力文字列
        char buffer[32];
        prompt(buffer);
        // デフォルト other
        type = other;

        /* ----------キーワードに会う文字列探索する----------- */
        for (int i = 0; i < other; i++)
        {
            char *key = strstr(buffer, wordsTable[i]);
            if (key != NULL)
            {
                type = i;
                break;
            }
        }

        /* ----------リアクションする--------- */
        // どのキーワードにも当てはまらない時
        if (type == other)
        {
            printf("コンピュータ> %s\n", CONFUSEDMESSAGE);
            continue;
        }

        //key word: do you
        if (type == doQuestion)
        {
            respond(buffer);
        }

        if (type == whoQuestion)
        {
            printf("コンピュータ> %s!! %s\n", HELLO, INTRODUCTION);
        }

        //  じゃんけんする
        if (type == letsJanken)
        {
            printf("コンピュータ> Ok,Let's play janken\n");
            doJanken();
        }

        if (type == helloQuestion)
        {
            printf("コンピュータ> %s\n", HELLO);
            printf("コンピュータ> %s\n", INTRODUCTION);
        }
    }
}
