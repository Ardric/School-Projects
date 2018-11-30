#include "syscall.h"

int main()
{
  int size = 20;
  char buf[size];
  OpenFileId fid = 0;
  char* name = "CreateTest.txt";

  size = Read(buf, size, fid);

  fid = Open(name);

  Write(buf, size, fid);

  Close(fid);

  Halt();

  return 0;
}
