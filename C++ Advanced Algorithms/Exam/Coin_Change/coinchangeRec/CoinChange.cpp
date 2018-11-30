// some starter code with minimal documentation


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

//  ------------
// get list of ints from a file
vector<int>  getListFromFile(string filename)
{
  vector<int> listFromFile;
  
  ifstream f;
  f.open(filename.c_str());
  if (f.fail())
    { cout << "There was a problem opening the file " << filename << endl;
      return listFromFile;
    }
  while (!f.fail())
    {
      int num;
      f >> num;
      if (!f.fail())
	listFromFile.push_back(num);
    }
  f.close();
  return listFromFile;
      
}
//---------------------------------
int main(int argc, char *argv[])
{
  if ( argc != 3 ) // argc should be 2 for correct execution
    { cout<<"usage: "<< argv[0] <<" <filename> <changeamount>" << endl;;
      return 0;
    }
  
  vector<int> coinValues = getListFromFile(argv[1]);
  cout << "The coin values:" << endl;
  for (int n: coinValues)
    cout <<  n << " ";
  cout << endl;

  istringstream ss(argv[2]);
  int changeAmount;
  if (!(ss >> changeAmount))
    cerr << "Invalid number " << argv[2] << '\n';

  cout << "Change amount: " << changeAmount << endl;

  // CAN PUT YOUR CODE / FUNCTION calls here.

  
}
