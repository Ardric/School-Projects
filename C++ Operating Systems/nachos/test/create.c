#include "syscall.h"
//Hey
int
main ()
{
  char* name  = "CreateTest.txt";
  //int size = 40;

  Create(name);

  Halt();
  return 0;
}
