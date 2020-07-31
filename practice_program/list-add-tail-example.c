#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person
{
    int id;
    char name[32];
    struct person *next; //次のリストの要素
};

int command()
{
    int number;
    scanf("%d", number);
    if (number > 3)
    {
        printf("Invalid number");
        return 2;
    }
    return number;
}

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

int *append(struct person *list)
{
    int i = 1;
    char buf[32];
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
        display_list(list);
    }
}

int *display(struct person *list)
{
    struct person *element = list;
    while (element != NULL)
    {
        printf("[%d],%s\n", element->id, element->name);
        element = element->next;
    }
}
/** 
* メイン
 */
int main()
{
    int i = 1;
    char buf[32];
    struct person *list = NULL;
    int com = command();
    if (com == 0)
        display(list);
    if (com == 1)
        append(list);
    if (com == 2)
        printf("end\n");
    return 0;
}