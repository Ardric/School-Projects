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
  vector< vector<int> > transitionTable;
  int initialState;
  vector<int> finalStates;
  string line;
  int count = 0;
  int state = 0;
  int x = 0;

  if ( argc != 3 )
  {
    cout<<"usage: "<< argv[0]
	<<" <DFA description filename>  <String list filename> " << endl;
    return 0;
  }

  string DFAfilename = argv[1];
  string stringlistFilename =  argv[2] ;

  ifstream infile;
  infile.open(DFAfilename);

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
	transitionTable[i].resize(alpha);
      }
     
	istringstream sin(line);
	for(int j = 0; j < alpha; j++)
	{
	    sin >> transitionTable[count - 2][j];
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

  infile.open(stringlistFilename);

  infile >> x;
  getline(infile, line);
  
  vector<string> filestring;
  vector<int> stringfinal;

  for (int i = 0; i < x; i++)
  {
    string test;
    getline(infile, test);
    filestring.push_back(test);
  }
  
  for (string s : filestring)
  {
  int cstate = initialState;
  for (unsigned int i = 0; i < s.size(); ++i)
  {
    for (unsigned int j = 0; j < alphabet.size(); ++j)
    {
      if (s[i] == alphabet[j])
      {
	cstate = transitionTable[cstate][j];
      }
    
    }
  }
  stringfinal.push_back(cstate);
  }
  for (unsigned int i = 0; i < stringfinal.size(); ++i)
  {
    for (unsigned int j = 0; j < finalStates.size(); j++)
    {
      if (stringfinal[i] == finalStates[j])
      {
	cout << "ACCEPTED : "<< filestring[i] << endl;
	break;
      }
      if (stringfinal[i] != finalStates[j] && j == finalStates.size() - 1)
      {
	cout << "NOT ACCEPTED : "<< filestring[i] << endl;
      }
    }
  }
  infile.close(); 
}
