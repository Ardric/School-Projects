#ifndef CONSOLE__H
#define CONSOLE__H
#include <unistd.h>
#include <curses.h>
#include <string>

using namespace std;

class Console{
public:
    Console();
    bool getLine(WINDOW* window,string& line);
    void reDraw();
    bool needsDraw();
    string getBuffer();
private:
    bool update;
    string buffer;
    
};

#endif
