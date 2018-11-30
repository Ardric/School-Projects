#include "hashtable.h"



HashTable::HashTable()
{

Data d = { -1, -1, -1 };

//	HashTable* hasharray = new HashTable();

for(int i = 0; i < NumPhysPages; ++i)
{
 	HashArray[i] = d;
}

}


HashTable::~HashTable()
{
}

int
HashTable::hash(int vpn)
{
	return vpn % NumPhysPages;
}


void
HashTable::insert(int vpn, int pid, int ppn, bool use)
{
	int position = hash(vpn);
	if( HashArray[position].vpn == -1 )
	{	
	  	//printf("Inserting at position %d, values %d, %d, %d.\n", position, vpn, pid, ppn);
		Data d = { vpn, pid, ppn, use };
		HashArray[position] = d;
		return;
	}
	else{
		for( int i = (position + 1) % NumPhysPages; i < NumPhysPages + position + 1; i = (i + 1) % NumPhysPages)
		{
	//	  printf("%d\n", i);
			if( i == position )
				break;
			if( HashArray[i].vpn == -1 )
			{
	  	//		printf("Inserting at position %d, values %d, %d, %d.\n", i, vpn, pid, ppn);
				Data d = { vpn, pid, ppn, use };
				HashArray[i] = d;
				return;
			}

		}
	}
}




int
HashTable::check(int vpn, int pid)
{
	int position = hash(vpn);
	if( HashArray[position].vpn == vpn && HashArray[position].pid == pid)
	{
	  	//printf("Retrieving from position %d, values %d, %d.\n", position, vpn, pid);
		return HashArray[position].ppn;
	}
	else{
		for( int i = (position + 1) % NumPhysPages; i < NumPhysPages + position + 1; i = (i + 1) % NumPhysPages)
		{
			if( i == position )
				break;
			if( HashArray[i].vpn == vpn && HashArray[i].pid == pid)
			{
	  		//	printf("Retrieving from position %d, values %d, %d.\n", i, vpn, pid);
				return HashArray[i].ppn;
			}
		}
	}
	return -1;
}

int
HashTable::GetVPN(int ppn)
{
	if (HashArray[ppn].ppn == ppn){
	  return HashArray[ppn].vpn;
	}
	else{
	  for( int i = ppn + 1; i < NumPhysPages + ppn + 1; i = (i + 1) % NumPhysPages)
	  {
	    if (HashArray[i].ppn == ppn)
	      return HashArray[i].vpn;
	  }
	}
	return -1;
}

int
HashTable::GetPID(int ppn)
{
	if (HashArray[ppn].ppn == ppn){
	  return HashArray[ppn].pid;
	}
	else{
	  for( int i = ppn + 1; i < NumPhysPages + ppn + 1; i = (i + 1) % NumPhysPages)
	  {
	    if (HashArray[i].ppn == ppn){
	      return HashArray[i].pid;
	    }
	  }
	}
	return -1;
}

void
HashTable::update(int vpn, int pid)
{
	int position = hash(vpn);
	if( HashArray[position].vpn == vpn && HashArray[position].pid == pid)
	{
	  HashArray[position].use = true;
	}
	else{
		for( int i = (position + 1) % NumPhysPages; i < NumPhysPages + position + 1; i = (i + 1) % NumPhysPages)
		{
			if( i == position )
				break;
			if( HashArray[i].vpn == vpn && HashArray[i].pid == pid)
			{
			  HashArray[i].use = true;
			}
		}
	}
}
int
HashTable::adjust(int position)
{
  while (HashArray[position].use == true)
  {
    HashArray[position].use = false;
    position = (position + 1) % NumPhysPages;
  }

  return HashArray[position].ppn;
}

void
HashTable::remove(int ppn)
{
	if (HashArray[ppn].ppn == ppn){
	  HashArray[ppn].vpn = -1;
	  HashArray[ppn].pid = -1;
	  HashArray[ppn].ppn = -1;
	  HashArray[ppn].use = false;
	}
	else{
	  for( int i = ppn + 1; i < NumPhysPages + ppn + 1; i = (i + 1) % NumPhysPages)
	  {
	    if (HashArray[i].ppn == ppn){
	  //    printf("We found it\n");
	  HashArray[i].vpn = -1;
	  HashArray[i].pid = -1;
	  HashArray[i].ppn = -1;
	  HashArray[ppn].use = false;
	  break;
	    }
	  }
	}
}

void
HashTable::print()
{
  for( int i = 0; i < NumPhysPages; i++)
  {
    printf("Stored in location %d, values vpn: %d, pid: %d, ppn: %d. use: %d\n", i, HashArray[i].vpn, HashArray[i].pid, HashArray[i].ppn, HashArray[i].use);
  }
}

