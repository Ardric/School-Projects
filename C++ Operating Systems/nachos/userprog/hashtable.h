#ifndef HASHTABLE_H
#define HASHTABLE_H


//#include <iostream>
#include "../machine/machine.h"

struct Data
{
	int vpn, pid, ppn;
	bool use;
};

class HashTable {


public:
HashTable();

~HashTable();
 

int hash(int vpn);

void insert(int pid, int vpn, int ppn, bool use);

int check(int vpn, int pid);

int GetPID(int ppn);

int GetVPN(int ppn);

int adjust(int position);

void update(int vpn, int pid);

void remove(int ppn);

void print();

private:
Data HashArray[NumPhysPages];
};




#endif // HASHTABLE_H
