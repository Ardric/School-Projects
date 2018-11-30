/*** STUDENTS: DO NOT FORGET TO PUT COMMENTS UP HERE
****/

#include <sstream>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int main ( int argc, char *argv[] )
{
  int alpha = 0;
  vector<char> alphabet;
  vector< vector< vector<int> > > transitionTable;
  int initialState;
  vector<int> finalStates;
  string line;
  int count = 0;
  int state = 0;
  int x = 0;

  if ( argc != 2 )
  {
    cout<<"usage: "<< argv[0]
	<<" <NFA description filename>  <String list filename> " << endl;
    return 0;
  }

  string NFAfilename = argv[1];

  ifstream infile;
  infile.open(NFAfilename);

  while (getline(infile, line))
  {
    if (count == 0)
    {
      for (char& c : line)
      {
	alphabet.push_back(c);
	++alpha;
      }
    }

    else if (count == 1)
    {
      state = stoi(line);
    }

    else if (count < (state + 2))
    {
      transitionTable.resize(state);
      for (int i = 0; i < state; i++)
      {
	transitionTable[i].resize(alpha+1);
      }
     
	istringstream sin(line);
	for(int j = 0; j < alpha + 1; j++)
	{
	    int temp;
	    sin >> temp;
	    if(temp == -1)
	    {
	      cout << "hello" << endl;
	      sin >> temp;
	      while (temp != -1)
	      {
		cout << temp << endl;
		transitionTable[count - 2][j].push_back(temp);
		sin >> temp;
	      }
	    }
	    else
	    {
	      transitionTable[count - 2][j].push_back(temp);
	      cout << temp << endl;
	    }
	}
    }

    else if (count == (state + 2))
    {
      initialState = stoi(line);
    }

    else if (count == (state + 3))
    {
       istringstream sin(line);
       for (unsigned int i = 0; i < line.size(); i++)
       { 
	 sin >> x;
	 finalStates.push_back(x);
       }
    } 
   ++count; 
  }
  infile.close();
}
