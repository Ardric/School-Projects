#include <iostream>
#include <cstdlib>

using namespace std;
unsigned int calc_subkey(unsigned int* key, int round, int pos)
{
  return (key[round] >> (8*(3-pos))) % 256;
}

unsigned char substitute(unsigned char c)
{
  return (c + 1)%256;
}

void permute(unsigned int* old_block, unsigned int* new_block)
{
  unsigned int value = (old_block[0] << 24) | (old_block[1] << 16) | (old_block[2] << 8) | old_block[3];
  unsigned int left = value << 5;
  unsigned int right = value >> 27;
  right = right & 0x0000001f;
  unsigned int combo = left | right;

  new_block[0] = combo >> 24 & 0xFF;
  new_block[1] = combo >> 16 & 0xFF;
  new_block[2] = combo >> 8 & 0xFF;
  new_block[3] = combo & 0xFF;
}

void encrypt(int rounds, unsigned int* key, string block, int len)
{
  unsigned int w[4], v[4], u[4];

  for (int cur = 0; cur < 4; cur++)
  {
    w[cur] = block.at(cur);
  }

  cout << "Initial: " << endl;
  for(int i = 0; i < 4; ++i)
  {
    cout << w[i] << " ";
   }
  cout << endl;



  for (int i = 0; i < 4; i++)
  {
    w[i] ^= calc_subkey(key,0,i);
  }

  for (int i = 0; i < 4; i++)
  {
    u[i] = substitute(w[i]);
  }

  for (int i = 0; i < 4; i++)
  {
    w[i] = u[i] ^ calc_subkey(key,1,i);
  }

  for (int n = 2; n <= rounds - 1; n++)
  {
    for (int i = 0; i < 4; i++)
    {
      u[i] = substitute(w[i]);
    }
    
    permute(u,v);

    for (int i = 0; i < 4; i++)
    {
      w[i] = v[i] ^ calc_subkey(key,n,i);
    }
  }
 if (rounds > 1)
 { 
  for (int i = 0; i < 4; i++)
  {
    u[i] = substitute(w[i]);
  }

  for (int i = 0; i < 4; i++)
  {
    w[i] = u[i] ^ calc_subkey(key,rounds,i);
  }
 }

  cout << "FINAL" << endl;
  for (int i = 0; i < 4; i++)
  {
    cout << w[i] << " ";
  }
  cout << endl;
  
}

int main(int argc, char** argv)
{
  int rounds;
  unsigned int* key;
  string message = "";
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

  cin >> message;

  while (message.length() % 4 != 0)
  {
    message += " ";
  }

  for (int i = 0; i*4 < message.length(); ++i)
  {
    block = message.substr(i*4, 4);
    int len = block.length();
    encrypt(rounds, key, block, len);
  }
  cout << endl;
  delete[] key;
}

