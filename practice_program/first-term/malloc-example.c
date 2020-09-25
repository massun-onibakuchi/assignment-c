#include <stdio.h>
#include <stdlib.h> // malloc を使うのに必要
#include <string.h>

int test();

/* person 構造体の宣言 */
struct person
{
    int id;
    char name[32];
    struct person *link;
};

int main()
{
    int hoge = 12;
    char name[4] = "Tom";
    // 領域確保
    /* 構造体のポインタを代入する変数宣言 */
    /* 動的領域確保してポインタをxに代入 */
    struct person *x;
    x = (struct person *)malloc(sizeof(struct person));
    //これに等しい
    // struct *x = (struct person *)malloc(sizeof(struct person));
    /* 構造体の値の代入 */
    //等価
    // x->id= 1
    // *    x.idと意味が全く違う
    (*x).id = hoge;
    /* 構造体の値の代入(文字列コピーの関数を使用) */
    strcpy((*x).name, name);
    printf("id=%d, name=%s\n", (*x).id, (*x).name);
    /* もう使わないことが確実な場合に限り、動的に確保した領域を解放する */
    free(x);
    test();
    return 0;
}
struct point
{
    int x;
    int y;
};

int test()
{
    struct point *pp;
    pp = (struct point *)malloc(sizeof(struct point)); //#1
    pp->x = 12;
    pp->y = 34;
    printf("x = % d, y = % d\n", pp->x, pp->y);
    free(pp);
    return 0;
}
