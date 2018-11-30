#ifndef _PATHFINDER_H_
#define _PATHFINDER_H_

#include <vector>
#include <iostream>
#include <sstream>
#include "Location.h"

class Pathfinder
{
   private:
    vector<vector<char>> grid;
    int row = 0;
    int col = 0;
    Location start = Location(-1, -1);
    Location finish = Location(-1, -1);
    
   public:
//    Pathfinder (vector<vector<char>> newgrid) { grid = newgrid; };
    void readgrid (FILE * fp);
    void printgrid () const;
    bool contains (const Location& loc) const;
    char elementAt (const Location& loc) const;
    bool doesPathExist() ;
    
};

struct AstarItem
{
  Location current;
  int from_start;
  Pathfinder *newgrid; 
  
  bool operator< (const AstarItem& b) const
  {
    return from_start > b.from_start;
  }
  vector<AstarItem> GetAdj() const;
};
#endif
