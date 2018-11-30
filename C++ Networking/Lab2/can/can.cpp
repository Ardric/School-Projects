#include "Socket.h"
#include "Node.h"
#include <vector>
#include <iomanip>
#include <sstream>
using namespace std;

Socket listener;
Socket client;
Node *N = new Node;

struct Message{
	int type;
};

struct Router{
	Socket socket;
	double xl;
	double xu;
	double yl;
	double yu;
};


vector<Router> peeps;

string NewBounds(Router &router, Router &r){
  // We have a square, split to rectangles
  string a, b, c, d, e, f, g, h;
  if (router.xl == router.yl && router.xu == router.yu){
	b = to_string(router.xu);
	r.xu = router.xu;
	router.xu = router.xu / 2;
	a = to_string(router.xu);
	r.xl = router.xu;
	router.xu = router.xu - 0.001;

	c = to_string(router.yl);
	r.yl = router.yl;
	d = to_string(router.yu);
	r.yu = router.yu;

        //cout << router.xl << " " << router.xu << " " << router.yl << " " << router.yu << endl;
	//cout << a+" "+b+" "+c+" "+d << endl;
	
	e = to_string(router.xl);
	f = to_string(router.xu);
	g = to_string(router.yl);
	h = to_string(router.yu);
	return a+" "+b+" "+c+" "+d+" "+e+" "+f+" "+g+" "+h;

  }
  // We have a rectangle, split to squares
  else{
    	a = to_string(router.xl);
	r.xl = router.xl;
	b = to_string(router.xu);
	r.xu = router.xu;

	d = to_string(router.yu);
	r.yu = router.yu;

	router.yu = router.yu / 2;
	c = to_string(router.yu);
	r.yl = router.yu;
	router.yu = router.yu - 0.001;

  //cout << router.xl << " " << router.xu << " " << router.yl << " " << router.yu << endl;
	e = to_string(router.xl);
	f = to_string(router.xu);
	g = to_string(router.yl);
	h = to_string(router.yu);
//	cout << a+" "+b+" "+c+" "+d << endl;
	return a+" "+b+" "+c+" "+d+" "+e+" "+f+" "+g+" "+h;
  }
}
Message readMessage(Socket& sock){
	Message msg;
	if(0 > sock.readInt(&msg.type)){
		msg.type = -1;
	}
	return msg;
}

int whoOwns(Router router, double x, double y){
  Router r;
  //cout << x << " " << y << endl;
  //cout << router.xl << " " << router.xu << " " << router.yl << " " << router.yu << endl;
  if (router.xl <= x && router.xu >= x && router.yl <= y && router.yu > y)
    return 0;
  
  else{
    for (int i = 0; i < peeps.size(); i++)
    {
      r = peeps[i];
      //cout << r.xl << " " << r.xu << " " << r.yl << " " << r.yu << endl;
      if (r.xl <= x && r.xu >= x && r.yl <= y && r.yu > y)
	return i + 1;
    }
  }
  return 4;
}
void Print(Router router)
{
  double x = 0.099;
  double y = 0.999;
  //cout << router.xl << " " << router.xu << " " << router.yl << " " << router.yu << endl;
  int owner;
    for (int i = 0; i < 21; i++) {
  
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
  
          else if (peeps.size() == 0)
            cout << 0;

	  else if (peeps.size() > 0){
	    owner = whoOwns(router, x, y);
	    cout << owner;
	    x += 0.100;
	    if ( j == 19 ){
	      y -= 0.100;
  	      x = 0.099;	
	    }
	  }
          else
            cout << " ";
  
        }	  
      }
        cout << endl;
    }
}


int main(int argc,char** argv){
	SocketSet socketSet;
	listener.listen(argv[1]);
	listener.joinGroup(&socketSet);
	Router router;
	if (argc == 4) {
	  string line;
	  Socket sock;
	  Router r;
	  cout << "Made it here" << endl;
	  sock.open(argv[2], argv[3]);
	  //r.socket = sock;
	  sock.joinGroup(&socketSet);
	  sock.writeInt(1);
	  sock.readString(line, 100);
	  router.xl = stod(line.substr(0, 5));
	  router.xu = stod(line.substr(9, 5));
	  router.yl = stod(line.substr(18, 5));
	  router.yu = stod(line.substr(27, 5));
	  r.xl = stod(line.substr(36, 5));
	  r.xu = stod(line.substr(45, 5));
	  r.yl = stod(line.substr(54, 5));
	  r.yu = stod(line.substr(63, 5));
	  //sock.readString(line, 100);
	  //cout << line << endl;
	  r.socket = sock;
	  peeps.push_back(r);
	  //cout << router.xl << " " << router.xu << " " << router.yl << " " << router.yu << " " << r.xl << " " << r.xu << " " << r.yl << " " << r.yu << endl;
	}
	else {
		router.xl = 0.000;
        	router.xu = 1.000;
		router.yl = 0.000;
		router.yu = 1.000;	
		cout << "Original bounds being set for first node: ";
		cout << "(" <<  router.xl << ", " << router.xu << ") (" << router.yl << ", " << router.yu << ")" << endl;
	}
    
	while(!listener.isClosed()){
        //wait at most 2 seconds -- on event it will interupt
		socketSet.wait(2);
        
		if(listener.hasEvent()){
			Socket sock = listener.accept();
			Message msg = readMessage(sock);
			cout << msg.type << endl;
			if(msg.type == 1){
			        string bounds;
				Router r;
				sock.joinGroup(&socketSet);
				cout << sock.toString() << " has joined\n";
				r.socket = sock;
				//write bounds to connecting router
				bounds = NewBounds(router, r);
				r.socket.writeString(bounds);
				//bounds = N->AdjustValues(bounds);
				//cout << bounds << endl;
				//r.socket.writeString(bounds);
				peeps.push_back(r);
				for (int i = 0; i < peeps.size(); i++){
				  	Router x = peeps[i];
					cout << "Original node new bounds: ";
					cout << "(" <<  router.xl << ", " << router.xu << ") (" << router.yl << ", " << router.yu << ")" << endl;
					cout << "New bounds given to joining node: ";
  					cout << "(" << x.xl << ", " << x.xu << ") (" << x.yl << ", " << x.yu << ")" << endl;
				}
			}else if(msg.type == 2){
				sock.joinGroup(&socketSet);
				client = sock;
			}/*
			else if(msg.type == 3){
			  cout << "Made it to other node" << endl;
			  string line;
			  sock.readString(line, 100);
			  cout << line << endl;
			  line = N->MessageHandler(line, router.xl, router.xu, router.yl, router.yu);
			  sock.writeString(line);
			}
			*/else{
				sock.close();
			}
		}else if(client.hasEvent()){
			//Message msg = readMessage();
			if(!client.isClosed()){
				string line;
				client.readString(line,100);
				if (line == "Print"){
				  cout << line.size() << endl;
				  Print(router);
				}

				line = N->MessageHandler(line, router.xl, router.xu, router.yl, router.yu);
				if (line.substr(0,3) == "Get" || line.substr(0,3) == "Set"){
				  if (peeps.size() > 0){
					for (int i = 0; i < peeps.size(); i++) {
					  peeps[i].socket.writeInt(3);
					  cout << line << endl;
					  peeps[i].socket.writeString(line);
					  peeps[i].socket.readString(line, 100);
					}
				  }
				}
				client.writeString(line);
			}
		}else{
			for(int i=peeps.size()-1; i >= 0; --i){
				if(peeps[i].socket.hasEvent()){
				  cout << "Event triggered from peep" << endl;
					Message msg = readMessage(peeps[i].socket);
					if(peeps[i].socket.isClosed()){
						//remove
						peeps.erase(peeps.begin()+i);
					}else{
					  if (msg.type == 3){
					        string line;
						peeps[i].socket.readString(line, 100);
			  			cout << line << endl;
			  			line = N->MessageHandler(line, router.xl, router.xu, router.yl, router.yu);
						cout << line << endl;
			  			peeps[i].socket.writeString(line);}

					}
				}
			}
		}
	}
	for(int i =0; i < peeps.size(); i++){
		peeps[i].socket.close();
	}
	return 0;
}
