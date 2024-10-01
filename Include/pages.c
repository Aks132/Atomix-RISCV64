#include "../Include/pages.h"
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
    my_printf("%d\n",readSATP);
    // satp_write(0x8000000000000000); // enable sv39 mode(i am using as it looks more easier to use)
    // we also have to save the addr of root page table into 44th bit
    unsigned long* root_page_table = makepagetable();
	map_page(root_page_table, (unsigned long)0x10000000,(unsigned long) 0x10000000,((1<<2)| (1<<1)));
	unsigned long satp_value = (((unsigned long)root_page_table >> 12) | (0x8UL << 60));  // 0x8 sets Sv39 mode
	satp_write(satp_value);
	lib_putc("satp write done\n");

}
unsigned long* makepagetable(){
	unsigned long* pagetabledatastruct; // -> this is what holds the page table
	my_printf("called makepagetable done\n");
	pagetabledatastruct = (unsigned long*)memory_alloc(); // now we get the mem for our table!!
	// ok now page is already filled with our previous memset so :) lets make it to 7 (thala!)
	my_memset(pagetabledatastruct , 7 , PAGE_SIZE); //eventually set it to 0!!
	my_printf("page table done\n");
	return pagetabledatastruct; // pointer to table where we are going to map!
}


// sv39 -> 9bit for L1 , L2 & L3 = 27 bit and 12 bit for internal page offset
// for now idk how exactly these per bit do , like the actual need of these bits
void map_page(unsigned long* pagetabledatastruct , unsigned long virtualAddr , unsigned long physicAddr , unsigned long permissionBits)
{ 
//since we get the VA -> break into 9-9-9 = 1FF
	// page number -> 73
	unsigned long VPN[3] ; // these are virtual page number we have to set
	//0-11 ->offset
	VPN[0] = (virtualAddr >> 12) & 0x1FF ;//12-20
	VPN[1] = (virtualAddr >> 21) & 0x1FF ;//21-29
	VPN[2] = (virtualAddr >> 30) & 0x1FF ; // 30-38
	my_printf("VPN 1 value : %d\n" ,VPN[0]);
	my_printf("VPN 2 value : %d\n" ,VPN[1]);
	my_printf("VPN 3 value : %d\n" ,VPN[2]);

	unsigned long* Level1PageTable = &pagetabledatastruct[VPN[2]];
	my_printf("created leve1 page");
	if ((*Level1PageTable & (1 << 0)) == 0) {
    *Level1PageTable = (unsigned long)makepagetable() >> 12;  // Allocate level 2 table
    *Level1PageTable |= (1 << 0);
    my_printf("level 1 paging doene");
    my_printf("Allocated Level 2 table at: %d\n", (*Level1PageTable << 12));
    }
    unsigned long* Level2PageTable = (unsigned long*)(*Level1PageTable << 12);
    if ((Level2PageTable[VPN[1]] & (1 << 0)) == 0) {
        Level2PageTable[VPN[1]] = (unsigned long)makepagetable() >> 12;  // Allocate level 3 table
        Level2PageTable[VPN[1]] |= (1 << 0);
        my_printf("Allocated Level 3 table at: %d\n", Level2PageTable[VPN[1]] << 12);
    }

    unsigned long* Level3PageTable = (unsigned long*)(Level2PageTable[VPN[1]] << 12);
    Level3PageTable[VPN[0]] = (physicAddr >> 12) | permissionBits | (1 << 0);  // Map VA to PA with flags
    my_printf("Mapped VPN[0] entry to PA: %d\n", physicAddr);
}
