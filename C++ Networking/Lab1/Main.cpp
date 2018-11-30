#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <iomanip>
using namespace std;

int main ( int argc, char * argv[] ) {

  int offset = 0;
  int y = 0;
  int x = 0;
  vector<int> messageChunks;
  char buffer[5000];
  int count = 7;
  char space = 32;

  ifstream inFile;
  inFile.open(argv[1]);
  
  inFile.seekg(0, inFile.end);
  size_t length = inFile.tellg();
  inFile.seekg(0, inFile.beg);

  if (length > sizeof (buffer)) 
    length = sizeof(buffer);

  inFile.read(buffer, length);

  /*
  while (inFile >> message) {
    messageChunks.push_back(message);
  }
*/
  inFile.close();

  for ( int i = 0; i < length; ++i ) {


    if ( y == 4 ){
	  cout << "Vector Filled" << endl;
	  for (int i = 0; i < messageChunks.size(); ++i) {
	  cout << "Vector Value in Hex: " << hex << setfill('0') << setw(2) << messageChunks[i] <<" Vector Position: " << i << endl;
	  }

	  if ( i < (length - 1) ){
	  y = 0;
	  messageChunks.clear();
	 
	  if ( buffer[i] == '1' ) {
	    x += pow(2.0, count);
	    cout << "Value added after y==4: " << x << " Original Value: " << buffer[i] << " Count: " << count << endl;
	    --count;
	  }
	  else if ( buffer[i] == '0'){
	    x += 0;
	    cout << "Value added after y==4: " << x << " Original Value: " << buffer[i] << endl;
	    --count;
	  }
	  else {
	    cout << "Space found and added to vector" << endl;
	    messageChunks.push_back(space);
	    y++;
	    offset = -1;
	  }
	  }
	  else
	    cout << "No more bits to process. End of buffer." << endl;
	  
	  
	}
    
    else  {
      if ( offset == 0 || offset % 8 != 0 ){
	cout << "Adding up bits for Vector Position: " << y << " Value Processed: " << buffer[i] << endl;

     	if ( buffer[i] == '1' ){ 
	  x += pow(2.0, count);
	  cout << x <<endl;
	  --count;
	}
	else if ( buffer[i] == '0'){
	  x += 0;
	  cout << x << endl;
	  --count;
	}
      }
      
      else{
	  cout << "Byte has been finalized and is being pushed into vector. Value of byte is: " << x << endl;;
	  messageChunks.push_back(x);
	  ++y;

	  if ( i < (length - 1) ){
	  cout << "Handling first bit of new byte following push back. Value: " << buffer[i] << endl;
	  x = 0;
	  count = 7;

	  if ( buffer[i] == '1' ) {
	    x += pow(2.0, count);
	    cout << x <<endl;
	    --count;
	  }
	  else if ( buffer[i] == '0'){
	    x += 0;
	    cout << x << endl;
	    --count;
	  }
	   else {
	    cout << "Found a space" << endl;
	    messageChunks.push_back(space);
	    y++;
	    offset = -1;
	  }

	  }
	  else
	    cout << "No more bits to process. End of buffer." << endl;
	  
	 
	}
    }
    ++offset;
  }
	  for (int i = 0; i < messageChunks.size(); ++i) {
	    cout << "Position of Vector: " << i << " Value in position in hex: " << hex << setfill('0') << setw(2) << messageChunks[i] << endl;;
	  }
	  y = 0;
	  messageChunks.clear();
	  cout << endl;
	  
  return 0;

}
