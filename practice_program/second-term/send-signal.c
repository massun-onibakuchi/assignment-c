#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>

int main(int argc, char *argv[])
{
    int  i;

    if (argc > 1) sscanf(argv[1], "%d", &i);
    kill(i, SIGINT);
    return 0;
}