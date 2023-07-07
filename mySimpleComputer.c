#include "mySimpleComputer.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int memory[memory_count];
char flags;
int
sc_memoryInit ()
{

  int n;
  for (n = 0; n < memory_count; n++)
    {
      memory[n] = 0;
    }
  return 1;
}
int
sc_memorySet (int address, int value)
{
  if (address < memory_count || address >= 0)
    {
      memory[address] = value;
    }
  else
    {
      // printf ("\nError: going beyond the boundaries of memory");
      sc_regSet (regM, 1);
      return 0;
    }
  return 1;
}
int
sc_memoryGet (int address, int *value)
{
  if (address < memory_count || address >= 0)
    {
      *value = memory[address];
      return 1;
    }
  else
    {
      // printf ("\nError: going beyond the boundaries of memory");
      sc_regSet (regM, 1);
      return 0;
    }
}
int
sc_memorySave (char *filename)
{
  FILE *file = NULL;
  if ((file = fopen (filename, "wb")) == NULL)
    { //проверка на открытие файла
      // printf ("Ошибка открытия файла");
      return -1;
    }

  fwrite (memory, sizeof (int), memory_count, file);
  fclose (file);
  return 1;
}
int
sc_memoryLoad (char *filename)
{
  FILE *file = NULL;
  if ((file = fopen (filename, "rb")) == NULL)
    { //проверка на открытие файла
      // printf ("Ошибка открытия файла");
      return -1;
    }
  fread (memory, sizeof (int), memory_count, file);
  fclose (file);
  return 1;
}
int
sc_regInit (void)
{
  flags = 0;
}
int
sc_regSet (int registe_r, int value)
{
  if (registe_r != 0x1 && registe_r != 0x2 && registe_r != 0x4
      && registe_r != 0x8 && registe_r != 0x10)
    {
      // printf ("\nError invalid register or value");
      return -1;
    }
  else
    {
      if (value == 1)
        {
          flags = flags | registe_r;
        }
      else if (value == 0)
        {
          flags = flags & (~(registe_r));
        }
      return 1;
    }
}
int
sc_regGet (int registe_r, int *value)
{
  char val;
  if (registe_r != 0x1 && registe_r != 0x2 && registe_r != 0x4
      && registe_r != 0x8 && registe_r != 0x10)
    {
      // printf ("\nError invalid register or value");
      return -1;
    }
  else
    {
      val = registe_r & flags;
      if (val == registe_r)
        *value = 1;
      else
        *value = 0;
      return 0;
    }
}
int
sc_commandEncode (int command, int operand, int *value)
{
  if (command < 10 || command > 76 && operand < 0 || operand > 127)
    {
      // printf ("Error: invalid command or operator");
      return 0;
    }
  else
    {
      *value = (operand & 0x7F) | ((command & 0x7F) << 7);
      return 1;
    }
}
int
sc_commandDecode (int value, int *command, int *operand)
{
  int num, num2;
  if (value > 0x7F7F)
    {
      // printf ("Error");
      sc_regSet (regE, 1);
      return 0;
    }
  else
    {
      num = (value & 0x3F80) >> 7;
      num2 = (value & 0x7F);
      *command = num;
      *operand = num2;
      return 1;
    }
}
