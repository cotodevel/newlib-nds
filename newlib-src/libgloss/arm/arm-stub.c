#include <string.h>
#include <signal.h>
#include "debug.h"
//#include "asm.h"

//already written in GDB TGDS (gba gdb server stub), so we stub out methods here

void write_pc(unsigned long *registers, unsigned long addr)
{
  /*
  DEBUG (1, "In write_pc");

  registers[PC] = addr;
  registers[NPC] = addr + 4;
  */
  
}