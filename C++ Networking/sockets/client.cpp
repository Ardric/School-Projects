#include "Socket.h"
#include "SocketSet.h"
#include <unistd.h>
#include <iostream>

using namespace std;



int main(int argc,char** argv){
	Socket socket;
	SocketSet socketSet;
	socket.open(argv[1],argv[2]);
	socket.joinGroup(&socketSet);
	int value;

	cout << "Enter a value" << endl;
	cin >> value;

	while(value >= 0 && !socket.isClosed()){
	  socket.writeInt(value);
	  cin >> value;
	}

	//socket.writeInt(value);	

	//socket.readInt(&value);

	//cout << "Number returned from Server is: " << value << endl;

	socket.close();

	return 0;
}
