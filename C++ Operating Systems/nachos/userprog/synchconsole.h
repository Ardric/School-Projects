#ifndef SYNCHCONSOLE_H
#define SYNCHCONSOLE_H

class Console;
class Lock;
class Semaphore;

class SynchConsole{
  public:
    SynchConsole();
    ~SynchConsole();
    void SynchPutChar(char ch);
    char SynchGetChar();
    
    void ReadAvail();
    void WriteDone();
  
    private:
    Console* console;
    Lock* SCL;
    Semaphore* readAvail;
    Semaphore* writeDone;
};
#endif
