#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <set>
#include <map>
#include <sstream>
using namespace std;

/** Setup for Dijkstra live-code
  * This is not beautiful code.
  * @author Don Blaheta
  * @version 16 Sep 2014 */
template <typename NodeLabel>
class Graph
{
  public:
    Graph () = default;
    void read (istream& in);
    set<NodeLabel> getNodes() const;
    set<NodeLabel> getAdjacent(const NodeLabel& node) const;
    /** assumes a and b are endpoints of actual edge, throws otherwise */
    int getWeight(const NodeLabel& a, const NodeLabel& b) const;

  private:
    map<NodeLabel, map<NodeLabel, int>> weights;
    set<NodeLabel> nodes; // for convenience
};

template <typename T>
void Graph<T>::read(istream& in)
{
  string line;
  while (getline(in, line))
  {
    istringstream edge(line);
    T st, fn;
    int weight;
    edge >> st >> fn >> weight;
    weights[st][fn] = weight;
    weights[fn][st] = weight;  // assuming bidirectional edges
    nodes.insert(st);
    nodes.insert(fn);
  }
}

template <typename T>
set<T> Graph<T>::getNodes() const
{
  return nodes;
}

template <typename T>
set<T> Graph<T>::getAdjacent(const T& node) const
{
  set<T> retval;
  if (weights.count(node) == 0)
    return retval;
  const map<T, int>& adj = weights.at(node);
  for (const auto& entry : adj)
  {
    retval.insert(entry.first);
  }
  return retval;
}


template <typename T>
int Graph<T>::getWeight(const T& a, const T& b) const
{
  return weights.at(a).at(b);
}


#endif
