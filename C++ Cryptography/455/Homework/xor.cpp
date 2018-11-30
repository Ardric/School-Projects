#include <iostream>
using namespace std;

int main()
{
  int x = 0x675C006E;
  int y = 0xD13F0CA7;
  int z = x^y;
  cout << hex << z << endl;
return 0;
}
