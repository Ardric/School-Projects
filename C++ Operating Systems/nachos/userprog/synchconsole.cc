#include "synchconsole.h"
#include "../machine/console.h"
#include "../threads/synch.h"
//static Condition *readAvail;
//static Condition *writeDone;
//static Lock L = new Lock("Lock");

static void GlobalReadAvail(int arg) { SynchConsole * SC = (SynchConsole*) arg; SC->ReadAvail(); }
static void GlobalWriteDone(int arg) { SynchConsole * SC = (SynchConsole*) arg; SC->WriteDone(); }


SynchConsole::SynchConsole()
{
  char* readFile = NULL;
  char* writeFile = NULL;
  readAvail = new Semaphore("SemRead",0);
  writeDone = new Semaphore("SemWrite",0);
  SCL = new Lock("SCLock");
  console = new Console(readFile, writeFile, GlobalReadAvail, GlobalWriteDone, (int)this);
}

SynchConsole::~SynchConsole()
{
  delete console;
  delete SCL;
  delete readAvail;
  delete writeDone;
}

char SynchConsole::SynchGetChar()
{
  printf("In get char\n");
 char ch;

 SCL->Acquire();
 readAvail->P();
 ch = console->GetChar();
 printf("Retrieved character %c.\n", ch);
 SCL->Release();
 return ch;
}

void SynchConsole::SynchPutChar(char ch)
{
 SCL->Acquire();
 console->PutChar(ch);
 writeDone->P();
 SCL->Release();
}

void SynchConsole::ReadAvail()
{
  readAvail->V();
}

void SynchConsole::WriteDone() 
{
  writeDone->V();
}
