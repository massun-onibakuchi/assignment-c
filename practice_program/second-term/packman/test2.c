#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <curses.h>

#define PLAYER "\x1b[44m  \x1b[49m"
#define ENEMY "\x1b[41m  \x1b[49m"

void init_curses()
{
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    timeout(0);
}

int mv_entity(int *ch, int *x, int *y)
{
    switch (*ch)
    {
    case KEY_LEFT:
    case 'h':
    case 's':
        *x = *x - 2;
        break;
    case KEY_RIGHT:
    case 'l':
    case 'f':
        *x = *x + 2;
        break;
    case KEY_UP:
    case 'k':
    case 'e':
        (*y)--;
        break;
    case KEY_DOWN:
    case 'j':
    case 'd':
        (*y)++;
        break;
    case 'q':
        *x = 999;
    }
    if (*x == 999)
        return 0;
    *x = (*x + COLS) % COLS;   /* 必ず 0～COLS-1 に納める */
    *y = (*y + LINES) % LINES; /* 必ず 0～LINES-1 に納める */
    return 1;
}
int main()
{
    int x = COLS / 2, y = LINES / 2;
    int ch = 'l';
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    timeout(0);

    int posi_x = 0;
    while (1)
    {
        refresh();
        // mvaddstr(y, x, PLAYER);
        mvprintw(2, 2, "AA");
        posi_x++;
        mvaddstr(2, posi_x, "ASS");
        // move(y, x);
        mvaddch(y, x, '*');
        ch = getch();
        //   delch(); /* 文字を消す */
        clear();

        mv_entity(&ch, &x, &y);
        posi_x = (posi_x + COLS) % COLS;

        usleep(100000);
    }
    endwin();
}