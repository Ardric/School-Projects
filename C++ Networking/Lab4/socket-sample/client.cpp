#include "Socket.h"
#include "SocketSet.h"
#include "Console.h"
#include <curses.h>
#include <unistd.h>
#include <iostream>
#include <vector>
using namespace std;

WINDOW* window;
int width,height;
string msg = "";
vector <string> chat;
vector <string> log;
vector <string> server;
vector <string> error;
vector <string> errorcheck;
vector <string> hand;
vector <string> played;
Console console;

/*
string readTilCRLF(string msg)
{	
	string newmsg = "";
	for (int i = 0; i < msg.length(); ++i)
	{
		if (msg[i] == '\r')
			return newmsg;
		else
			newmsg[i] = msg[i];
	}
	return newmsg;
}
*/
void initCurses(){
    window = initscr();
    getmaxyx(window,height,width);
    nodelay(window,true);

    refresh();
}

void shutdownCurses(){
    delwin(window);
    endwin();
    refresh();
}

void drawScreen(){
    if(!console.needsDraw()){
        return;
    }
    clear();
    getmaxyx(window,height,width);
    
	attron(A_REVERSE);
		mvwvline(window, 0, width-27, ' ', height-12);
		mvwhline(window, height-12, 0, ' ', width);
	attroff(A_REVERSE);

	//If good message:
	if (msg.substr(0,1) == "+")
	{
		//Printing chat
		for (int i = 0; i < 9 && i < chat.size(); ++i)
		{
		    mvwaddstr(window,height-11+i, 0, chat[i].c_str());
		}
/*
		for (int i = 0; i < 9 && i < server.size(); ++i)
		{
			mvwaddstr(window, height-14, 0, server[i].c_str());
		}
*/	
		//Printing log
		for (int i = 0; i < log.size(); ++i)
		{
			mvwaddstr(window, 0+i, width-26, log[i].c_str());
		}
		//Printing hand
		for (int i = 0; i < hand.size(); ++i)
			mvwaddstr(window, height-13, 0, hand[i].c_str());
	
		if (msg != "" && msg.substr(0, 5) == "+PLYR")
		{
			mvwaddstr(window, height-14, 0, msg.c_str());
		}
		
	}
	//else if bad message
	else if (msg.substr(0,1) == "-")
	{
		mvwaddstr(window, height/2, width/2-2, msg.c_str());
		for(int i = 0; i < hand.size(); ++i)
		{
			mvwaddstr(window, height-13, 0, hand[i].c_str());
		}
		for (int i = 0; i < log.size(); ++i)
		{
			mvwaddstr(window, 0+i, width-26, log[i].c_str());
		}

	}
	string line = console.getBuffer();
	mvwaddstr(window, height-1, 0, line.c_str());
}


int main(int argc,char** argv){
	Socket socket;
    SocketSet socketSet;
    initCurses();
    socket.open(argv[1],argv[2]);
    socket.joinGroup(&socketSet);
    string line = "";
    console.reDraw();
    drawScreen();
    while(!socket.isClosed()){
        
        if(console.getLine(window,line)){
            //execute a command
            if(line == "QUIT"){
                socket.close();
            }else{
                if(line.size() > 256)
                    line = line.substr(0,256); 
                socket.writeString(line + "\r\n");
            }
        }else{
            socketSet.wait(0);
            if(socket.hasEvent()){
                socket.readString(msg,256);
//				msg = readTilCRLF(msg);
 				msg = msg.substr(0, msg.length()-2);
                if(!socket.isClosed()){
					if (chat.size() >= 9)
					{
						chat.erase(chat.begin(), chat.begin()+1);
					}
					if (log.size() >= 25)
					{
						log.erase(log.begin(), log.begin()+1);
					}

					if (msg.substr(0,1) == "+")
					{
						if (msg.substr(1, 4) == "QUIT")
						{
							server.push_back(msg);
						}
						if (msg.substr(1, 4) == "CHAT")
						{
							chat.push_back(msg);
						}
						else if (msg.substr(1, 4) == "HAND")
						{
							hand.push_back(msg.substr(6, 26));
					
						}
						if (msg.substr(1, 4) == "ACTV")
						{
							
							log.push_back(msg);
						}
						if (msg.substr(1, 4) == "PLYR")
						{
							if (server.size() > 0)
								server.erase(server.begin(), server.begin()+1);
							else
								server.push_back(msg);

						}
					}

					else
					{
						if (error.size() > 0)
							error.erase(error.begin(), error.begin()+1);
						else
							error.push_back(msg);
					}

                    console.reDraw();
                }
            }
        
        }
        drawScreen();
    }
    shutdownCurses();
	return 0;
}
