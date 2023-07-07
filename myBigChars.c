#include "myBigChars.h"
#include "myTerm.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <unistd.h>
int
bc_printA (char *str)
{
  if (!str)
    return -1;
  int n = 0;
  while (str[n] != '\0')
    {
      n++;
      if (n > 200)
        {
          printf ("err");
          return -1;
        }
    }
  char *buf = (char *)malloc (sizeof (char) * (n + 7));
  sprintf (buf, "\E(0%s\E(B", str);
  write (1, buf, n + 7);
  free (buf);
  return 0;
}

int
bc_box (int x1, int y1, int x2, int y2)
{
  int i, pov = 0;
  int maxx, maxy;
  mt_getscreensize (&maxy, &maxx);
  if ((x1 < 0) || (y1 < 0) || (x2 > maxx) || (y2 > maxy) || (x2 - x1 < 2)
      || (y2 - y1 < 2))
    return -1;
  mt_gotoXY (y1, x1);
  bc_printA ("l");

  for (i = 1; i < x2 - x1; i++)
    {
      bc_printA ("q");
    }

  bc_printA ("k");

  mt_gotoXY (y2, x1);
  bc_printA ("m");

  for (i = 1; i < x2 - x1; i++)
    {
      bc_printA ("q");
    }
  bc_printA ("j");
  for (i = 1; i < y2 - y1; i++)
    {
      mt_gotoXY (y1 + i, x1);
      bc_printA ("x");
    }
  for (i = 1; i < y2 - y1; i++)
    {
      mt_gotoXY (y1 + i, x2);
      bc_printA ("x");
    }
  return 0;
}
int
bc_printbigchar (int num[2], int x, int y, enum colors color1,
                 enum colors color2)
{
  int x1 = num[0], x2 = num[1], ob, raz, i, j;
  int maxx, maxy;
  mt_getscreensize (&maxy, &maxx);
  mt_setfgcolor (color1);
  mt_setbgcolor (color2);
  mt_gotoXY (y, x);
  if ((x < 0) || (y < 0) || (x + 8 > maxx) || (y + 8 > maxy))
    return -1;
  for (i = 1; i <= 4; i++)
    {
      if (i != 1)
        x1 = x1 >> 8;
      ob = (x1);
      for (j = 0; j < 8; j++)
        {
          if (j != 0)
            ob = ob >> 1;
          raz = ob % 2;
          if (raz == 0)
            {
              write (1, " ", 1);
            }
          else
            bc_printA ("a");
        }
      y += 1;
      mt_gotoXY (y, x);
    }
  for (i = 1; i <= 4; i++)
    {
      if (i != 1)
        x2 = x2 >> 8;
      ob = (x2);
      for (j = 0; j < 8; j++)
        {
          if (j != 0)
            ob = ob >> 1;
          raz = ob % 2;
          if (raz == 0)
            {
              write (1, " ", 1);
            }
          else
            bc_printA ("a");
        }
      y += 1;
      mt_gotoXY (y, x);
    }
  return 0;
}
int
bc_setbigcharpos (int *big, int x, int y, int value)
{
  if ((x < 0 || x > 7) || (y < 0 || y > 7))
    {
      return -1;
    }
  if (y < 4)
    {
      if (value == 0)
        {
          big[0] = ~((1 << ((y % 4) * 8 + x)) & big[0]) & big[0];
        }
      else
        big[0] = (1 << ((y % 4) * 8 + x)) | big[0];
    }
  else
    {
      y -= 4;
      if (value == 0)
        {
          big[1] = ~((1 << ((y % 4) * 8 + x)) & big[1]) & big[1];
        }
      else
        big[1] = (1 << ((y % 4) * 8 + x)) | big[1];
    }
  return 0;
}
int
bc_getbigcharpos (int *big, int x, int y, int *value)
{
  if ((x < 0 || x > 7) || (y < 0 || y > 7))
    {
      return -1;
    }
  if (y < 3)
    {
      *value = (1 << ((y % 4) * 8 + x)) & big[0];
    }
  else
    {
      *value = (1 << ((y % 4) * 8 + x)) & big[1];
    }
  return 0;
}
int
bc_bigcharwrite (int fd, int *big, int count)
{
  int res_w;
  res_w = write (fd, big, count * 2 * sizeof (int));
  if (res_w == -1)
    return -1;
  return 0;
}
int
bc_bigcharread (int fd, int *big, int need_count, int *count)
{
  int res_w;
  res_w = read (fd, big, 18 * 2 * sizeof (int));
  if (res_w == -1)
    return -1;
  return 0;
}
