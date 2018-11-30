#include "syscall.h"

int main(){
char *name = "../test/read";
int size = 20;
char buf[size];
OpenFileId fid = 0;
OpenFileId tmp = 1;
char* name1 = "CreateTest.txt";

SpaceId id = Exec(name);

int x = Join(id);

fid = Open(name1);

size = Read(buf, size, fid);

Write(buf, size, 1);

Close(fid);

Halt();
return 0;
}
