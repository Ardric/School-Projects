#ifndef _DIJKSTRA_H_
#define _DIJKSTRA_H_

#include "Graph.h"
#include <string>
using namespace std;

struct dijkstraItem
{
  string label;
  int distance; // best so far

  bool operator< (const dijkstraItem& b) const
  {
    return distance > b.distance;
  }
};

int dijkstra (const Graph<string>& graph, string start, string finish);


#endif
