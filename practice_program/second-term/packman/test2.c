#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <curses.h>

#define PLAYER "\x1b[44m  \x1b[49m"
#define ENEMY "\x1b[41m  \x1b[49m"

int mv_entity(int *ch, int *x, int *y)
{
    // flash();
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
        *y--;
        break;
    case KEY_DOWN:
    case 'j':
    case 'd':
        *y++;
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
    keypad(stdscr, TRUE);
    timeout(0);
    start_color();
    // init_pair(1, COLOR_RED, COLOR_RED);    //色1に赤文字の赤地をセット
    // bkgd(COLOR_PAIR(1));                   // 色1を背景色に
    init_pair(2, COLOR_WHITE, COLOR_BLUE); //色2に青文字の黒地をセット
    attrset(COLOR_PAIR(2));                // 色2を文字色にセット
    mvprintw(1, 1, "AA");
    int posi_x = 0;
    while (1)
    {
        refresh();
        // mvaddstr(y, x, PLAYER);
        posi_x++;

        // mvaddstr(2, posi_x, "ASS");

        move(y, x);
        mvaddch(y, x, '*');
        ch = getch();

        delch(); /* 文字を消す */
        // flash();
        switch (ch)
        {
        case KEY_LEFT:
        case 'h':
        case 's':
            x -= 2;
            break;
        case KEY_RIGHT:
        case 'l':
        case 'f':
            x = *x + 2;
            break;
        case KEY_UP:
        case 'k':
        case 'e':
            y--;
            break;
        case KEY_DOWN:
        case 'j':
        case 'd':
            y++;
            break;
        case 'q':
            x = 999;
        }
        if (x == 999)
            break;
        x = (x + COLS) % COLS;   /* 必ず 0～COLS-1 に納める */
        y = (y + LINES) % LINES; /* 必ず 0～LINES-1 に納める */
        usleep(100000);
    }
    endwin();
}