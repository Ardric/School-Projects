#include "Socket.h"
#include "SocketSet.h"
#include <unistd.h>
#include <iostream>

using namespace std;



int main(int argc,char** argv){
	Socket socket;
	SocketSet socketSet;
	socket.open(argv[1],argv[2]);
	socket.writeInt(2);
	socket.joinGroup(&socketSet);
	string line = "";
	string msg = "";
	while(!socket.isClosed()){
		getline(cin,line);    
		if(line != ""){
			//execute a command
			if(line == "quit"){
				socket.close();
			}else{
				if(line.size() > 100)
					line = line.substr(0,100);
				socket.writeString(line);
				
				socketSet.wait(-1);
				if(socket.hasEvent()){
					socket.readString(msg,100);
					if(!socket.isClosed()){
						msg = "[server]:" + msg;
						cout << msg << endl;
					}
				}
			}
		}

	}
	return 0;
}
