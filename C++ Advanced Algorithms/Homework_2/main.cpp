#include <iostream>
#include <vector>
#include <string>
#include <math.h>
using namespace std;

int main(int argc, char* argv[]){

  vector <int> squares;
  vector <int> assignment;
  vector <int> set;

  long long count = 0;
  long long check = 0;
  int i, position;
  bool solving = true;


  //Sets up Squares and Set Assignment Vectors
  for( i = 0; i < stoi(argv[1]); i++ )
  {
    	squares.push_back( pow((i+1), 2) );
	assignment.push_back( 0 );
  }

  //Sets up Set Vector
  for( i = 0; i < stoi(argv[2]); i++ )
  {
    	set.push_back( 0 );
  }

  //While we haven't found a solution, check
  //to see if the current set assignments
  //satisfy our goal. If not, check the next possible set
  //assignment.
  while( solving )
  {
    	for( i = 0; i < squares.size(); i++ )
	{
		position = assignment[i];
		set[position] += squares[i];
	}

	if( set[0] == set[1] && set[0] == set[2] && set[0] == set[3] )
	{
	  	cout << "Answer has been found." << endl;
		cout << "Set assignment is: ";

		for( i = 0; i < assignment.size(); i++ )
		  	cout << assignment[i];

		cout << endl;

		for( i = 0; i< set.size(); i++)
		{
		  cout << set[i] << endl;
		}

		solving = false;
	}

	else
	{
		count++;

		if( count == pow(set.size(), assignment.size()) )
		{
		  solving = false;

		  cout << "Unable to find a solution" << endl;
		  cout << "Set assignment is: ";

		  for( i = 0; i < assignment.size(); i++ )
		    	cout << assignment[i];

		  cout << endl;
		  cout << count << endl;
		}

		for( i = 0; i < set.size(); i++ )
		{
		  set[i] = 0;
		}

		for( i = assignment.size() - 1; i >= 0; i-- )
		{
			assignment[i] = (( assignment[i] + 1 ) % set.size());

			if( assignment[i] != 0 )
				  break;
		}

		}
	}

  return 0;

}
