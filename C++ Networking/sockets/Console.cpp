#include "Console.h"

Console::Console(){
    update = false;
}

bool Console::needsDraw(){
    return update;
}

bool Console::getLine(WINDOW* window,string& line){
    int c = wgetch(window);
    update = true;
    if(c == 8 || c == 127){
        if(buffer.size() > 0){
            buffer.erase(buffer.size()-1);
        }
    }else if(c == '\n' || c == '\r'){
        line = buffer;
        buffer = "";
        return true;
    }else if(c > 0){
        buffer += c;
    }else{
        update = false;
    }
    line = buffer;
    return false;
}

void Console::reDraw(){
    update = true;
}

string Console::getBuffer(){
    return buffer;
}