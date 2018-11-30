#include "Socket.h"
#include "Timer.h"
#include <vector>
using namespace std;

Socket listener;
vector<Socket> sockets;
vector<int> Sums;




int main(int argc,char** argv){
	SocketSet socketSet;
	listener.listen(argv[1]);
	listener.joinGroup(&socketSet);
    	int msg;
    
	while(!listener.isClosed()){
	 socketSet.wait(2); 
	  if(listener.hasEvent()){
	    Socket sock = listener.accept();
	    sock.joinGroup(&socketSet);
            cout << sock.toString() << " has joined\n";
	    sockets.push_back(sock);
	    Sums.push_back(0);
	  
	  }else{
	    
	    for(int i = sockets.size()-1; i >=0; --i){
	      
	      if(sockets[i].hasEvent()){
		sockets[i].readInt(&msg);
                    
		if(!sockets[i].isClosed()){
		    cout << "Client " << i << " input the value: " << msg << "\n";
		    Sums[i] += msg;
                
		}else{
		  cout << "Sum for client " << i << " is: " << Sums[i] << endl;
		  sockets.erase(sockets.begin()+i);
		  Sums[i] = 0;
                }
              }
	    }
	  }

        
	  }

	for(int i =0; i < sockets.size(); i++){
		sockets[i].close();
	}
	return 0;

}
