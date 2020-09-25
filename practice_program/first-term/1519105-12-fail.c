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
    struct person *root = NULL; /* リスト構造の最初の構造体へのポインタを覚えておく変数 root */
    struct person *new, *current, *head;
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
        new = (struct person *)malloc(sizeof(struct person));
        new->id = i;
        strcpy(new->name, buf);
        new->link = NULL;
        /* NULLの実体は整数の0. 何もないことを強調するため0でなくNULLを使った. */

        /* リスト構造につなぐ処理:新しいデータは、リストの最初に追加する */
        /* rootには、常にリストの最初の構造体のポインタを格納 */
        if (root == NULL)
        {
            /* まだrootに何もない時 */
            root = new;
        }
        else
        {
            /* root にすでにデータが保存されている時 */
            //rootはこのwhileループの前で追加されたかつて(現在のループの１つ前）のnewを参照するポインタ
            new->link = root;
            root = new;
            current = root; //current は新しいやつ new
            while (current != NULL)
            {
                printf("[%d] %s\n", current->id, current->name);
                current = current->link;
            }
        }

        if (head == NULL)
        {
            head = new;
        }
        
        while (head->link != NULL)
        {
            head = head->link;
        }
    }
}