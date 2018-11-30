#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <queue>
#include <unordered_set>
#include "Pathfinder.h"

/*
struct AstarItem
{
  Location current;
  int from_start;
}*/

bool Pathfinder::contains(const Location& loc) const
{
    return loc.getX() >= 0 and loc.getX() < col
       and loc.getY() >= 0 and loc.getY() < row;
}

char Pathfinder::elementAt (const Location& loc) const
{
  if (!contains(loc))
    throw runtime_error("Location " + loc.toString()
			  + " not valid in this Maze");
  return grid[loc.getX()][loc.getY()];
}



bool Pathfinder::doesPathExist() 
{

  priority_queue< AstarItem > agenda;
  agenda.push( AstarItem{start, 0, this} );
  unordered_set< Location > explored;
  //vector<vector<char>> *newgrid = &grid;
  while (not agenda.empty())
  {
    AstarItem node = agenda.top();
    agenda.pop();

    if (explored.count(node.current) > 0)
      continue;

    explored.insert(node.current);
    
    if (node.current.isEqualTo(finish))
    { 
      cout <<  "Path exists with length:" << " " << node.from_start << endl;

      for (int y = 0; y < row; ++y)
      {
	for (int x = 0; x < col; ++x)
	{
	  cout << " ";
	  if ((explored.count(Location{x, y}) > 0) and (grid[x][y] != '*') and (grid[x][y] != 'o'))
	    cout << "-";
	  else
	    cout << grid[x][y];
	}
	cout << endl;
      }
      return true;
    }
    for (AstarItem Add : node.GetAdj())
    {
      if (explored.count(Add.current) > 0)
	continue;
      agenda.push(Add);
    }
  }

  cout << "There was no path to be found to the finish." << endl;
      for (int y = 0; y < row; ++y)
      {
	for (int x = 0; x < col; ++x)
	{
	  cout << " ";
	  if ((explored.count(Location{x, y}) > 0) and (grid[x][y] != '*') and (grid[x][y] != 'o'))
	    cout << "-";
	  else
	    cout << grid[x][y];
	}
	cout << endl;
      }
 return false; 
}

vector<AstarItem> AstarItem::GetAdj() const 
{ 
  Location North = current.north();
  Location South = current.south();
  Location East = current.east();
  Location West = current.west();
  vector<AstarItem> retvec;
 

  if ((newgrid->contains(South)) and (newgrid->elementAt(South) != '#'))
  {
    retvec.push_back(AstarItem{South, from_start + 1, newgrid});
  }
  if ((newgrid->contains(North)) and (newgrid->elementAt(North) != '#'))
  {
    retvec.push_back(AstarItem{North, from_start + 1, newgrid});
  }
  if ((newgrid->contains(East)) and (newgrid->elementAt(East) != '#'))
  {
    retvec.push_back(AstarItem{East, from_start + 1, newgrid});
  }
  if ((newgrid->contains(West)) and (newgrid->elementAt(West) != '#'))
  {
    retvec.push_back(AstarItem{West, from_start + 1, newgrid});
  }

 return retvec;
}

void Pathfinder::readgrid(FILE * fp)
{
  char charinput;
  fscanf(fp, "%d %d", &col, &row);
  
  grid.resize(col);

  for (int x = 0; x < col; ++x)
  {
    grid[x].resize(row);
  }

  for (int y = 0; y < row; ++y)
  {
    for (int x = 0; x < col; ++x)
    {
      
        fscanf(fp, "%c", &charinput);
      if (charinput != '\n')
      {	
        grid[x][y] = charinput;
      }

      else
       {
	 fscanf(fp, "%c", &charinput);
	 grid[x][y] = charinput;
       }
      
      if (charinput == 'o')
      {
	start = Location(x, y);
      }

      if (charinput == '*')
      {
	finish = Location(x, y);
      }
    }
  }
}


void Pathfinder::printgrid() const
{
  for (int y = 0; y < row; ++y)
  {
    for (int x = 0; x < col; ++x)
    {
      cout << grid[x][y];
    }
  cout << endl;
  }
}

int main(int argc, char * argv[])
{
  
  Pathfinder M;

  FILE * fp;
  
  fp = fopen (argv[1], "r+");

  M.readgrid(fp);
  M.doesPathExist();
  M.printgrid();



return 0;
}

