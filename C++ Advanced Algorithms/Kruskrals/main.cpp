#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;


/********************************
 * Sets up data structures 
 * ****************************/
struct node {
  string n;
  string set = "set";
};

struct graph{
  node a;
  node b;
  int weight;
};


/*******************************
 * Compare function for sorting 
 * ***************************/
bool compareByWeight(const graph &a, const graph &b){
  return a.weight < b.weight;
}



int main(int argc, char* argv[]){
  vector<graph> Complete_Graph;
  vector<graph> SpanningTree;
  unordered_map <string, string> checked;
  ifstream f;
  string line = "";
  graph edges;

  f.open(argv[1]);

/*******************************
 * Reads in data from file and 
 * sets up our graph vector
 * ***************************/
  while (getline(f, line)){
    edges.a.n = line.substr(0, 1);
    edges.b.n = line.substr(1, 1);
    edges.a.set = "set";
    edges.b.set = "set";
    edges.weight = stoi(line.substr(3));
    Complete_Graph.push_back(edges);
  }
  
  f.close();

/******************************
 * Sorts our edges by weight
 * ***************************/
  sort(Complete_Graph.begin(), Complete_Graph.end(), compareByWeight);


/*****************************
 * Loops through our list of
 * sorted edges and determines
 * which edges should be added to 
 * the spanning tree
 * **************************/
  for (int i = 0; i < Complete_Graph.size(); i++){
  	unordered_map<string, string>::const_iterator got = checked.find(Complete_Graph[i].a.n);
	unordered_map<string, string>::const_iterator got2 = checked.find(Complete_Graph[i].b.n);

	//If both vertices are in the hashtable, compare there sets.
	//If their sets are the same, ignore the edge, if the sets are
	//different combine the two sets into one
	if (got != checked.end() && got2 != checked.end()){

	  if (got->second == got2->second)
	    continue;

	  else if (got->second != got2->second){
	    SpanningTree.push_back(Complete_Graph[i]);
	    checked.insert ( {Complete_Graph[i].b.n, Complete_Graph[i].a.n} );

	    for( pair<string, string> it : checked ){
	      if (it.second == got2->second)
	      {
		checked[it.first] = got->second;
	      }
	    }
	}
	}

	//If only 1 is in the hashtable, add the one that is not to the
	//set of the one that is
	else if (got == checked.end() && got2 != checked.end())
	{
	  SpanningTree.push_back((Complete_Graph[i]));
	  checked.insert( {Complete_Graph[i].a.n, got2->second} );
	}

	else if ( got != checked.end() && got2 == checked.end())
	{
	  SpanningTree.push_back((Complete_Graph[i]));
	  checked.insert( {Complete_Graph[i].b.n, got->second} );
	}


	//If neither are in the hashtable, add the edge with the set of the
	//first vertex
	else{
	  	SpanningTree.push_back(Complete_Graph[i]);
	  	checked.insert( {{Complete_Graph[i].a.n, Complete_Graph[i].a.n}, {Complete_Graph[i].b.n, Complete_Graph[i].a.n}} );
	}
  }

  for (int i = 0; i < SpanningTree.size(); i++)
    cout << "Edge: ("<< SpanningTree[i].a.n << "," << SpanningTree[i].b.n << ") Weight: " << SpanningTree[i].weight << endl;

  return 0;

}
