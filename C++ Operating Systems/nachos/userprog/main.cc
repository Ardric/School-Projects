#include <iostream>
#include "hashtable.h"
using namespace std;

int main()
{
	HashTable *test = new HashTable;
	
	test->insert( 32, 0, 12 );
	cout << "First insert successful" << endl;
	test->insert( 0, 0, 14 );
	cout << "Second insert successful" << endl;

	//test->print();
	int ppn = test->check( 32, 0 );

	cout << ppn << endl;
	
	ppn = test->check( 0, 0 );
	cout << ppn << endl;

	return 0;
}
