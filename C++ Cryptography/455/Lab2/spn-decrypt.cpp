#include <iostream>
#include <cstdlib>

using namespace std;
unsigned int calc_subkey(unsigned int* key, int round, int pos)
{
  return (key[round] >> (8*(3-pos))) % 256;
}

unsigned char substitute(unsigned char c)
{
  return (c + 255)%256;
}

void permute(unsigned int* old_block, unsigned int* new_block)
{
  unsigned int value = (old_block[0] << 24) | (old_block[1] << 16) | (old_block[2] << 8) | old_block[3];
  unsigned int left = value >> 5;
  unsigned int right = value >> 27;
  right = right & 0x0000001f;
  unsigned int combo = left | right;

  new_block[0] = combo >> 24 & 255;
  new_block[1] = combo >> 16 & 255;
  new_block[2] = combo >> 8 & 255;
  new_block[3] = combo & 255;
}

void decrypt(int rounds, unsigned int* key, int* block, int len)
{
  unsigned int w[4], v[4], u[4];

  for (int cur = 0; cur < 4; ++cur)
  {
    w[cur] = block[cur];
  }

  for (int i = 0; i < 4; i++)
  {
    w[i] ^= calc_subkey(key,rounds,i);
  }

  for (int i = 0; i < 4; ++i)
  {
    u[i] = substitute(w[i]);
  }

  for (int i = 0; i < 4; ++i)
  {
    w[i] = u[i] ^ calc_subkey(key,rounds - 1,i);
  }
  
    
    for (int i = 2; i < rounds; i++)
    {
     permute(w,v);
     for (int j = 0; j < 4; ++j)
     {
       u[j] = substitute(v[j]);
     }

     for (int j = 0; j < 4; ++j)
     {
       w[j] = u[j] ^ calc_subkey(key, rounds - i, j);
     }
     cout << i << endl;
   }
if (rounds > 1){  
    for (int i = 0; i < 4; ++i)
    {
      u[i] = substitute(w[i]);
    }
    
    for (int i = 0; i < 4; i++)
    {
      w[i] = u[i] ^ calc_subkey(key,0,i);
    }
  }
for (int i = 0; i < 4; ++i)
{
  cout << (char)w[i] << " ";
}
}

int main(int argc, char** argv)
{
  int rounds;
  unsigned int* key;
  int message[4];
  string block = "";

  if (argc < 2)
  {
    cout << "Syntax: Encrypt <num_rounds> <key0> <key1> ... <keyNr+1<" << endl;
    return 1;
  }

  rounds = atoi(argv[1]);
  if (argc < rounds + 2)
  {
    cout << "Syntax: Encrypt <num_rounds> <key0> <key1> ... <keyNr+1<" << endl;
    return 1;
  }

  key = new unsigned int [rounds + 1];
  for (int i = 0; i < rounds + 1; ++i)
  {
    key[i] = atoi(argv[i+2]);
  }
  int count = 0;
  while (cin >> message[count])
  {
   if (count == 3)
   {
    decrypt(rounds,key,message,4);
    count = 0;
   }
   else
     count++;
  }
  cout << endl;
  delete[] key;
}

