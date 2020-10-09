#include <stdio.h>

/** 
 *  @brief 標準入力より整数値n を入力すると、この数列の第n項 の値を計算して示すプログラム
 * a_1 =1,a_2 =1
 * nが3以上の時
 * a_n = a_n-1 + a_n-2
 */

/** 
 * 引数に与えられた整数をnとした時，第n項a_nを返す
 * 
 * index<3の場合　1　を返す
 * それ以外の場合漸化式を実行
 */
int term(int index)
{
  if (index == 0)
    printf("Please enter an integer greater than or equal to 1.");
  if (index < 3)
    return 1;
  else
    return term(index - 1) + term(index - 2);
}

/** 
 * 引数の関数を1-19の整数で実行し，その結果を表示する
 * @param (*func(int)) 
 */
void loop_test(int (*func)(int))
{

  printf("----test-----\n");
  for (int idx = 1; idx < 20; idx++)
  {
    printf("%d\n", func(idx));
  }
  printf("----test-----\n");
}

void main(void)
{
  //入力された数字
  int n;
  printf("Input an integer>\n");
  scanf("%d", &n);

  //数列の第n項の値を計算
  int result = term(n);
  // 示す
  printf("Result : %d\n", result);

  // 1ー19までの整数を全部でtermを実行した結果を表示する
  loop_test(term);
}