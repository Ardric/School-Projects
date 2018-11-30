#include "Socket.h"
#include "Timer.h"
#include <vector>
using namespace std;

Socket listener;
vector<Socket> sockets;




int main(int argc,char** argv){
	SocketSet socketSet;
	listener.listen(argv[1]);
	listener.joinGroup(&socketSet);
    string msg = "";
    Timer watch;
    //start a 30 second timer
    watch.start(30);
    
	while(!listener.isClosed()){
        //wait at most 2 seconds -- on event it will interupt
		socketSet.wait(2);
        
        msg = "";
        
		if(listener.hasEvent()){
			Socket sock = listener.accept();
			sock.joinGroup(&socketSet);
            cout << sock.toString() << " has joined\n";
			sockets.push_back(sock);
		}else{
			for(int i =sockets.size()-1; i >=0; --i){
				if(sockets[i].hasEvent()){
                    int bytes = sockets[i].readString(msg,10);
                    if(!sockets[i].isClosed()){
                        cout << msg << "\n";
                        sockets[i].writeString(msg);
                    }else{
                        sockets.erase(sockets.begin()+i);
                    }
                }
			}
		}

        if(watch.timeLeft() == 0){
            for(int i =0; i < sockets.size(); ++i){
                sockets[i].writeString("time again");
            }
            watch.start(30);
        }
	}
	for(int i =0; i < sockets.size(); i++){
		sockets[i].close();
	}
	return 0;
}
