#include <iostream>
#include <vector>
#include <string>
#include <math.h>
using namespace std;


vector <int> squares;
vector <int> assignment;
vector <int> set;

int limit;
int test = 0;

bool Solve(int position){
/***********************************
 * Baseline Checks:
 * If position = assignment.size() - 1 we failed
 * ********************************/ 

    //Did we fail?
    if (position == assignment.size() - 1){
      return false;
    }

    //Are we finished?
    if( position == -1 )
    {
      if( set[0] == set[1] && set[0] == set[2] && set[0] == set[3] )
      {
	return true;
      }

      else{
	return false;
      }
    }


/***********************************
 * If we pass, try a assignment
 * ********************************/

    for( int i = 0; i < set.size(); i++)
    {
      set[i] += squares[position];
      assignment[position] = i;

      if( set[i] > limit ){
        set[i] -= squares[position];
	assignment[position] = 0;
	if( i == 3 ){
	  return false;
	}
      }

      else{
        bool ans = Solve(position - 1);
      	if ( ans == true )
	  return true;
	if ( ans == false)
          set[i] -= squares[position];
	  assignment[position] = 0;
	  continue;
      }
    }
    }

int main(int argc, char* argv[]){

  int NumSquares = stoi(argv[1]);
  int NumSets = stoi(argv[2]);

  int i;
  int position = NumSquares - 2;
  bool Solved;

  //Sets up Squares and Set Assignment Vectors
  for( i = 0; i < NumSquares; i++ )
  {
    	squares.push_back( pow((i+1), 2) );
	assignment.push_back( 0 );
  }

  //Calculate Limit
  for( i = 0; i < NumSquares; i++ )
  {
    limit += squares[i];
  }
 
  //Sets up Set Vector
  for( i = 0; i < NumSets; i++ )
  {
    	set.push_back( 0 );
  }

  limit = limit / NumSets;

  set[0] += squares[NumSquares - 1];

  if (set[0] > limit)
  {
    cout << "No Solution Found." << endl;
    return 0;
  }

  Solved = Solve(position);
  cout << "Exited the function" << endl;
  if (Solved == true)
  {
    cout << "solution found" << endl;
    for( i = 0; i < assignment.size(); i++ )
      cout << assignment[i];

    cout << endl;
  }

  else
    cout << "No solution found" << endl;

  cout << "Solution Set Values: " << endl;
  for( i = 0; i < set.size(); i++)
	cout << set[i] << " ";

  cout << endl;

  return 0;
}
