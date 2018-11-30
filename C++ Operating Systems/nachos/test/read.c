#include "syscall.h"

int main()
{
  OpenFileId fid;
  int read;
  int size = 20;
  char* name = "CreateTest.txt";
  char buf[size];
 

  fid = Open(name);
  size = Read(buf, size, fid);


  Write(buf, size, fid);

  Close(fid);

  Exit(0);

  return 0;
  
}
