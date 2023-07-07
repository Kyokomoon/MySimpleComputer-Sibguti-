#include "myTerm.h"
#include "myBigChars.h"
#include "mySimpleComputer.h"
#include <stdio.h>
#include <stdlib.h>
//#include "myInterface.h"
#include <sys/ioctl.h>
#include <unistd.h>

// enum colors{
//	BLACK=0,RED,GREEN,YELLOW,BLUE,VIOLET,LIGHT_BLUE,WHITE
//};
int
mt_clrscr (void)
{
  write (1, "\E[H\E[J", 8);
  return 0;
}

int
mt_gotoXY (int x, int y)
{
  char buf[12];
  int i;
  for (i = 0; i < 12; i++)
    {
      buf[i] = '\0';
    }
  sprintf (buf, "\E[%d;%dH", x, y);
  write (1, buf, 12);
  return 0;
}

int
mt_getscreensize (int *rows, int *cols)
{
  struct winsize wz;
  if (!ioctl (1, TIOCGWINSZ, &wz))
    {
      *rows = wz.ws_row;
      *cols = wz.ws_col;
      return 0;
    }
  else
    return -1;
}
int
mt_setfgcolor (enum colors color)
{
  char buf[8];
  if (color >= 0 && color <= 7)
    {
      sprintf (buf, "\E[3%dm", color);
      write (1, buf, 8);
      return 0;
    }
  else
    return -1;
}
int
mt_setbgcolor (enum colors color)
{
  char buf[8];
  if (color >= 0 && color <= 7)
    {
      sprintf (buf, "\E[4%dm", color);
      write (1, buf, 8);
      return 0;
    }
  else
    return -1;
}
