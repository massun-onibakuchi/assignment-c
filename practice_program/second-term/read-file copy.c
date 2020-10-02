#include <stdio.h>
int readFile(char *filename)
{
  float data[1024];
  int i, num;
  FILE *fd;
  fd = fopen(filename, "r");
  i = 0;
  while (fscanf(fd, "%f", &(data[i])) != EOF)
    i++;
  fclose(fd);

  i = 0;
  while ( data[i] != 0.0 )
  {
    /* code */
    printf("%d,%f\n", i,data[i]);
    i++;
  }

  return data;
}
