group4: Daniel Lowdermilk, Deric Lester, Patrick Candia

	Task 1: Implemented Page Replacing and Demand Paging - All code is located in Exception.cc (PageFault ExceptionHandler) and Addrspace.cc/h (Addrspace::Load)
		Global variables located in System.h/cc

		Demand Paging with TLB:	A Pagefault exception is genereated and caught everytime a page fails to load (when a tlb miss occurs).
	       				We then load that specific page into memory and have a reference to it in the tlb.
					
		IvPT:			Whenever a page is loaded into memory, a reference is also loaded into the IvPT that
					maps the virtual page number and process id to the specific page in main memory.

		Swap:			Whenenever the 32 page limit of main memory is exceeded, a page is replaced based on the particular algorithm in place and loaded 
					into swap. Once it is stored in swap, that page is then cleared from memory to make room for the page we just page faulted on and
					the IvPT and tlb are both updated to reference the new page being loaded in.

	Task 2: Individual tasks

		Patrick - PreFetching:	Made an attempt to implement pre-fetching that would load more than one page into main memory based on if it's an either/odd numbered
					page. Code was implemented, but when compiled and ran nothing seems to be different than before it. Due to this, the code has been left
					out to avoid potential conflicts with the other individual tasks.

		Daniel - Clock:		Replaced fifo page replacement algorithm with clock algorithm. Everytime a page is loaded into memory, the IvPT is updated that the
					page has been used and should be saved. When memory is filled and all pages are marked used, all pages are marked unused and the first
					page we encounter after doing so is replaced with the incoming page which is then marked used. Any pages used while marked unused in the
					IvPT will be remarked used and not loaded again.

		Deric - Statistics:	Statistics adds another system call SC_Memstats.  This keeps track of the number of page faults that occcurs, and the number of page hits that occur.  
					When called it will return the hit rate % that our virtual memory system incured. Code was added in /test/start.c to allow our test files to identify Memstat.
					Code was also added to /userprog/syscall.h to allow the system to know that the system call exisited. 

	
	Contributions to group work:
		
		Daniel: 		Partially wrote code and contributed to logic of tlb, IvPT, and Swap.
					Implemented Clock.

		Deric:			Partially wrote code and contributed to logic of tlb, IvPT, and Swap.
					Implemented Statistics.

		Patrick:		Attempted pre-fetching
