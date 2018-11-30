#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
//#include <utility>
using namespace std;

typedef struct Points
{
  double x, y;
};

class Node{

  public:
    	Node();
	~Node();
	//void Print();
	string MessageHandler( string msg, double xl, double xu, double yl, double yu );
	string Get( double X, double Y );
	string Set( double X, double Y, string Value );
	//string AdjustValues ( string bounds ); 
			
  private:
	//int NodeId;
	double lowerBound;
	double upperBound;
	//int address;
	int port;
	// pair < double, double > Points;
	 vector<Points> Nodes;
	unordered_map < int, string > Info;
	// node split with
};
#endif
