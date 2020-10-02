#include <stdio.h>
int main(void) {
  float data[512];
  int i, num;
  FILE *fd;
  fd = fopen("numbers.dat", "r");
  i = 0;
  while (fscanf(fd, "%f", &(data[i])) != EOF)
    i++;
  fclose(fd);
  return 0;
}
