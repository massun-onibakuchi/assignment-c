#include <stdio.h>

/** 
 *  @brief 整数の階乗を返す
 */

/** 
 * 引数に与えられた整数の階乗を返す
 */
int factorial(int num)
{
  // if (num == 1)
  //   return num;
  // else
  //   return num * factorial(num - 1);
  return (num == 1) ? 1 : num * factorial(num - 1);
}

int main(void)
{
  int n;
  printf("Input an integer> \n");
  scanf("%d", &n);
  int result = factorial(n);
  printf("Result : %d\n", result);
  return 0;
}
