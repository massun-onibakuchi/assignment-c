## C言語　ポインタ
https://qiita.com/nishiwakki/items/6757de7d3e4c1a72d546
https://www.cc.kyoto-su.ac.jp/~yamada/programming/pointer.html
### ポインタ
:=アドレスの値を記憶する変数

 - ポインタ型
 アドレスを格納する型
 - ポインタの値=アドレス
 - ポインタ変数
 int double　の派生みたいな感じ

### %p , &: アドレスを求める演算子  
 - &: アドレス演算子  
`&x`は`x`のメモリ上のアドレスを表す．これを表示するには%pを使って出力する
 - *間接演算子     
 `*p_x`


```c
include <stdio.h>
int main(void)
{
    int x;    /* xはint型の変数 */
    x = 5;    /* 変数xに5を代入 */

    printf("   x:%d\n", x);     /* xの値を表示 */
    printf("  &x:%p\n", &x);    /* xのアドレスを表示 */

    int *p_x;  /* p_xはポインタ変数 */
    p_x = &x;  /* ポインタ変数p_xにxのアドレスを代入 */

    printf(" p_x:%p\n", p_x);   /* p_xの値を表示 */
    printf("*p_x:%d\n", *p_x);  /* *p_xの値を表示 */
    return 0;
}
/*----実行結果------
   x:5
  &x:0x7ffeed0dca38
 p_x:0x7ffeed0dca38
*p_x:5
---------------- */

// 先頭のアドレスから4バイトずつ増加するアドレスが割り当てられる
//配列名は配列の最初の要素のアドレスだから&をつける必要はない

int printCharAddress(void)
{
	int array[10];
	printf("array___(%p)\n",array);//配列名は配列の最初の要素のアドレスだから&をつける必要はない
	printf("array0%d\n",&array[0]);
	printf("array1%d\n",&array[1]);
	printf("array2%d\n",&array[2]);
	return 0;
}

```
