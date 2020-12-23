#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <curses.h>

#define MAP_CHIP_WIDTH 21
//マップチップのの縦幅
#define MAP_CHIP_HEIGHT 21
#define ENEMY_NUMBER 5
//表示するアイコン
#define ITEM "\x1b[44m\x1b[49m"
#define PLAYER "\x1b[44m  \x1b[49m"
#define ENEMY "\x1b[41m  \x1b[49m"
#define WALL "II"
#define INVISIBLE_WALL "XX"
#define ROAD "  "

void init_curses()
{
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    timeout(0);
}
int map_chip_data[MAP_CHIP_HEIGHT][MAP_CHIP_WIDTH] =
    {
        {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
        {2, 0, 2, 2, 0, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 0, 2, 2, 0, 2},
        {2, 0, 2, 2, 0, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 0, 2, 2, 0, 2},
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
        {2, 0, 2, 0, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 2, 0, 2},
        {2, 0, 2, 0, 2, 2, 0, 2, 3, 3, 3, 3, 3, 2, 0, 2, 2, 0, 2, 0, 2},
        {2, 0, 2, 0, 2, 2, 0, 2, 3, 3, 3, 3, 3, 2, 0, 2, 2, 0, 2, 0, 2},
        {2, 0, 2, 0, 2, 2, 0, 2, 3, 3, 3, 3, 3, 2, 0, 2, 2, 0, 2, 0, 2},
        {2, 0, 2, 0, 2, 2, 0, 2, 3, 3, 3, 3, 3, 2, 0, 2, 2, 0, 2, 0, 2},
        {2, 0, 2, 0, 2, 2, 0, 2, 3, 3, 0, 3, 3, 2, 0, 2, 2, 0, 2, 0, 2},
        {2, 0, 2, 0, 2, 2, 0, 2, 2, 2, 0, 2, 2, 2, 0, 2, 2, 0, 2, 0, 2},
        {2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2},
        {2, 0, 2, 2, 0, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 0, 2, 2, 0, 2},
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
        {2, 0, 2, 0, 2, 2, 2, 2, 0, 2, 2, 2, 0, 2, 2, 2, 2, 0, 2, 0, 2},
        {2, 0, 2, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 2, 0, 2},
        {2, 0, 2, 0, 2, 2, 0, 2, 2, 2, 0, 2, 2, 2, 0, 2, 2, 0, 2, 0, 2},
        {2, 0, 2, 0, 2, 2, 0, 2, 2, 2, 0, 2, 2, 2, 0, 2, 2, 0, 2, 0, 2},
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
        {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
};
// MapChip構造体
struct MapChip
{
    char *icon;
    int id;
    unsigned int position_x;
    unsigned int position_y;
};
struct MapChip map_chip[MAP_CHIP_HEIGHT][MAP_CHIP_WIDTH];
void initMapChip()
{
    for (unsigned int i = 0; i < MAP_CHIP_HEIGHT; i++)
    {
        for (unsigned int j = 0; j < MAP_CHIP_WIDTH; j++)
        {
            map_chip[i][j].id = map_chip_data[i][j];
            if (map_chip[i][j].id == 0)
            {
                map_chip[i][j].icon = ROAD;
            }
            if (map_chip[i][j].id == 2)
            {
                map_chip[i][j].icon = WALL;
            }
            if (map_chip[i][j].id == 3)
            {
                map_chip[i][j].icon = INVISIBLE_WALL;
            }
            map_chip[i][j].position_x = j;
            map_chip[i][j].position_y = i;
        }
    }
}
int mv_entity(int *ch, int *x, int *y)
{
    switch (*ch)
    {
    case KEY_LEFT:
    case 'h':
    case 's':
        *x = *x - 1;
        break;
    case KEY_RIGHT:
    case 'l':
    case 'f':
        *x = *x + 1;
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
    int posi_x = 0;
    init_curses();
    // if (LINES < MAP_CHIP_HEIGHT || COLS < MAP_CHIP_WIDTH)
    //     return 1;
    initMapChip();
    while (1)
    {
        refresh();
        // mvaddstr(y, x, PLAYER);
        mvprintw(2, 2, "AA");
        posi_x++;
        mvaddstr(2, posi_x, "AAA");

        for (unsigned int y = 0; y < MAP_CHIP_HEIGHT; y++)
        {
            for (unsigned int x = 0; x < MAP_CHIP_WIDTH; x++)
            {
                // if (player.position_y == y && player.position_x == x)
                // {
                //     printf("%s", player.icon);
                //     continue;
                // }
                // !printEnemies(enemies, x, y) && printf("%s", map_chip[y][x].icon);
                // move(y,x);
                // printw("%s",map_chip[y][x].icon);
                mvprintw(y, x, map_chip[y][x].icon);
            }
            // printf("\n");
        }
        // printf("\x1b[49m");

        // move(y, x);
        mvaddstr(y, x, "*");
        // mvaddch(y, x, '*');
        ch = getch();
        //   delch(); /* 文字を消す */
        clear();

        mv_entity(&ch, &x, &y);
        posi_x = (posi_x + COLS) % COLS;

        usleep(100000);
    }
    endwin();
}