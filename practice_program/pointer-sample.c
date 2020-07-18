#include <stdio.h>

int keisan(float *, int);
int main()
{
    float x[5];
    int i;
    for (i = 0; i < 5; i++)
        x[i] = (float)i;
    keisan(x, 5);
    for (i = 0; i < 5; i++)
        printf("x[%d]=%f ", i, x[i]);
    printf("\n");

   
}
int keisan(float *a, int n)
{
    int i;
    for (i = 0; i < n; i++)
        *(a + i) = *(a + i) * *(a + i);
}