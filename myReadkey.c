#include "myReadkey.h"
#include "myBigChars.h"
#include "myTerm.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>
struct termios tsaved;
int
rk_readkey (enum keys *key)
{
  char buf[100];
  int i, j, chek = 0;
  char simb[13][6] = { "l",      "s",  "r",    "t",    "i",    "e",   "\E[15~",
                       "\E[17~", "\n", "\E[A", "\E[B", "\E[D", "\E[C" };
  int read_chars;
  if ((read_chars = read (0, buf, 99)) > 0)
    {
      for (i = 0; i < 13; i++)
        {
          chek = 0;
          for (j = 0; j < strlen (simb[i]); j++)
            {
              if (simb[i][j] == buf[j])
                {
                }
              else
                chek = 1;
            }
          if (chek == 0)
            {
              *key = i;
            }
        }
    }
  else
    {
      return -1;
    }
}
int
rk_mytermsave (void)
{

  tcgetattr (0, &tsaved);
}
int
rk_mytermrestore (void)
{
  tcsetattr (0, TCSAFLUSH, &tsaved);
}
int
rk_mytermregime (int regime, int vtime, int vmin, int echo, int sigint)
{
  struct termios tek;
  tcgetattr (0, &tek);
  if (regime == 1)
    {
      tek.c_lflag = tek.c_lflag | ECHO;
      tek.c_lflag = tek.c_lflag | ICANON;
      tcsetattr (0, TCSANOW, &tek);
      return 0;
    }
  else if (regime == 0)
    {
      tek.c_lflag = tek.c_lflag & (~(ICANON));
      if (echo == 1)
        tek.c_lflag = tek.c_lflag | ECHO;
      else
        tek.c_lflag = tek.c_lflag & (~(ECHO));
      tek.c_cc[VTIME] = vtime;
      tek.c_cc[VMIN] = vmin;
      if (sigint == 1)
        tek.c_lflag = tek.c_lflag | ISIG;
      else
        tek.c_lflag = tek.c_lflag & (~(ISIG));
      tcsetattr (0, TCSANOW, &tek);
      return 0;
    }
  else
    return -1;
}
