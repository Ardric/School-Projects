#include <iostream>
#include <set>
#include <string>
using namespace std;

int inverse[26] = {0,1,0,9,0,21,0,15,0,3,0,19,0,0,0,7,0,23,0,11,0,5,0,17,0,25};

bool CheckGrams(string input)
{
  int count_the = 0;
  int count_and = 0;
  int count_tha = 0;
  int count_th = 0;
  int count_he = 0;
  int count_in = 0;
  size_t found = 0;
  int length = input.length();

  for (string::iterator i = input.begin(); i != input.end(); i++)
  {
    found = input.find("the");
    if (found != 0)
    {
      count_the++;
      if (found+2 < input.length())
      {
        input = input.substr(found+2);
	found = 0;
      }
      
      else
	break;
    }
  }

  for (string::iterator i = input.begin(); i != input.end(); i++)
  {
    found = input.find("and");
    if (found != 0)
    {
      count_and++;
      if (found+2 < input.length())
      {
        input = input.substr(found+2);
	found = 0;
      }
      
      else
	break;
    }
  }

  for (string::iterator i = input.begin(); i != input.end(); i++)
  {
    found = input.find("tha");
    if (found != 0)
    {
      count_tha++;
      if (found+2 < input.length())
      {
        input = input.substr(found+2);
	found = 0;
      }
      
      else
	break;
    }
  }

  for (string::iterator i = input.begin(); i != input.end(); i++)
  {
    found = input.find("th");
    if (found != 0)
    {
      count_th++;
      if (found+1 < input.length())
      {
        input = input.substr(found+1);
	found = 0;
      }
      
      else
	break;
    }
  }

  for (string::iterator i = input.begin(); i != input.end(); i++)
  {
    found = input.find("he");
    if (found != 0)
    {
      count_he++;
      if (found+1 < input.length())
      {
        input = input.substr(found+1);
	found = 0;
      }
      
      else
	break;
    }
  }

  for (string::iterator i = input.begin(); i != input.end(); i++)
  {
    found = input.find("in");
    if (found != 0)
    {
      count_in++;
      if (found+1 < input.length())
      {
        input = input.substr(found+1);
	found = 0;
      }
      
      else
	break;
    }
  }

  if ((count_the + count_and + count_tha + count_th + count_he + count_in)*100 < 6*length)
  {
    return false;
  }
  return true;
}

bool Checkuncommon(string input)
{
  int count_q = 0;
  int count_z = 0;
  int count_j = 0;
  int count_x = 0;

  int length = input.length();

  for (int i = 0; i < length; i++)
  {
    if (input.at(i) == 'q')
    {
      count_q++;
    }

    if (input.at(i) == 'j')
    {
      count_j++;
    }

    if (input.at(i) == 'x')
    {
      count_x++;
    }

    if (input.at(i) == 'z')
    {
      count_z++;
    }
  }

  if (count_x*100 > 1*length)
  {
    return false;
  }

  if (count_j*100 > 1*length)
  {
    return false;
  }

  if (count_q*100 > 1*length)
  {
    return false;
  }

  if (count_z*100 > 1*length)
  {
    return false;
  }
  return true;
}

bool CheckTAOINSHR(string input)
{
   int count_t = 0;
   int count_a = 0;
   int count_o = 0;
   int count_i = 0;
   int count_n = 0;
   int count_s = 0;
   int count_h = 0;
   int count_r = 0;

   int length = input.length();

   for (int i = 0; i < length; i++)
   {
   if (input.at(i) == 't')
   {
   count_t++;
   }

   if (input.at(i) == 'a')
   {
   count_a++;
   }

   if (input.at(i) == 'o')
   {
   count_o++;
   }

   if (input.at(i) == 'i')
   {
   count_i++;
   }

   if (input.at(i) == 'n')
   {
   count_n++;
   }

   if (input.at(i) == 's')
   {
   count_s++;
   } 

   if (input.at(i) == 'h')
   {
   count_h++;
   }

   if (input.at(i) == 'r')
   {
   count_r++;
   }
   }
   if (count_t*100 < 5*length)
   {
     return false;
   }
   if (count_a*100 < 4*length)
   {
     return false;
   }
   if (count_o*100 < 3*length)
   {
     return false;
   }
   if (count_i*100 < 3*length)
   {
     return false;
   }
   if (count_n*100 < 3*length)
   {
     return false;
   }
   if (count_s*100 < 3*length)
   {
     return false;
   }
   if (count_h*100 < 3*length)
   {
     return false;
   }
   if (count_r*100 < 2*length)
   {
     return false;
   }
   return true;
}
bool CheckE(string input)
{
  int count_e = 0;
  int length = input.length();

  for (int i = 0; i < length; i++)
  {
    if (input.at(i) == 'e')
    {
      count_e++;
    }
  }
  if (count_e*100 < 8*length)
  {
    return false;
  }
  return true;
}
char affine(int a, int b, char input)
{
  if (input < 'A' || input > 'Z')
    return input;

  char ciphertext;
  char plaintext;
  ciphertext = input - 'A';
  plaintext = ((ciphertext + (26-b)) * inverse[a]) %26;
  plaintext = plaintext + 'a';
  return plaintext;
}
void decrypt(string input)
{
  string guess = input;
  for (int y = 1; y < 26; y++)
  {
    if (inverse[y] != 0){
      for (int x = 0; x < 26; x++)
      {
	for(unsigned i = 0; i < input.length(); i++)
	{
	  guess[i] = affine(y,x,input[i]);
	}
	if (CheckE(guess) && CheckTAOINSHR(guess) && Checkuncommon(guess) && CheckGrams(guess))
	{
	  cout << guess << endl;
	}
      }
    }
  }
}

int main()
{
  string input;
  while (getline(cin, input))
  {
    decrypt(input);
  }
}

