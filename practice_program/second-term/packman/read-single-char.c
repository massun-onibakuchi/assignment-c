#include <stdlib.h>
#include <stdio.h>

char c;

system("/bin/stty raw");
c = tolower(getchar());
system("/bin/stty cooked");