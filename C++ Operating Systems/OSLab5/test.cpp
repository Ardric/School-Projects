#include "filesys.h"
#include <iostream>

int main()
{
  bool check = false;;
  string files = "";
  Filesystem* fs = new Filesystem("glitter.img", 4194304);

  fs->format();

  check = fs->create("Firstfile");
  cout << "First file creation was successful: " << check << endl;
  check = fs->create("Secondfile");
  cout << "Second file creation was successful: " << check << endl;
  check = fs->create("Thirdfile");
  cout << "Third file creation was successful: " << check << endl;

  check = fs->isFragmented();
  cout << "Is the disk currently fragmented: " << check << endl;

  check = fs->rm("Secondfile");
  cout << "Second file removal was successful: " << check << endl;

  check = fs->isFragmented();
  cout << "Is the disk currently fragmented: " << check << endl;

  fs->defragment(0);
  cout << "Defragmenting..." << endl;

  check = fs->isFragmented();
  cout << "Is the disk currently fragmented: " << check << endl;

  delete fs;

  return 0;
}
