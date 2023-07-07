#include "math.h"
#include "myBigChars.h"
#include "myInterface.h"
#include "myReadkey.h"
#include "mySignal.h"
#include "mySimpleComputer.h"
#include "myTerm.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

int
main ()
{

  srand (time (NULL));
  enum keys key;
  int i, j, adr, val, ret, com, oper, comcode, yach = 0, fd;
  char filename[11] = "memory.dat";
  sc_regInit ();
  Counter = 0;
  sc_accumulator = 0;
  sc_memoryInit ();
  /*for (i = 0; i < memory_count; i++)
    {
      //val = 1280 + rand () % (31359 + 1);
      sc_memorySet (i, 0);
    }
  sc_memorySave (filename);
  sc_memoryLoad (filename);
   sc_commandDecode (0, &com, &oper);*/

  int maxx, maxy;

  mt_getscreensize (&maxy, &maxx);

  if (maxy < 32 || maxx < 86)
    {
      printf ("\nmaxx=%d, maxxy=%d", maxx, maxy);
      printf ("\nError scrin size");
      exit (0);
    }
  ms_setSignals ();
  struct itimerval nval, oval;
  // signal (SIGALRM, signalhandler);
  nval.it_interval.tv_sec = 1;
  nval.it_interval.tv_usec = 500;
  nval.it_value.tv_sec = 1;
  nval.it_value.tv_usec = 0;

  /* Запускаем таймер */
  // setitimer (ITIMER_REAL, &nval, &oval);
  drow (Counter, 0, YELLOW);
  rk_mytermregime (0, 1, 0, 0, 1);

  while (!0)
    {
      rk_readkey (&key);
      int ignore;
      sc_regGet (regT, &ignore);
      if (ignore)
        {
          if (key == 0)
            {
              rk_mytermregime (1, 1, 0, 1, 1);
              printf ("Enter filename> ");
              scanf ("%s", filename);
              sc_memoryLoad (filename);
              // mt_clrscr();
              // drow();
              drow (Counter, yach, YELLOW);
              rk_mytermregime (0, 1, 0, 0, 1);
              key = -1;
            }
          else if (key == 1)
            {
              rk_mytermregime (1, 1, 0, 1, 1);
              printf ("Enter filename> ");
              scanf ("%s", filename);
              sc_memorySave (filename);
              rk_mytermregime (0, 1, 0, 0, 1);
              key = -1;
            }

          // else if(key == 5)
          else if (key == 6)
            {
              int znach;
              rk_mytermregime (1, 1, 0, 1, 1);
              printf ("Enter Accumulator> ");
              scanf ("%d", &znach);
              sc_accumulator = znach;
              drow (Counter, yach, YELLOW);
              rk_mytermregime (0, 1, 0, 0, 1);
              key = -1;
            }
          else if (key == 7)
            {
              int counter;
              rk_mytermregime (1, 1, 0, 1, 1);
              printf ("Enter counter> ");
              scanf ("%d", &counter);
              if ((counter >= 0) && (counter < 100))
                {
                  Counter = counter;
                  sc_regSet (regM, 0);
                  drow (Counter, yach, YELLOW);
                }
              else
                {
                  sc_regSet (regM, 1);
                }
              rk_mytermregime (0, 1, 0, 0, 1);
              key = -1;
            }
          else if (key == 8)
            {
              rk_mytermregime (1, 1, 0, 1, 1);
              mt_setbgcolor (GREEN);
              drow (Counter, yach, GREEN);
              scanf ("%d", &val);
              sc_memorySet (yach, val);
              drow (Counter, yach, YELLOW);
              rk_mytermregime (0, 1, 0, 0, 1);
              mt_gotoXY (30, 1);
              key = -1;
            }
          else if (key == 9)
            {
              if ((yach - 10) >= 0)
                {
                  mt_setfgcolor (WHITE);
                  yach -= 10;
                  drow (Counter, yach, YELLOW);
                  mt_setbgcolor (BLACK);
                  mt_gotoXY (30, 1);
                  // mt_gotoXY (30, 1);
                }
              key = -1;
            }
          else if (key == 10)
            {
              if ((yach + 10) <= 99)
                {
                  mt_setfgcolor (WHITE);
                  yach += 10;
                  drow (Counter, yach, YELLOW);
                  mt_setbgcolor (BLACK);
                  mt_gotoXY (30, 1);
                  // mt_gotoXY (30, 1);
                }
              key = -1;
            }
          else if (key == 11)
            {
              if ((yach - 1) >= 0)
                {
                  mt_setfgcolor (WHITE);
                  yach -= 1;
                  drow (Counter, yach, YELLOW);

                  mt_setbgcolor (BLACK);
                  mt_gotoXY (30, 1);
                  // mt_gotoXY (30, 1);
                }
              key = -1;
            }
          else if (key == 12)
            {
              if ((yach + 1) <= 99)
                {
                  mt_setfgcolor (WHITE);
                  yach += 1;
                  drow (Counter, yach, YELLOW);
                  mt_setbgcolor (BLACK);
                  mt_gotoXY (30, 1);
                }
              key = -1;
            }
        }
      if (key == 2)
        {
          int valueR;
          sc_regGet (regT, &valueR);
          if (valueR)
            {
              sc_regSet (regT, 0);
              // ms_timerHandler(SIGALRM);
              setitimer (ITIMER_REAL, &nval, &oval);
              // alarm(3);
              yach = Counter;
            }
          else
            {
              alarm (0);
              sc_regSet (regT, 1);
              yach = Counter;
              drow (Counter, Counter, YELLOW);
            }
          key = -1;
        }
      else if (key == 3)
        {
          drow (Counter, Counter, YELLOW);
          yach = Counter;
          // CU();
        }
      else if (key == 4)
        {
          rk_mytermregime (1, 1, 0, 1, 1);
          raise (SIGUSR1);
          /*sc_memoryInit ();
          sc_regInit ();
          counter = 0;
          yach = 0;
          drow (counter, yach, YELLOW);
          mt_setbgcolor (BLACK);*/
          rk_mytermregime (0, 1, 0, 0, 1);
          key = -1;
        }
    }
  rk_mytermregime (1, 1, 0, 1, 1);
}
