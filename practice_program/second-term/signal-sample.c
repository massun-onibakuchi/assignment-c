#include <stdio.h>
#include <stdlib.h> /* for exit */
#include <signal.h> /* for signal */

int main()
{
    int i;
    void sigmsg(void); /* function called after signal is detected */

    /* signal setting */
    if (signal(SIGINT, (void *)sigmsg) == SIG_ERR)
    { /* SIGINT --> "sigmsg" is called */
        /* in case of error */
        perror("signal");
        exit(1);
    }

    for (i = 0; i < 20; i++)
    {
        sleep(1); /* sleep for 1 sec */
        printf("%2d: sleeping...\n", i);
        fflush(NULL);
    }

    return 0;
}

void sigmsg(void)
{
    printf("*** Interrupted !! ***\n");
}