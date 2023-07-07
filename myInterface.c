#include "myInterface.h"
#include "myBigChars.h"
#include "mySimpleComputer.h"
#include "myTerm.h"
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

void
drow_box ()
{
  mt_clrscr ();
  bc_box (1, 1, 62, 12);
  bc_box (63, 1, 85, 3);
  bc_box (63, 4, 85, 6);
  bc_box (63, 7, 85, 9);
  bc_box (63, 10, 85, 12);
  bc_box (1, 13, 43, 22);
  bc_box (44, 13, 85, 22);

  mt_gotoXY (1, 29);
  write (1, " Memory ", 8);
  mt_gotoXY (1, 67);
  write (1, " accumulator ", 13);
  mt_gotoXY (4, 64);
  write (1, " instructionCounter ", 20);
  mt_gotoXY (7, 69);
  write (1, " Operation ", 11);
  mt_gotoXY (10, 70);
  write (1, " Flags ", 7);
  mt_gotoXY (13, 46);
  write (1, " Keys: ", 7);
  mt_gotoXY (14, 46);
  write (1, "l  -  load", 10);
  mt_gotoXY (15, 46);
  write (1, "s  -  save", 10);
  mt_gotoXY (16, 46);
  write (1, "r  -  run", 9);
  mt_gotoXY (17, 46);
  write (1, "t  -  step", 10);
  mt_gotoXY (18, 46);
  write (1, "i  -  reset", 11);
  mt_gotoXY (19, 46);
  write (1, "F5 -  accumulator", 17);
  mt_gotoXY (20, 46);
  write (1, "F6 -  instructionCounter", 24);
}
void
drow_flag ()
{
  int ret;
  mt_gotoXY (11, 70);
  sc_regGet (regP, &ret);
  if (ret == 1)
    write (1, "П", 1);
  else
    write (1, "_", 1);

  mt_gotoXY (11, 72);
  sc_regGet (regM, &ret);
  if (ret == 1)
    write (1, "M", 1);
  else
    write (1, "_", 1);

  mt_gotoXY (11, 74);
  sc_regGet (regO, &ret);
  if (ret == 1)
    write (1, "O", 1);
  else
    write (1, "_", 1);

  mt_gotoXY (11, 76);
  sc_regGet (regT, &ret);
  if (ret == 1)
    write (1, "T", 1);
  else
    write (1, "_", 1);

  mt_gotoXY (11, 78);
  sc_regGet (regE, &ret);
  if (ret == 1)
    write (1, "E", 1);
  else
    write (1, "_", 1);
}
int
printCell (int address, enum colors color, int adress_enabled)
{
  int value, row, col, command, operand, i;
  char buf[6];
  sc_memoryGet (address, &value);
  if (value != 0)
    sc_commandDecode (value & 0x3FFF, &command, &operand);

  if (sc_memoryGet (address, &value) < 0
      || sc_commandDecode (value & 0x3FFF, &command, &operand) < 0)
    return -1;
  if (address == adress_enabled)
    {
      mt_setfgcolor (WHITE);
      mt_setbgcolor (color);
    }
  else
    {
      mt_setfgcolor (WHITE);
      mt_setbgcolor (BLACK);
    }
  row = address / 10;
  col = address % 10;
  // command = command << 7;
  // command = command | operand;
  if ((value & 0x4000) > 0)
    snprintf (buf, 6, "%c%02X%02X", '-', command, operand);
  else if ((value) == 0)
    snprintf (buf, 6, "%c%02X%02X", '+', 0, 0);
  else
    snprintf (buf, 6, "%c%02X%02X", '+', command, operand);

  mt_gotoXY (2 + row, 2 + col * 6);
  write (1, buf, 5);
  for (i = 0; i < 6; i++)
    buf[i] = '\0';
  mt_gotoXY (30, 1);
  // write (1, " ", 1);
  return 0;
}

void
drow_accum ()
{
  int i;
  char buf[6];
  if (sc_accumulator < 0)
    snprintf (buf, 6, "%c%04X", '-', abs (sc_accumulator));
  else if ((sc_accumulator) == 0)
    snprintf (buf, 6, "%c%04X", '+', 0);
  else
    snprintf (buf, 6, "%c%04X", '+', sc_accumulator);

  mt_gotoXY (2, 70);
  write (1, buf, 5);
  for (i = 0; i < 6; i++)
    buf[i] = '\0';
  mt_gotoXY (30, 1);
}

void
drow_instructioner (int yach)
{
  char buf[3];
  sprintf (buf, "%d", yach);
  mt_gotoXY (5, 73);
  if (yach < 10)
    write (1, buf, 1);
  else
    write (1, buf, 2);
}
void
drow_com (int value)
{
  int op, com, i;
  char buf[6];
  sc_commandDecode (value & 0x3FFF, &com, &op);
  if ((com >= 0 && com <= 127) && (op >= 0 && op <= 127))
    {
      mt_gotoXY (8, 72);
      snprintf (buf, 6, "%02X:%02X", com, op);
      write (1, buf, 5);
    }
  for (i = 0; i < 6; i++)
    buf[i] = '\0';
  mt_gotoXY (30, 1);
}
void
drow_bigchars (int address)
{
  int value, command, operand;
  int buff, i, numb, fd, ct;
  // char buf[6];
  int mass2[18][2];
  fd = open ("alph.txt", O_RDONLY);
  bc_bigcharread (fd, mass2[0], 18, &ct);
  // if(ct == 0) return 1;
  close (fd);

  char buf[6];
  if (sc_memoryGet (address, &value) < 0
      || sc_commandDecode (value & 0x3FFF, &command, &operand) < 0)
    return;

  // command = command << 7;
  // command = command | operand;
  if ((value & 0x4000) > 0)
    snprintf (buf, 6, "%c%02X%02X", '-', command, operand);
  else if ((value) == 0)
    snprintf (buf, 6, "%c%02X%02X", '+', 0, 0);
  else
    snprintf (buf, 6, "%c%02X%02X", '+', command, operand);
  mt_gotoXY (30, 1);
  if ((value & 0x4000) > 0)
    bc_printbigchar (mass2[17], 2, 14, LIGHT_BLUE, WHITE);
  else
    bc_printbigchar (mass2[16], 2, 14, LIGHT_BLUE, WHITE);
  for (i = 1; i < 5; i++)
    {
      if (buf[i] == '0')
        numb = 0;
      else if (buf[i] == '1')
        numb = 1;
      else if (buf[i] == '2')
        numb = 2;
      else if (buf[i] == '3')
        numb = 3;
      else if (buf[i] == '4')
        numb = 4;
      else if (buf[i] == '5')
        numb = 5;
      else if (buf[i] == '6')
        numb = 6;
      else if (buf[i] == '7')
        numb = 7;
      else if (buf[i] == '8')
        numb = 8;
      else if (buf[i] == '9')
        numb = 9;
      else if (buf[i] == 'A')
        numb = 10;
      else if (buf[i] == 'B')
        numb = 11;
      else if (buf[i] == 'C')
        numb = 12;
      else if (buf[i] == 'D')
        numb = 13;
      else if (buf[i] == 'E')
        numb = 14;
      else
        numb = 15;
      if (i == 1)
        bc_printbigchar (mass2[numb], 10, 14, GREEN, WHITE);
      else if (i == 2)
        bc_printbigchar (mass2[numb], 18, 14, GREEN, WHITE);
      else if (i == 3)
        bc_printbigchar (mass2[numb], 26, 14, GREEN, WHITE);
      else if (i == 4)
        bc_printbigchar (mass2[numb], 34, 14, GREEN, WHITE);
    }
  mt_gotoXY (30, 1);

  // return 0;
}
void
drow (int counter, int yach, enum colors color)
{
  int i, value;
  mt_setfgcolor (WHITE);
  mt_setbgcolor (BLACK);
  mt_clrscr ();
  //Отрисовка рамок
  drow_box ();
  //
  //отрисовка флагов
  drow_flag ();
  //отрисовка памяти

  for (i = 0; i < memory_count; i++)
    printCell (i, color, yach);

  sc_memoryGet (counter, &value);

  //отрисовка bigChars
  mt_setbgcolor (BLACK);
  drow_accum ();
  drow_instructioner (counter);
  drow_com (value);
  drow_bigchars (yach);
}
