#include "mySignal.h"
//#include "CU.h"
#include "math.h"
#include "myBigChars.h"
#include "myInterface.h"
#include "myReadkey.h"
#include "mySimpleComputer.h"
#include "myTerm.h"
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>
int
ms_setSignals ()
{
  signal (SIGALRM, ms_timerHandler);
  signal (SIGUSR1, ms_userSignal);
}

void
ms_timerHandler (int sig)
{
  // CU();
  int value;
  sc_regGet (regT, &value);
  // sleep(1);

  if ((Counter < 99 && Counter >= 0) && !value)
    {
      Counter++;
    }
  else if (Counter >= 99)
    {
      Counter = 0;
    }
  drow (Counter, Counter, YELLOW);
}

void
ms_userSignal (int sig)
{
  alarm (0);
  sc_memoryInit ();
  sc_regInit ();
  sc_regSet (regT, 1);
  Counter = 0;
  sc_accumulator = 0;
  drow (Counter, 0, YELLOW);
}
