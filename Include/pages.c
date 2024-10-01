#include ""
/*
	My basic intutition to do this 

	* page table is just represention of pages in memory 
	* so it will just return a memory location (means a pointer to a specifc memory)

CURRENT LOCATION --->>      | Page 1 | 
NEXT CURRENT LOCATION -->	| Page 2 | -> Next location counter will shift here if we use a page 
							| Page 3 |
							|
							|
							|
							|
							|
							|
							|


Now we will take page of memory(means pointer to it) and use it to map(or create a page table)

That meas our page table should be of some data type (for now unsigned long *)

so we will use malloc to to take mem of 4096 byte and use that mem to map thhings

*/ 
/* 0000
0000
0001
0011
0000
0000 */
/*
	I am choosing 48 bit addressing mode for PT

*/

void SetupPaging(){
    unsigned long readSATP = satp_read();
    satp_write(0x8000000000000000); // enable sv39 mode(i am using as it looks more easier to use)
    // we also have to save the addr of root page table into 44th bit

}
unsigned long* makepagetable(){


	unsigned long* pagetabledatastruct; // -> this is what holds the page table
	pagetabledatastruct = (unsigned long*)memory_alloc(); // now we get the mem for our table!!
	// ok now page is already filled with our previous memset so :) lets make it to 7 (thala!)
	my_memset(pagetabledatastruct , 7 , PAGE_SIZE); //eventually set it to 0!!
	return pagetabledatastruct; // pointer to table where we are going to map!
}

