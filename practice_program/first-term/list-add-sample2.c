#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person
{
    int id;
    char name[32];
    struct person *next; //次のリストの要素
};

/**
 * @param () 構造体のポインタ
 * @param (int)
 * @param (char *)
 */
struct person *list_add(struct person *list, int id, char name[])
{
    // 新しい要素を作成
    struct person *new = (struct person *)malloc(sizeof(struct person));
    new->id = id;
    strcpy(new->name, name);

    /* 次の要素がないことを示すために NULL を代入 */
    new->next = NULL;

    if (list == NULL)
    {
        /* リストが空の場合は特別扱いする */
        return new;
    }
    else
    {
        /* リストの末尾の要素を探す */
        struct person *p = list;
        while (p->next != NULL)
        {
            p = p->next;
        }
        /* ここで変数 p は末尾の要素をさす */
        p->next = new;
        return list;
    }
}

int main()
{
    int i = 1;
    char buf[32];
    struct person *list = NULL;
    while (1)
    {
        //標準入力
        printf("ID ?>\n");
        scanf("%d", &i);
        if (i <= 0)
            break;
        printf("Name ?>\n");
        scanf("%s", buf);

        // リストに追加する
        list = list_add(list, i, buf);
        struct person *element = list;
        while (element != NULL)
        {
            printf("[%d],%s\n", element->id, element->name);
            element = element->next;
        }
    }
    return 0;
}