#include "debug.h"
#include "typedefsTGDS.h"

int inbyte (void)
{
  char ch;
  if (read (0, &ch, 1) == 1)
    return ch;

  return -1;
}
