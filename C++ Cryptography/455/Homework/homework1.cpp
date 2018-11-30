#include <iostream>
#include "bias.h"
using namespace std;

int main()
{
  int count = 0;
  
  for (int x = 0; x < 64; ++x)
  {
    int y = apply(S1, x);
    if ((X2(x) ^ Y1(y) ^ Y2(y) ^ Y3(y) ^ Y4(y)) == 0)
      ++ count;
  }

  cout << "The bias of S1 is: " << 32-count << "/64" << endl;
  count = 0;
  

  for (int x = 0; x < 64; ++x)
  {
    int y = apply(S2, x);
    if ((X2(x) ^ Y1(y) ^ Y2(y) ^ Y3(y) ^ Y4(y)) == 0)
      ++ count;
  }

  cout << "The bias of S2 is: " << 32-count << "/64" << endl;
  count = 0;

  for (int x = 0; x < 64; ++x)
  {
    int y = apply(S3, x);
    if ((X2(x) ^ Y1(y) ^ Y2(y) ^ Y3(y) ^ Y4(y)) == 0)
      ++ count;
  }

  cout << "The bias of S3 is: " << 32-count << "/64" << endl;
  count = 0;

  for (int x = 0; x < 64; ++x)
  {
    int y = apply(S4, x);
    if ((X2(x) ^ Y1(y) ^ Y2(y) ^ Y3(y) ^ Y4(y)) == 0)
      ++ count;
  }

  cout << "The bias of S4 is: " << 32-count << "/64" << endl;
  count = 0;

  for (int x = 0; x < 64; ++x)
  {
    int y = apply(S5, x);
    if ((X2(x) ^ Y1(y) ^ Y2(y) ^ Y3(y) ^ Y4(y)) == 0)
      ++ count;
  }

  cout << "The bias of S5 is: " << 32-count << "/64" << endl;
  count = 0;

  for (int x = 0; x < 64; ++x)
  {
    int y = apply(S6, x);
    if ((X2(x) ^ Y1(y) ^ Y2(y) ^ Y3(y) ^ Y4(y)) == 0)
      ++ count;
  }

  cout << "The bias of S6 is: " << 32-count << "/64" << endl;
  count = 0;

  for (int x = 0; x < 64; ++x)
  {
    int y = apply(S7, x);
    if ((X2(x) ^ Y1(y) ^ Y2(y) ^ Y3(y) ^ Y4(y)) == 0)
      ++ count;
  }

  cout << "The bias of S7 is: " << 32-count << "/64" << endl;
  count = 0;

  for (int x = 0; x < 64; ++x)
  {
    int y = apply(S8, x);
    if ((X2(x) ^ Y1(y) ^ Y2(y) ^ Y3(y) ^ Y4(y)) == 0)
      ++ count;
  }

  cout << "The bias of S8 is: " << 32-count << "/64" << endl;
}
