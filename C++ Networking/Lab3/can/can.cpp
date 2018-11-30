#include "Socket.h"
#include <fstream>
#include <vector>
using namespace std;

Socket listener;
Socket client;

struct FileList{
  	string file;
	int deleted = 0;
};

struct Message{
	int type;
};

struct Client{
	Socket socket;
	int state = 0;
	int Username = -1;
};


vector<Client> peeps;

Message readMessage(Socket& sock){
	Message msg;
	if(0 > sock.readInt(&msg.type)){
		msg.type = -1;
	}
	return msg;
}

struct Users{
  string Username;
  string Password;
  vector <FileList> Emails;
};

vector <Users> Accounts;

string ParseRequest(string line, Client &client)
{
	string cmd = line.substr(0, 4);

	if (cmd == "SPEC"){
	  return to_string(client.state);
	}
	//If clients state is AUTH
	if(client.state == 0){	
		if (cmd == "USER"){
		  for (int i = 0; i < Accounts.size(); i++){
			if (line.substr(5, 6) == Accounts[i].Username){
		  	  client.state = 1;
			  client.Username = i;
		  	  return "+OK valid username\r\n";
			}
		  }
		  	  return "-ERR invalid username\r\n";
		}
		else if (cmd == "QUIT"){
			return "+OK POP3 server signing off\r\n";
		}
		else
		  return "-ERR invalid command for current state\r\n";
	}

	else if (client.state == 1){
		if (cmd == "PASS"){
		  	if (line.substr(5, 6) == Accounts[client.Username].Password){
		    	  client.state = 2;
		    	  return "+OK valid password\r\n";
			}
			else
			  return "-ERR invalid password\r\n";
		}
		else if (cmd == "QUIT"){
			return "+OK POP3 server signing off\r\n";
		}
		else
		  return "-ERR invalid command for current state\r\n";
	}
	
        //If the clients state is TRANS
	else if (client.state == 2){
		      if (cmd == "STAT"){
			int marked = 0;
			int bytes = 0;
		        char c;
			if (line.length() > 4)
				return "-ERR no arugments with STAT\r\n";	  
			for (int i = 0; i < Accounts[client.Username].Emails.size(); i++)
			{
			  if (Accounts[client.Username].Emails[i].deleted == 0){
			    ifstream f;
			    f.open(Accounts[client.Username].Emails[i].file);
			    while (f.get(c)){
			      bytes++;
			    }
			    f.close();
			    marked++;
			  }
			}
			return "+OK " + to_string(marked) + " " + to_string(bytes) + "\r\n";
		      }
		      else if (cmd == "LIST"){
			int emails = 0;
			int bytes = 0;
			char c;

			if (line.size() > 4){
			int arg = stoi(line.substr(5, 1));
			int choose = 0;
		      	for (int i = 0; i < Accounts[client.Username].Emails.size(); i++){
			  if (Accounts[client.Username].Emails[i].deleted == 0){
			    emails++;
			  }
			}
			if (arg > 0 && arg <= emails){
			  for (int i = 0; i < Accounts[client.Username].Emails.size(); i++){
			    if (Accounts[client.Username].Emails[i].deleted == 0){
				choose++;
				if (arg == choose){
				  ifstream f;
				  f.open(Accounts[client.Username].Emails[i].file);
				  while (f.get(c)){
				    bytes++;
				  }
				  f.close();
				  return "+OK " + to_string(arg) + " " + to_string(bytes) + "\r\n";
				}
			    }
			  }
			}
			else
			  return "-ERR no such message, only " + to_string(emails) + " messages in maildrop\r\n";
			}
			else{
			  string info = "";
			  int tmp = 0;
			  int choose = 0;
			for (int i = 0; i < Accounts[client.Username].Emails.size(); i++)
			{
			  if (Accounts[client.Username].Emails[i].deleted == 0){
			    choose++;
			    ifstream f;
			    f.open(Accounts[client.Username].Emails[i].file);
			    while (f.get(c)){
			      bytes++;
			      tmp++;
			    }
			    f.close();
			    emails++;
			    info = info + " " + to_string(choose) + " " + to_string(tmp) + "\r\n";
			    tmp = 0;
			  }
			}
			return "+OK " + to_string(emails) + " messages (" + to_string(bytes) + " octets)\r\n" + info + ".\r\n";
			}

		      }
		      else if (cmd == "RETR"){
			if (line.size() == 4)
			  return "-ERR no such message\r\n";
			else{
			  int bytes = 0;
			  int arg = stoi(line.substr(5, 1));
			  string msg = "";
			  char c;
			  int choose = 0;

			  for (int i = 0; i < Accounts[client.Username].Emails.size(); i++){
			    if (Accounts[client.Username].Emails[i].deleted == 0){
			      ++choose;
			      if (arg == choose){
				ifstream f;
				f.open(Accounts[client.Username].Emails[i].file);
				while (f.get(c)){
				  bytes++;
				  msg = msg + c;
				}
				f.close();
				return "+OK " + to_string(bytes) + " octets\r\n" + msg + ".\r\n";
			      }
			    }
			  }
			  return "-ERR no such message\r\n";
			}
		      }
		      else if (cmd == "DELE"){
			if(line.size() == 4)
			  return "-ERR no such message\r\n";
			else{
			  int arg = stoi(line.substr(5, 1));
			  int choose = 0;
			  for (int i = 0; i < Accounts[client.Username].Emails.size(); i++)
			  {
			    if (Accounts[client.Username].Emails[i].deleted == 0){
			      choose++;
			      if (choose == arg){
			      	Accounts[client.Username].Emails[i].deleted = 1;
				return "+OK message " + to_string(choose) + " deleted\r\n";
			      }
			    }
			  }
			  return "-ERR no such message\r\n";
		      }
		      }
		      else if (cmd == "NOOP"){
		      	if (line.size() > 4)
			  return "-ERR no arguments with NOOP\r\n";
			else
			  return "+OK\r\n";
		      }
		      else if (cmd == "RSET"){
		      	if (line.size() > 4)
			  return "-ERR no arguments with RSET\r\n";
			else{
			  int bytes = 0;
			  char c;
			  for (int i = 0; i < Accounts[client.Username].Emails.size(); i++){
			    ifstream f;
			    f.open(Accounts[client.Username].Emails[i].file);
			    while (f.get(c)){
			      bytes++;
			    }
			    f.close();
			    if (Accounts[client.Username].Emails[i].deleted == 1)
			      Accounts[client.Username].Emails[i].deleted = 0;
			  }
			return "+OK maildrop has " + to_string(Accounts[client.Username].Emails.size()) + " messages " + to_string(bytes) + " octets\r\n";
			}
		      }
		      else if (cmd == "QUIT"){
			int remain = 0;
			for (int i = 0; i < Accounts[client.Username].Emails.size(); i++){
			  if (Accounts[client.Username].Emails[i].deleted == 0)
			    remain++;
			}

			return "+OK POP3 server signing off (" + to_string(remain) + " messages left)\r\n";
		      }
		else
		  return "-ERR invalid command for current state\r\n";
		      //return command invalid

	}
}


int main(int argc,char** argv){
	SocketSet socketSet;
	listener.listen(argv[1]);
	listener.joinGroup(&socketSet);

	Users u;
	u.Username = "Daniel";
	u.Password = "Secure";
	FileList file;
	file.file = "Email0.txt";
	u.Emails.push_back(file);
	file.file = "Email1.txt";
	u.Emails.push_back(file);
	file.file = "Email2.txt";
	u.Emails.push_back(file);
	Accounts.push_back(u);

	Users x;
	x.Username = "Liz";
	x.Password = "Lizard";
	file.file = "Email3.txt";
	x.Emails.push_back(file);
	file.file = "Email4.txt";
	x.Emails.push_back(file);
	file.file = "Email5.txt";
	x.Emails.push_back(file);
	Accounts.push_back(x);
    
	while(!listener.isClosed()){
        //wait at most 2 seconds -- on event it will interupt
		socketSet.wait(2);
        
		if(listener.hasEvent()){
			Socket sock = listener.accept();
			Message msg = readMessage(sock);
			cout << msg.type << endl;
			if(msg.type == 1){
				//Router r;
				//sock.joinGroup(&socketSet);
				//cout << sock.toString() << " has joined\n";
				//r.socket = sock;
				//peeps.push_back(r);
			}else if(msg.type == 2){
				sock.joinGroup(&socketSet);
				Client c;
				c.socket = sock;
				peeps.push_back(c);
				//client = sock;
				c.socket.writeString("+OK POP3 server ready\r\n");
			}else{
				sock.close();
			}
		}else if(client.hasEvent()){
			//Message msg = readMessage();
			if(!client.isClosed()){
				string line;
				client.readString(line,100);
				//ParseRequest(line);
				client.writeString(line);
			}
		}else{
		  string line = "";
			for(int i=peeps.size()-1; i >= 0; --i){
				if(peeps[i].socket.hasEvent()){
				//	Message msg = readMessage(peeps[i].socket);
					peeps[i].socket.readString(line,100);
					string tmp = line;
					line = ParseRequest(line, peeps[i]);
					peeps[i].socket.writeString(line);
					if (tmp == "QUIT"){
						peeps[i].socket.close();
					}		
					if(peeps[i].socket.isClosed()){
						//remove
						peeps.erase(peeps.begin()+i);
					}else{

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
