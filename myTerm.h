
enum colors
{
  BLACK = 0,
  RED,
  GREEN,
  YELLOW,
  BLUE,
  VIOLET,
  LIGHT_BLUE,
  WHITE
};

int mt_clrscr (void);
int mt_gotoXY (int x, int y);
int mt_getscreensize (int *rows, int *cols);
int mt_setfgcolor (enum colors color);
int mt_setbgcolor (enum colors color);
