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

bool Solve(int position, int start){
/***********************************
 * Baseline Checks:
 * If position = assignment.size() - 1 we failed
 * If start = 4, we need to back track
 * ********************************/ 
    cout << position << endl;
  if (position == 11)
  {
    cout << "in the pos 11 if" << endl;
    return false;
    cout << "I should not see this code" << endl;
  }

   if (position == assignment.size() - 1)
      return false;

     if( start == set.size() )
    {
      cout << "also shouldnt be here." << endl;
      set[start] -= squares[position];
      assignment[position] = 0;
      start = assignment[position + 1];
      Solve( position + 1, start + 1 );
    }


/***********************************
 * If we pass, try a assignment
 * ********************************/

    assignment[position] = start;
    set[start] += squares[position];

  cout << "Position: " << position << " Start: " << start << endl;  
     if( set[start] > limit )
    {
      set[start] -= squares[position];
      if( start == 3 ){
	cout << "shouldnt be here" << endl;
	assignment[position] = 0;
	start = assignment[position + 1];
	Solve(position + 1, start + 1);
      }
      start = (start + 1) % set.size();
      Solve(position, start);
    }





    //Are we finished?
    if( position == 0 )
    {
      cout << "we make it here" << endl;
      return false;
      if( set[0] == set[1] && set[0] == set[2] && set[0] == set[3] )
      {
	return true;
      }

      else
      {
	Solve(position, start + 1);
      }
    }
	
    cout << position << endl;
    position--;
    start = 0;
    cout << position << endl;
    bool ans = Solve(position, start);
    return ans;
}
















int main(int argc, char* argv[]){

  int NumSquares = stoi(argv[1]);
  int NumSets = stoi(argv[2]);

  int i;
  int position = NumSquares - 2;
  bool Solved;
  int start = 0;

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
  limit = limit / 4;;
  cout << limit << endl;
 
  //Sets up Set Vector
  for( i = 0; i < NumSets; i++ )
  {
    	set.push_back( 0 );
  }

  set[0] += squares[NumSquares - 1];

  if (set[0] > limit)
  {
    cout << "No Solution found." << endl;
    return 0;
  }

  Solved = Solve(position, start);
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


  return 0;
}
