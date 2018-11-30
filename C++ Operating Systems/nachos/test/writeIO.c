#include "syscall.h"

char array[4096];
int main()
{

  int i;

  for (i = 0; i < 4096; i++)
  {
    array[i] = 'i';
  }


  Write(array, 4096, 1);

  Halt();
  return 0;

  /*
  int size = 20;
  char buf[size];
  OpenFileId fid = 0;
  OpenFileId tmp = 1;
  char* name = "CreateTest.txt";
  int i;
  SpaceId id;
for( i = 0; i < 10; i++){
  fid = Open(name);

  size = Read(buf, size, fid);

  tmp = 1;

  Write(buf, size, 1);

  Close(fid);
}
  for( i = 1; i < 4; i++){
    SpaceId id = Exec("../test/writeIO");
    Join(id);
  }
  Halt();

  return 0;*/
}
