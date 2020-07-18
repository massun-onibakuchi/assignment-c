#include <stdio.h>
int main(void) {
  int seconds,hour, min,sec;
  // 秒の入力を促す
  scanf("Seconds> %d", &seconds);
  // seconds = 310;
  // 変換される時間をそれぞれ計算
   hour = seconds / 3600;
   min = (seconds%3600)/60;
   sec = seconds %60;
   // 結果を返す
   printf("Hour:min:sec--%d:%d:%d\n", hour, min, sec);
   return 0; 
}
