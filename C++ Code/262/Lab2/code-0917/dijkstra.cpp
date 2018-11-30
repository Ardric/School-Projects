#include "Dijkstra.h"
#include <queue>
using namespace std;


/** Takes graph and start, finish
  * @return length of shortest, or -1 if none */
int dijkstra (const Graph<string>& graph, string start, string finish)
{
  priority_queue< dijkstraItem > agenda;
  agenda.push( dijkstraItem{start, 0} );

  set<string> explored;

  while (not agenda.empty())
  {
    dijkstraItem node = agenda.top();
    agenda.pop();

    if (explored.count(node.label) > 0)
      continue;

    explored.insert(node.label);

    if (node.label == finish)
      return node.distance;

    
    for (string adj : graph.getAdjacent(node.label))
    {
      if (explored.count(adj) > 0)
        continue;

      agenda.push( dijkstraItem{ adj, node.distance 
          + graph.getWeight(node.label, adj) } );
    }
    

  }

  // not found
  return -1;
}
