// threadtest.cc 
//	Simple test case for the threads assignment.
//
//	Create two threads, and have them context switch
//	back and forth between themselves by calling Thread::Yield, 
//	to illustratethe inner workings of the thread system.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "synch.h"

// testnum is set in main.cc
int testnum = 1;


void
do_nothing(int i){
  while(1)
    currentThread->Yield();
}

//----------------------------------------------------------------------
//Thread::Join Test
//----------------------------------------------------------------------
void
joinchild( int pid )
{
  if ( pid == 1){
    printf("Child forking and becoming a parent.\n");
    Thread *t = new Thread("secondchild", true);
    Thread *f = new Thread("thirdchild", true);
    t->Fork(joinchild, 2);
    currentThread->Join(t);
    f->Fork(joinchild, 3);
    currentThread->Join(f);
    printf("Children of original forked thread has finished and joined.\n");
  }
  
  else
    printf("Doing\n");
}

void
JoinTest()
{
  Thread *t = new Thread("forkedthread", true);
  t->Fork(joinchild, 1);
  //Thread *t2 = new Thread("nothing", false);
  //t2->Fork(do_nothing, 2);
  currentThread->Join(t);
  printf("Done\n");
}

//----------------------------------------------------------------------
//Condition Test
//----------------------------------------------------------------------
Lock L1("ConditionLock");
Condition C("ConditionTest");
int val = 0;

void
ConditionTest(int which)
{
  if ( which != 9 ) {
    L1.Acquire();
    printf("*** thread %d sees the value %d\n", which, val);
    C.Wait(&L1);
    printf("*** thread %d sees the value %d\n", which, val);
    L1.Release();
  }

  else{
    L1.Acquire();
    printf("*** thread %d sets value to 12\n", which);
    val = 12;
    C.Broadcast(&L1);
    L1.Release();
  }

  printf("*** thread %d has exited.\n", which);
}

void
TestCondition()
{
  for (int i = 0; i < 9; i++){
    Thread *t = new Thread("CondTest", false);
    t->Fork(ConditionTest, i+1);
  }
  printf("9 threads forked.\n");
}

//----------------------------------------------------------------------
//Lock Test
//----------------------------------------------------------------------
Lock L("TestingLock");

void
Locktest2(int which)
{
  if (which == 1){
    L.Acquire();
    printf("thread %d has the lock.\n", which);
  }

  else{
    printf("thread %d attempting to release lock.\n", which);
    L.Release();
  }
}

void
LockTest2()
{
  for (int i = 0; i < 2; i++){
    Thread *t = new Thread("Locktest", false);
    t->Fork(Locktest2, i+1);
  }
  printf("2 threads forked.\n");
}

void
Locktest1(int which)
{
  L.Acquire();
  printf("thread %d holds the lock.\n", which);
  while ( true ){
    currentThread->Yield();
  }
  L.Release();
}
  
  
void
LockTest1()
{
  for (int i = 0; i < 5; i++){
    Thread *t = new Thread("Locktest", false);
    t->Fork(Locktest1, i+1);
  }
  printf("5 threads forked\n");
}

//----------------------------------------------------------------------
// SimpleThread
// 	Loop 5 times, yielding the CPU to another ready thread 
//	each iteration.
//
//	"which" is simply a number identifying the thread, for debugging
//	purposes.
//----------------------------------------------------------------------



/*

int SharedVariable;
void
SimpleThread1(int which)
{
  int num, val;
  L.Acquire();
  printf("*** thread%d has the lock\n", which);
  currentThread->Yield();
}

void
SimpleThread(int which)
  
{
    int num, val;
    
    for (num = 0; num < 15; num++) {
      L.Acquire();
      val = SharedVariable;
      printf("*** thread %d sees value %d\n", which, val);
      SharedVariable = val+1;
      L.Release();
    }
    val = SharedVariable;
    printf("Thread %d sees final value %d\n", which, val);
}
*/
//----------------------------------------------------------------------
// ThreadTest1
// 	Set up a ping-pong between two threads, by forking a thread 
//	to call SimpleThread, and then calling SimpleThread ourselves.
//----------------------------------------------------------------------
/*
void
ThreadTest1(int n)
{
    DEBUG('t', "Entering ThreadTest1");

    for ( int i = 0; i < n; i++ ){
      Thread *t = new Thread("forked thread", true);
      t->Fork(ConditionTest, i+1);
    }
    ConditionTest(0);
}
*/
//----------------------------------------------------------------------
// ThreadTest
// 	Invoke a test routine.
//----------------------------------------------------------------------

void
ThreadTest(int n)
{
    switch (testnum) {
    case 1:
	LockTest1();
	break;
    case 2:
	LockTest2();
	break;
    case 3:
	TestCondition();
	break;
    case 4:
	JoinTest();
	break;
    default:
	printf("No test specified.\n");
	break;
    }
}

