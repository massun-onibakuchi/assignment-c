#include <stdio.h>

/** 
 *  @brief nCrを計算する
 */

int _combi(int, int);
int combi(int, int);

/** 
 * 引数に与えられたn,rのテェックをせずにnCrを返す
 */
int _combi(int n, int r)
{
  if (r == 0 || n == r)
    return 1;
  if (r == 1)
    return n;
  else
    return (r > n - r) ? _combi(n - 1, n - r) + _combi(n - 1, n - r - 1) : _combi(n - 1, r) + _combi(n - 1, r - 1);
  // nCr=nCn-rを使って計算が短く済むようにする
  // return ((r > n - r) ? _combi(n - 1, n - r) : _combi(n - 1, r - 1)) + ((r > n - r - 1) ? _combi(n - 1, n - r - 1) : _combi(n - 1, r));
  // 複数のラインで書いたもの
  // int term1 = (r > n - r) ? _combi(n - 1, n - r) : _combi(n - 1, r - 1);
  // int term2 = (r > n - r - 1) ? _combi(n - 1, n - r - 1) : _combi(n - 1, r);
  // return term1 + term2;
}

/** 
 * 引数に与えられたn,rにいくつかのテェックしてからnCrを返す
 */
int combi(int n, int r)
{
  // r>nなら弾く
  if (r > n)
  {
    printf("INVALID: r is greater than n.");
    return 0;
  }
  return _combi(n, r);
}

/** 
 * 引数の関数を1-19の整数で実行し，その結果を表示する
 * @param (n) ループ回数
 * @param (*func(int)) 
 */
void loop_test(int n, int (*func)(int, int))
{

  printf(
      "----calculate n=%d nCr-----\n"
      "----test-----\n"
      "r nCr\n",
      n);
  for (int r = 0; r <= n; r++)
  {
    printf("%d %d\n", r, func(n, r));
  }
  printf("----test-----\n");
}

void main(void)
{
  //入力された数字
  int n, r;
  printf("Input an integer n and r  >\n");
  scanf("%d,%d", &n, &r);

  //nCrを計算
  int result = combi(n, r);
  // 示す
  printf("Result : %d\n", result);

  // nを定数とした時の全部のrでnCrを計算した結果を表示する
  loop_test(n, combi);
}