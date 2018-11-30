// addrspace.cc 
//	Routines to manage address spaces (executing user programs).
//
//	In order to run a user program, you must:
//
//	1. link with the -N -T 0 option 
//	2. run coff2noff to convert the object file to Nachos format
//		(Nachos object code format is essentially just a simpler
//		version of the UNIX executable object code format)
//	3. load the NOFF file into the Nachos file system
//		(if you haven't implemented the file system yet, you
//		don't need to do this last step)
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "addrspace.h"
#include "synch.h"
#ifdef HOST_SPARC
#include <strings.h>
#endif



//----------------------------------------------------------------------
// SwapHeader
// 	Do little endian to big endian conversion on the bytes in the 
//	object file header, in case the file was generated on a little
//	endian machine, and we're now running on a big endian machine.
//----------------------------------------------------------------------

static void 
SwapHeader (NoffHeader *noffH)
{
	noffH->noffMagic = WordToHost(noffH->noffMagic);
	noffH->code.size = WordToHost(noffH->code.size);
	noffH->code.virtualAddr = WordToHost(noffH->code.virtualAddr);
	noffH->code.inFileAddr = WordToHost(noffH->code.inFileAddr);
	noffH->initData.size = WordToHost(noffH->initData.size);
	noffH->initData.virtualAddr = WordToHost(noffH->initData.virtualAddr);
	noffH->initData.inFileAddr = WordToHost(noffH->initData.inFileAddr);
	noffH->uninitData.size = WordToHost(noffH->uninitData.size);
	noffH->uninitData.virtualAddr = WordToHost(noffH->uninitData.virtualAddr);
	noffH->uninitData.inFileAddr = WordToHost(noffH->uninitData.inFileAddr);
}

//----------------------------------------------------------------------
// AddrSpace::AddrSpace
// 	Create an address space to run a user program.
//	Load the program from a file "executable", and set everything
//	up so that we can start executing user instructions.
//
//	Assumes that the object code file is in NOFF format.
//
//	First, set up the translation from program memory to physical 
//	memory.  For now, this is really simple (1:1), since we are
//	only uniprogramming, and we have a single unsegmented page table
//
//	"executable" is the file containing the object code to load into memory
//----------------------------------------------------------------------

AddrSpace::AddrSpace(OpenFile *executable)
{
    L = new Lock("bitLock");
    unsigned int i, size;
    loadFile = executable;
    loadFile->ReadAt((char *)&noffH, sizeof(noffH), 0);
    if ((noffH.noffMagic != NOFFMAGIC) && 
		(WordToHost(noffH.noffMagic) == NOFFMAGIC))
    	SwapHeader(&noffH);
    ASSERT(noffH.noffMagic == NOFFMAGIC);
// how big is address space?
    size = noffH.code.size + noffH.initData.size + noffH.uninitData.size 
			+ UserStackSize;	// we need to increase the size
						// to leave room for the stack
    numPages = divRoundUp(size, PageSize);
    size = numPages * PageSize;

    //ASSERT(numPages <= NumPhysPages);		// check we're not trying
						// to run anything too big --
						// at least until we have
						// virtual memory

    DEBUG('a', "Initializing address space, num pages %d, size %d\n", 
					numPages, size);

    //Checks what physical memory is available and what physical memory is available
    //If we try to load a process that is greater than the remaining size of physical memory
    //	we ASSERT that we have passed our limit
    /*
    if (bitMap->Test(0) == false)
      x = 0;
    else {
      for (unsigned int j = 0; j < NumPhysPages; j++)
      {
	printf("Made it here for Exec!");
	if (bitMap->Test(j) == false){
	  x = j;

	  if ((NumPhysPages - j) < size)
	    ASSERT("Not enough remaining pages for new process");
	}
      }
    }*/



   //x states where we are in physical memory
   //Used to keep track of our physical pages our virtual pages map to
   //Also ensures we are zeroing out only the phyiscal pages the new process
   //	is going to use
// first, set up the translation
/*
   L->Acquire(); 
    pageTable = new TranslationEntry[numPages];
    for (i = 0; i < numPages; i++) {
	pageTable[i].virtualPage = i;	// for now, virtual page # = phys page #
	int x = bitMap->Find();
	pageTable[i].physicalPage = x;
	pageTable[i].valid = FALSE;
	pageTable[i].use = FALSE;
	pageTable[i].dirty = FALSE;
	pageTable[i].readOnly = FALSE;  // if the code segment was entirely on 
					// a separate page, we could set its 
					// pages to be read-only
	bitMap->Mark(i);
        bzero(&machine->mainMemory[PageSize * x], PageSize);
    }
    L->Release();*/
/*
    L->Acquire();
    	tlb = new TranslationEntry[4];
	for (i = 0; i < 4; i++){
	  tlb[i].virtualPage = i;
	  int x = bitMap->Find();
	  tlb[i].physicalPage = x;
	  tlb[i].valid = TRUE;
	

	  bitMap->Mark(i);
	  bzero(&machine->mainMemory[PageSize * x], PageSize);
	}
    L->Release();
  */  
// zero out the entire address space, to zero the unitialized data segment 
// and the stack segment

// then, copy in the code and data segments into memory

/*
    if (noffH.code.size > 0) {
        DEBUG('a', "Initializing code segment, at 0x%x, size %d\n", 
			noffH.code.virtualAddr, noffH.code.size);


	int NumCodePages = noffH.code.size / PageSize;
	int restCode = noffH.code.size - (NumCodePages * PageSize); // get left over code

	for (i = 0; i < NumCodePages; i++){
	  int vaddrCode = noffH.code.virtualAddr + i * PageSize;
	  int vpn = vaddrCode / PageSize;
	  int offset = vaddrCode % PageSize;
	  int paddrCode = pageTable[vpn].physicalPage * PageSize + offset;
	  executable->ReadAt(&(machine->mainMemory[paddrCode]), PageSize, noffH.code.inFileAddr + (i * PageSize));
	}

	int vaddrCode = noffH.code.virtualAddr + NumCodePages * PageSize;
	int vpn = vaddrCode / PageSize;
	int offset = vaddrCode % PageSize;
	int paddrCode = pageTable[vpn].physicalPage * PageSize + offset;
	executable->ReadAt(&(machine->mainMemory[paddrCode]), restCode, noffH.code.inFileAddr + (NumCodePages * PageSize));
    }



    if (noffH.initData.size > 0) {
        DEBUG('a', "Initializing data segment, at 0x%x, size %d\n", 
			noffH.initData.virtualAddr, noffH.initData.size);

    int NumDataPages = noffH.initData.size / PageSize;
    int restData = noffH.initData.size - (NumDataPages * PageSize);
    
    for (i = 0; i < NumDataPages; i++) {
        int vaddrData = noffH.initData.virtualAddr + i * PageSize;
	int vpn = vaddrData / PageSize;
	int offset = vaddrData % PageSize;
	int paddrData = pageTable[vpn].physicalPage * PageSize + offset;
        executable->ReadAt(&(machine->mainMemory[paddrData]), PageSize, noffH.initData.inFileAddr + (i * PageSize));
	}

    	int vaddrData = noffH.initData.virtualAddr + NumDataPages * PageSize;
	int vpn = vaddrData / PageSize;
	int offset = vaddrData % PageSize;
	int paddrData = pageTable[vpn].physicalPage * PageSize + offset;
	executable->ReadAt(&(machine->mainMemory[paddrData]), restData, noffH.initData.inFileAddr + (NumDataPages * PageSize));
    }



//replace i with virtualaddrs * page = new addrs
*/
}

//----------------------------------------------------------------------
// AddrSpace::~AddrSpace
// 	Dealloate an address space.  Nothing for now!
//----------------------------------------------------------------------

AddrSpace::~AddrSpace()
{
   delete pageTable;
   delete loadFile;
}

//----------------------------------------------------------------------
// AddrSpace::InitRegisters
// 	Set the initial values for the user-level register set.
//
// 	We write these directly into the "machine" registers, so
//	that we can immediately jump to user code.  Note that these
//	will be saved/restored into the currentThread->userRegisters
//	when this thread is context switched out.
//----------------------------------------------------------------------
int tlbCount = 0;
int previousID = 0;
int fifo = 0;
//---------------------------------------------------------------------
//Most likely need a lock around swap code
void
AddrSpace::Load(int vaddr)
{
  L->Acquire();
	stats->numPageFaults++;
	int vpn = vaddr / PageSize;

	//Is there a different thread running?
/*	if ( previousID != currentThread->space->ID )
	{
	  RestoreState();
	  previousID = currentThread->space->ID;
	}
*/
	//Is the page in our IvPT?
	int ppn = IvPT->check(vpn, currentThread->space->ID);
	if( ppn != -1 )
	{
	  IvPT->update(vpn, currentThread->space->ID);
	  
	machine->tlb[tlbCount].virtualPage = vpn;
        machine->tlb[tlbCount].physicalPage = ppn;
        machine->tlb[tlbCount].valid = TRUE;
        machine->tlb[tlbCount].use = TRUE;
        machine->tlb[tlbCount].dirty = FALSE;
        machine->tlb[tlbCount].readOnly = FALSE;

	tlbCount = (tlbCount + 1) % 4;
	}

	

	else{


        int x = bitMap->Find();


	//If its not in our IvPT and Main Memory is filled check swap
	//
	//If its in swap, load it from swap and put the page we are replacing
	//in swap
	//
	//Else its not in swap, load the page we are replacing in Main memory
	//to swap then update everything with new page
	if ( x == -1 )
	{
	  //printf("We hit swap\n");
	  //printf("%d %d\n", vpn, currentThread->space->ID);
	  //printf("%d\n", fifo);
	  //IvPT->print();
	  if( freeswap->Test(( MAXVPNS * currentThread->space->ID) + vpn) == true )
	  {

	    fifo = IvPT->adjust(fifo);

	    //printf("Swap had the file.\n");
	    //Location of page to be written to main memory
	    int SwapPos = ((MAXVPNS * currentThread->space->ID) + vpn) * PageSize;
	
            //Write the page we are replacing in main memory to swap
	    int m_vpn = IvPT->GetVPN(fifo);
	    int m_pid = IvPT->GetPID(fifo);
	    int MainPos = ((( NumPhysPages * m_pid) + m_vpn) * PageSize);

	    Swap->WriteAt(&(machine->mainMemory[fifo*PageSize]), PageSize, MainPos);
	    freeswap->Mark( (MAXVPNS * currentThread->space->ID) + vpn);

            bzero(&machine->mainMemory[PageSize * fifo], PageSize);
	    //Write from Swap back to main Memory at position we cleared
	    Swap->ReadAt(&(machine->mainMemory[fifo * PageSize]), PageSize, SwapPos);

	    IvPT->remove(fifo);

	    //IvPT->print();
	    machine->tlb[tlbCount].virtualPage = vpn;
            machine->tlb[tlbCount].physicalPage = fifo;
            machine->tlb[tlbCount].valid = TRUE;
            machine->tlb[tlbCount].use = FALSE;
            machine->tlb[tlbCount].dirty = FALSE;
            machine->tlb[tlbCount].readOnly = FALSE;

	    tlbCount = (tlbCount + 1) % 4;

	    IvPT->insert(vpn, currentThread->space->ID, fifo, true);
	  //IvPT->print();

	    fifo = (fifo + 1) % NumPhysPages;
	  }

	  else
	  {
	    fifo = IvPT->adjust(fifo);

	    //printf("Swap didn't have the file\n");
            //Write the page we are replacing in main memory to swap
	    int m_vpn = IvPT->GetVPN(fifo);
	    int m_pid = IvPT->GetPID(fifo);
	    //printf("%d\n", m_vpn);
	    int MainPos = ((( NumPhysPages * m_pid) + m_vpn) * PageSize);
	    Swap->WriteAt(&(machine->mainMemory[fifo*PageSize]), PageSize, MainPos);
	    freeswap->Mark( (MAXVPNS * currentThread->space->ID) + vpn);
            bzero(&machine->mainMemory[PageSize * fifo], PageSize);

	    if(noffH.code.virtualAddr <= vaddr && vaddr < (noffH.code.virtualAddr + noffH.code.size))
	    {
	     loadFile->ReadAt(&(machine->mainMemory[fifo*PageSize]), PageSize, noffH.code.inFileAddr + (vpn * PageSize));
 	    } 

	    if(noffH.initData.virtualAddr <= vaddr && vaddr < (noffH.initData.virtualAddr + noffH.initData.size))
	    {
          
	      loadFile->ReadAt(&(machine->mainMemory[fifo*PageSize]), PageSize, noffH.code.inFileAddr + (vpn * PageSize));
	    }

	    IvPT->remove(fifo);
	   // printf("Did we make it here\n");

	    for( int i = 0; i < 4; i++ )
	    {
	      if(machine->tlb[i].physicalPage == fifo){
		machine->tlb[i].valid = FALSE;
            	machine->tlb[i].use = FALSE;
            	machine->tlb[i].readOnly = FALSE;
	      }
	    }

	    machine->tlb[tlbCount].virtualPage = vpn;
            machine->tlb[tlbCount].physicalPage = fifo;
            machine->tlb[tlbCount].valid = TRUE;
            machine->tlb[tlbCount].use = FALSE;
            machine->tlb[tlbCount].dirty = FALSE;
            machine->tlb[tlbCount].readOnly = FALSE;

	    tlbCount = (tlbCount + 1) % 4;

	    //printf("%d %d %d\n", vpn, currentThread->space->ID, fifo);
	    IvPT->insert(vpn, currentThread->space->ID, fifo, true);
	    //IvPT->print();
	    fifo = (fifo + 1) % NumPhysPages;
	  }
	}
	else{

        bzero(&machine->mainMemory[PageSize * x], PageSize);
	if(noffH.code.virtualAddr <= vaddr && vaddr < (noffH.code.virtualAddr + noffH.code.size))
	{
	  loadFile->ReadAt(&(machine->mainMemory[x*PageSize]), PageSize, noffH.code.inFileAddr + (vpn * PageSize));
 	} 

	if(noffH.initData.virtualAddr <= vaddr && vaddr < (noffH.initData.virtualAddr + noffH.initData.size))
	{
          
	  loadFile->ReadAt(&(machine->mainMemory[x*PageSize]), PageSize, noffH.code.inFileAddr + (vpn * PageSize));
	}
	
	machine->tlb[tlbCount].virtualPage = vpn;
        machine->tlb[tlbCount].physicalPage = x;
        machine->tlb[tlbCount].valid = TRUE;
        machine->tlb[tlbCount].use = TRUE;
        machine->tlb[tlbCount].dirty = FALSE;
        machine->tlb[tlbCount].readOnly = FALSE;

	tlbCount = (tlbCount + 1) % 4;

	fifo = (fifo + 1) % NumPhysPages;

	IvPT->insert(vpn, currentThread->space->ID, x, true);

	}}
	L->Release();

}

void
AddrSpace::Execute()
{



}


void
AddrSpace::InitRegisters()
{
    int i;

    for (i = 0; i < NumTotalRegs; i++)
	machine->WriteRegister(i, 0);

    // Initial program counter -- must be location of "Start"
    machine->WriteRegister(PCReg, 0);	

    // Need to also tell MIPS where next instruction is, because
    // of branch delay possibility
    machine->WriteRegister(NextPCReg, 4);

   // Set the stack register to the end of the address space, where we
   // allocated the stack; but subtract off a bit, to make sure we don't
   // accidentally reference off the end!
    machine->WriteRegister(StackReg, numPages * PageSize - 16);
    DEBUG('a', "Initializing stack register to %d\n", numPages * PageSize - 16);
}

//----------------------------------------------------------------------
// AddrSpace::SaveState
// 	On a context switch, save any machine state, specific
//	to this address space, that needs saving.
//
//	For now, nothing!
//----------------------------------------------------------------------

void AddrSpace::SaveState() 
{}

//----------------------------------------------------------------------
// AddrSpace::RestoreState
// 	On a context switch, restore the machine state so that
//	this address space can run.
//
//      For now, tell the machine where to find the page table.
//----------------------------------------------------------------------

void AddrSpace::RestoreState() 
{
	  for(int i = 0; i < 4; i++)
	  {
	    machine->tlb[i].valid = FALSE;
	  }
    machine->pageTable = NULL;
    machine->pageTableSize = numPages;
}
