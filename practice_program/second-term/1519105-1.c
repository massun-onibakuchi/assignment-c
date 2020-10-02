#include <stdio.h>

/** 
 *  @brief number.dataを読み込み，バブルソートを行い結果をプリント
 */

/** 
 * @param (*array) ソート対象の配列
 * @param　(length) 配列の長さ
 */
int bubble_sort(float *array, int length)
{
  // swap時に一時的に値を持たせる変数
  float temp;
  int i, j;
  for (i = 0; i < length - 1; i++)
  {
    //後方から2要素ずつ比較して入れ替える
    for (j = length - 1; j > i; j--)
    {
      if (array[j - 1] > array[j])
      {
        //swap
        temp = array[j];
        array[j] = array[j - 1];
        array[j - 1] = temp;
      }
    }
  }
  return 0;
}

/**
 * @param (data) 読み込んだデータを入れる変数
 * @param  (filename) ファイル名
 * @return 読み込んだ列数
 */
int read_file(float *data, char *filename)
{
  // float data[1024];
  int i, num;
  FILE *fd;
  fd = fopen(filename, "r");
  i = 0;
  while (fscanf(fd, "%f", &(data[i])) != EOF)
    i++;
  fclose(fd);
  return i;
}

int main(void)
{
  /* ----Read File----- */
  float data[1024];
  int length = read_file(data, "numbers.dat");

  /* ----sort----- */
  bubble_sort(data, length);

  /* -----print result----- */
  printf("After sorting\n");
  int k = 0;
  while (k < length)
  {
    printf("data[%d]:%f\n", k, data[k]);
    k++;
  }

  return 0;
}
