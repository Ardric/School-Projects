#include "Socket.h"
#include "SocketSet.h"
#include "Console.h"
#include <curses.h>
#include <unistd.h>
#include <iostream>

using namespace std;

WINDOW* window;
int width,height;
string msg = "";
Console console;

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
    
    mvwaddstr(window,height/2,width/2-msg.size()/2,msg.c_str());
    
    string line = console.getBuffer();
    mvwaddstr(window,height-1,0,line.c_str());
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
            if(line == "quit"){
                socket.close();
            }else{
                if(line.size() > 10)
                    line = line.substr(0,10);
                socket.writeString(line);
            }
        }else{
            socketSet.wait(0);
            if(socket.hasEvent()){
                socket.readString(msg,10);
                if(!socket.isClosed()){
                    flash();
                    msg = "[server]:" + msg;
                    console.reDraw();
                }
            }
        
        }
        drawScreen();
    }
    shutdownCurses();
	return 0;
}
