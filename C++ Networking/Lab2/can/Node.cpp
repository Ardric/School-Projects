#include "Node.h"



  // Have some global data structure that keeps track of
  // all the nodes we have. If we are the main node, we
  // will run the following constructor.
  // 
  // Address and Port will need to be retrieved from the
  // command line somehow. Stubs for the moment.
  //
  // When checking or inserting, must check that the positions
  // are within the bounds of our node.

Node::Node()
{
  //lowerBound = 0.0000;
  //upperBound = 0.9999;
  //address = 223;
  //port = 9900;
  Points p = {0.300, 0.500};
  Nodes.push_back(p);
  int position = Nodes.size() - 1;
  Info.insert( {position, "Hello World"} );
  cout << "Node Created" << endl;
}

Node::~Node()
{
  cout << "Node Deleted" << endl;
}
/*
void Node::Print()
{

  for (int i = 0; i < 11; i++) {

    for (int j = 0; j < 21; j++) {

      if ( i % 2 == 0 ){

	if ( j % 2 == 0 )
	  cout << " ";

	else
	  cout << "-";

      }

      else{

	if ( j % 2 == 0 )
	  cout << "|";

	else if (allNodes.size() == 1)
	  cout << 0;
	else
	  cout << " ";

      }
    }
      cout << endl;
  }

  
  cout << "lowerBound & upperBound: " << lowerBound << " " << upperBound << endl;
  cout << "Address & Port number: " << address << " " << port << endl;
  cout << "Current contents of hashtable:" << endl;
  for ( auto it = Info.begin(); it != Info.end(); ++it ){
  	cout << "Position: " << it->first << " " << "Value: " << it->second << endl;
  }
  for ( unsigned i = 0; i < Nodes.size(); i++){
    cout << Nodes[i].x << " " << Nodes[i].y <<  endl;
  }
 
}
*/
//Parses message sent by client
//Decides whether it is a Get or Set
//Calls method Get or Set to perform action
//Receives value based on those methods and
//returns an appropriate string to be sent
//to client
//String Value is first else if needs to take
//a string of length 255, not 5

string Node::MessageHandler(string msg, double xl, double xu, double yl, double yu)
{
  string result;
  string str;

  if (msg.substr( 0, 3 ) == "Get")
  {
    //cout << msg << " " << msg.length() << endl;
    str = msg.substr( 4, 5 );
    //cout << str << endl;
    double X = stod(str);
    str = msg.substr( 10, 5 );
    //cout << str << endl;
    double Y = stod(str);
    if ( X >= xl && X < xu && Y >= yl && Y < yu ){
      result = Get( X, Y );
    }
    else if ( X >= 0 && X < 1 && Y >= 0 && Y < 1 ){
      //cout << "Hit the correct else" << endl;
      return msg;
    }
    else
      result = "Key given was not within bounds.";
  }

  else if (msg.substr( 0, 3 ) == "Set")
  {
    str = msg.substr( 4, 5 );
    double x = stod(str);
    str = msg.substr( 10, 5 );
    double y = stod(str);
    string value = msg.substr( 16, 255 );
    if ( x >= xl && x < xu && y >= yl && y < yu )
      result = Set( x, y, value );
    else if ( x >= 0 && x < 1 && y >= 0 && y < 1 ){
      //cout << "Hit the correct else" << endl;
      return msg;
    }
    else
      result = "Key given was not within bounds.";
  }
/*
  else if (msg.substr( 0, 5 ) == "Print")
  {
    Print();
  }
  */

  return result;
}


//For Get and Set will need to add code that checks bounds
//and pushes work to other neighbors if needed.
string Node::Get(double X, double Y){
  
  string value;
  for ( int i = 0; i < Nodes.size(); i++ )
  {
    if (Nodes[i].x == X && Nodes[i].y == Y)
    {
        // Want value to be the string at the key i
	value = Info[i];
	return "The value: "+value+" is contained at the point specified.\n";
    }
  }

  return "No value found at point specified.\n";

}
string Node::Set(double X, double Y, string Value){

  for ( int i = 0; i < Nodes.size(); i++ ){
    if (Nodes[i].x == X && Nodes[i].y == Y)
      return "Value already set at specified key";
  }
  Points p = { X, Y };
  Nodes.push_back(p);
  int position = Nodes.size() - 1;
  Info.insert( {position, Value} );
  return "Value: "+Value+" has been inserted into position: "+to_string(position)+"\n";
}
/*
string Node::AdjustValues(string bounds)
{
  string value = "";
  string x, y;

  double a = stod(bounds.substr(0, 5));
  double b = stod(bounds.substr(9, 5));
  double c = stod(bounds.substr(18, 5));
  double d = stod(bounds.substr(27, 5));

  for ( int i = 0; i < Nodes.size(); i++)
  {
    if (Nodes[i].x >= a && Nodes[i].x < b && Nodes[i].y <= c && Nodes[i].y > d){
      x = to_string(Nodes[i].x);
      y = to_string(Nodes[i].y);
      value.append(x+" "+y+":"+Info[i]);
      value.append(" ");
    }
  }
  return value;
}*/
