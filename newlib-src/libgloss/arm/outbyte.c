#include "debug.h"

int outbyte (int byte)
{
  char ch = byte;
  return write (1, &ch, 1);
}
