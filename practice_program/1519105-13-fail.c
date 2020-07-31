#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person
{
    int id;
    char name[32];
    struct person *link;
};

int main()
{
    int i = 1;
    char buf[32];
    struct person *tail = NULL; /* リスト構造の最初の構造体へのポインタを覚えておく変数 tail */
    struct person *newTail, *head, *current;
    while (1)
    {
        /* データ入力とリスト構造になっている全会員表示を無限に繰り返す(Ctrl-cで終了) */
        /* データ入力(IDと名前を、変数 i と配列 buf の各々にとりあえず保存する) */
        printf("ID ?>\n");
        scanf("%d", &i);
        if (i <= 0)
            break;
        printf("Name ?>\n");
        scanf("%s", buf);
        /* 新しい構造体の要素の作成 */
        newTail = (struct person *)malloc(sizeof(struct person));
        newTail->id = i;
        strcpy(newTail->name, buf);
        newTail->link = NULL;
        /* NULLの実体は整数の0. 何もないことを強調するため0でなくNULLを使った. */

        /* リスト構造につなぐ処理:新しいデータは、リストの最初に追加する */
        /* rootには、常にリストの最初の構造体のポインタを格納 */
        // if (current == NULL)
        // {
        //     /* まだrootに何もない時 */
        //     current = newTail;
        //     head = newTail;
        // }
        if (head == NULL)
        {
            /* まだrootに何もない時 */
            head = newTail;
        }
        else
        {
            /* tail にすでにデータが保存されている時 */
            //rootはこのwhileループの前で追加されたかつて(現在のループの１つ前）のnewを参照するポインタ
            // tail->link = newTail;
            // current = newTail;
            // tail = current;
            tail->link = current;
            current = newTail;
            tail = current;
            while (head != NULL)
            {
                printf("[%d] %s\n", head->id, head->name);
                head = head->link;
            }
        }
    }
}