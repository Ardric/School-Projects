// some starter code with minimal documentation


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <cstdint>
#include <unordered_map>
#include <time.h>
using U64 = uint64_t;
using namespace std;





vector<set<int>> PowerSets;
set<int> tmp;

struct Key
{
  int dest;
  set<int> source;

  bool operator==(const Key &other) const
  {
    return (dest == other.dest && source == other.source);
  }
};

struct Value
{
  int cost;
  int parent;
};

struct KeyHasher
{
  size_t operator()(const Key& k) const
  {
    return k.dest + k.source.size();
  }
};


unordered_map<Key, Value, KeyHasher> DynamicProgramming;












void setPrint(U64 x)
{
//    std::cout << "{ ";
    for(auto i = 1; x; x >>= 1, ++i)
        if (x & 1)
	{
	  tmp.insert(i);
//	  std::cout << i << ", ";
	}
    PowerSets.push_back(tmp);
    tmp.clear();
  //  std::cout << "}\n";
}

// get next greater subset of set with 
// Same Number Of One Bits
U64 snoob (U64 sub, U64 set) {
   U64 tmp = sub-1;
   U64 rip = set & (tmp + (sub & (0-sub)) - set);
   for(sub = (tmp & sub) ^ rip; sub &= sub-1; rip ^= tmp, set ^= tmp)
       tmp = set & (0-set);
   return rip;
}

void generatePowerSet(unsigned n)
{
    auto set = (1ULL << n) - 1;                 // n bits
    for (unsigned i = 0; i < n+1; ++i) {
        auto sub = (1ULL << i) - 1;             // i bits
        U64 x = sub; U64 y; 
        do {            
            setPrint(x);
            y = snoob(x, set);                  // get next subset
            x = y;
        } while ((y > sub));
    }
}


















string SolveTSP(vector<vector<int>> thegraph){

  for (int i = 0; i < PowerSets.size(); i++)
  {

    for (int j = 1; j < thegraph[0].size(); j++)
    {
      if (PowerSets[i].find(j) != PowerSets[i].end())
      {
//	cout << "If" << endl;
	continue;
      }
      else if (i == 0)
      {
//	cout << "else if" << endl;
	Key k;
	k.dest = j;
	k.source.insert(0);
	Value v;
	v.cost = thegraph[i][j];
	v.parent = i;
	DynamicProgramming.insert( {k, v} );
//	cout << "{ [ " << k.dest << "], [ " << v.cost << ", " << v.parent << " ] }" << endl;
//	for (set<int>::iterator itr = k.source.begin(); itr != k.source.end(); itr++)
//	  cout << *itr << " ";
//	cout << endl;
//	cout << "size: " << k.source.size() << endl;
      }
      else
      {
//	cout << "else" << endl;
	int min_so_far = 1000;
	int tmp_dest;
//	bool skip = false;
	set<int> tmp_source;
	Key tmp;
	Key k;
	k.dest = j;
	k.source = PowerSets[i];
	for (set<int>::iterator itr = PowerSets[i].begin(); itr != PowerSets[i].end(); ++itr)
	{
	string path = "";
	  tmp.dest = *itr;
/*	  if (tmp.dest == 10)
	  {
	    skip = true;
	    //cout << "failing1" << endl;
	    break;
	  }
*/	  if (PowerSets[i].size() == 1)
	  {
//	    skip = false;
	    //cout << "failing2" << endl;
	    tmp.source = PowerSets[i];
	    tmp.source.erase(tmp.dest);
	    tmp.source.insert(0);
	}
	  else
	  {
//	    skip = false;
//	    cout << "shouldnt be here" << endl;
	    tmp.source = PowerSets[i];
	    tmp.source.erase(tmp.dest);
	  }
//	  for (set<int>::iterator itr2 = tmp.source.begin(); itr2 != tmp.source.end(); itr2++)
//	    path += to_string(*itr2) + ", "; 
//	  cout << "Current item: " << j << " Path to it: [" << tmp.dest << ", " << path << "]" << endl; 
	 //cout << j << endl;
	  //cout << "tmp destination " << tmp.dest << endl;

	//  for (set<int>::iterator itr2 = tmp.source.begin(); itr2 != tmp.source.end(); itr2++)
	  //  cout << "values in tmp source "<< *itr2 << endl;

	  unordered_map<Key, Value, KeyHasher>::const_iterator got = DynamicProgramming.find(tmp);
	  if (got == DynamicProgramming.end())
	  {
	    cout << "Fail because couldn't find subset" << endl;
	    /*
	    for (unordered_map<Key, Value, KeyHasher>::const_iterator it; it = DynamicProgramming.begin(); it != DynamicProgramming.end(); it++)
	    {
	      cout << to_string(it->first) << " " << to_string(it->second) << endl;
	    }
	    */
	  }
//	  cout << got->second.cost  << endl;
//	  cout << thegraph[*itr][j] << endl;
	  if ((got->second.cost + thegraph[*itr][j]) < min_so_far)
	  {
	    //cout << "failing3" << endl;
	    min_so_far = (got->second.cost + thegraph[*itr][j]);
	    tmp_dest = tmp.dest;
	    tmp_source = tmp.source;
	    //tmp_source.erase(tmp_dest);
	  }
	}
//	if (!skip){
	Value v;
	v.cost = min_so_far;
	v.parent = tmp_dest;
//	cout << "min for path: " << min_so_far << endl;
	//cout << "min inserted: " << min_so_far << " Parent chosen: " << v.parent << endl;
	DynamicProgramming.insert( {k, v} );
/*	if ( i == 15){
	return "";
	}*/
//	}
	//else
//	  cout << "Testing" << endl;
      }

      //cout << "Looped: " << j << " amount of times." << endl;
    }
    //cout << "Subset: " << i << endl;
  }

//  cout << "Last Round" << endl;
    Key k;
    k.dest = 0;
    k.source = PowerSets[PowerSets.size() - 1];

    Key tmp;
    int min_so_far = 10000;
    int tmp_dest;
    set<int> tmp_source;

    for (set<int>::iterator itr = k.source.begin(); itr != k.source.end(); itr++)
    {
      tmp.dest = *itr;
      tmp.source = k.source;
      tmp.source.erase(tmp.dest);
      unordered_map<Key, Value, KeyHasher>::const_iterator got = DynamicProgramming.find(tmp);
      if ((got->second.cost + thegraph[*itr][0]) < min_so_far)
      {
	min_so_far = (got->second.cost + thegraph[*itr][0]);
	tmp_dest = tmp.dest;
	tmp_source = tmp.source;
      }
    }
  //  cout << min_so_far << " " << tmp_dest << endl;

    string solution = "";

    solution += "Tour: 0<-" + to_string(tmp_dest) + "<-";

    tmp.dest = tmp_dest;
    tmp.source = tmp_source;
    for (set<int>::iterator itr = k.source.end(); itr != k.source.begin(); itr--)
    {
	unordered_map<Key, Value, KeyHasher>::const_iterator got = DynamicProgramming.find(tmp);
	solution += to_string(got->second.parent) + "<-";
	tmp.dest = got->second.parent;
	if (tmp.source.size() == 1)
	  break;
	tmp.source.erase(tmp.dest);
    }
   // cout << "made it here" << endl;
    solution += "0    Length of tour: " + to_string(min_so_far);
  return solution;
}




//  ------------
// get list of ints from a file
vector < vector<int> >   getMatrixFromFile(string filename)
{
  vector <vector<int> > matrixFromFile;
    
  ifstream f;
  f.open(filename.c_str());
  if (f.fail())
    { cout << "There was a problem opening the file " << filename << endl;
      return matrixFromFile;
    }
  while (!f.fail())
    {
      string onerowfromfile;
      vector<int> onerow;
      getline(f,onerowfromfile);
      if (!f.fail())
	{
	  stringstream s(onerowfromfile);
	  while (s)
	    { int num;
	      s >> num;
	      if (s)
		onerow.push_back(num);
	    }
	  matrixFromFile.push_back(onerow);
	}
    }

  f.close();
  return matrixFromFile;
      
}
//---------------------------------
//---------------------------------
int main(int argc, char *argv[])
{
  clock_t tStart = clock();
  if ( argc != 2 ) // argc should be 2 for correct execution
  { cout<<"usage: "<< argv[0] <<" <filename> " << endl;;
    return 0;
  }

  string filename = argv[1];
  vector < vector<int> > thegraph = getMatrixFromFile(argv[1]);
  cout << "The matrix:" << endl;
  for (vector<int> onerow:thegraph)
  {
    for (int n : onerow)
      cout <<  n << " ";
    cout << endl;
  }


  // CAN PUT YOUR CODE / FUNCTION calls here.
  int row = thegraph[0].size();
  generatePowerSet(row - 1);
/*  for (int i = 0; i < PowerSets.size(); i++){
    for (set<int>::iterator it=PowerSets[i].begin(); it!=PowerSets[i].end(); ++it)
      cout << ' ' << *it;

    cout << endl;
  }
*/
  string result = SolveTSP(thegraph);

  //cout << PowerSets.size() << endl;

  string toFile = "";
  double time = (clock() - tStart)/CLOCKS_PER_SEC;
  toFile += filename + "  :  "  + to_string(time) + "\n";
  ofstream file;
  file.open("TimingResults.txt", ios::app);
  file << toFile;
  file.close();

  cout << result << endl;
  return 0;  
}
