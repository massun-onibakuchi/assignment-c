#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <curses.h>

int main()
{
  int x = COLS / 2, y = LINES / 2;
  int ch;
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  while (1)
  {
    mvaddch(y, x, '*');
    move(y, x);
    refresh();
    ch = getch();
    // delch();     /* 文字を消す */
    clear(); // 画面をクリアする。端末コマンドからクリアするのでeraseより確実らしい
    switch (ch)
    {
    case KEY_LEFT:
    case 'h':
      x -= 2;
      break;
    case KEY_RIGHT:
    case 'l':
      x += 2;
      break;
    case KEY_UP:
    case 'k':
      y--;
      break;
    case KEY_DOWN:
    case 'j':
      y++;
      break;
    case 'q':
      x = 999;
    }
    if (x == 999)
      break;
    x = (x + COLS) % COLS;   /* 必ず 0～COLS-1 に納める */
    y = (y + LINES) % LINES; /* 必ず 0～LINES-1 に納める */
  }
  endwin();
}
