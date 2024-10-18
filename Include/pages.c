#include "pages.h"
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
extern char _text_end[];

#define MASKNINEBIT          0x1FF // 9 bits
#define PHYSICALSHIFT(level)  (12+(9*(level)))
#define PX(level, va) ((((unsigned long) (va)) >> PHYSICALSHIFT(level)) & MASKNINEBIT)

unsigned long * k_pagetable;
void maketable(){
	k_pagetable = setupPagetable();
	asm volatile("sfence.vma zero, zero");
	satp_write(((8L << 60) | (((unsigned long)k_pagetable) >> 12)));
	// my_printf("satp : %d\n" , ((8L << 60) | (((unsigned long)k_pagetable) >> 12)));
	asm volatile("sfence.vma zero, zero");
}

unsigned long *setupPagetable(){

	unsigned long * pagetable;
	pagetable = (unsigned long*)memory_alloc();
	// my_printf("%d\n" , pagetable);
	my_memset(pagetable , 0 , PAGE_SIZE);

	map_pages(pagetable,(unsigned long)UART_TX_ADDR,(unsigned long)UART_TX_ADDR,4096,((1<<1)|(1<<2)));
	// map_pages(pagetable, 0x10001000, 0x10001000, 4096, ((1g<<1)|(1<<2)));
	// my_printf("text - kernal %d\n" ,_text_end-KERNBASE );
	map_pages(pagetable, KERNBASE, KERNBASE, mem_round_upto_pages((unsigned long)_text_end-KERNBASE), ((1<<1)|(1<<3)));


	return pagetable;
}

void map_pages(unsigned long *pagetable , unsigned long virtAddr , unsigned long phyAddr , unsigned long size , int perms){
	unsigned long start = 0 ; // start of virtual address!
	unsigned long end ;   // end of the virtual addr

	unsigned long *PTE;
	end = virtAddr + size - PAGE_SIZE;
	start =( unsigned long )virtAddr;
	// my_printf("end : %d\n", end);
	// my_printf("start : %d\n" , virtAddr);
  for(;;){
    if((PTE = moveThroughPages(pagetable, start, 1)) == 0){
    	return;}
    if(*PTE & (1<<0))
      my_printf(" i am panicked : mappages: remap\n");
    *PTE = ((((((unsigned long)phyAddr) >> 12) << 10)) | perms | (1<<0));
    unsigned long x = phyAddr;
	UNUSED(x);
    if(start == end){
    	// my_printf(" start == end \n");
    	// my_printf(" linker text end : %d\n" , linker_textAddr);
      break;
      
    }
    // my_printf("mapppig. .......%d to %d with perm %d\n ::" , start , x,perms);

    start =  start + PAGE_SIZE;
    phyAddr =phyAddr  + PAGE_SIZE;

  }
}


unsigned long* moveThroughPages(unsigned long * pages , unsigned long virtAddr , int check){
	for(int i = 2 ; i > 0 ; i--){
		unsigned long* pte = &pages[PX(i,virtAddr)];
		if(*pte  & (1<<0)){
			pages = (unsigned long *)(((*pte) >> 10) << 12);
		}
		else {
      if(!check || (pages = (unsigned long*)memory_alloc()) == 0)
        return 0;
      my_memset(pages, 0, PAGE_SIZE);
      *pte = (((((unsigned long)pages) >> 12) << 10)) | (1<<0);
    }
	}
	// my_printf("mobe return %d\n" ,&pages[PX(0,virtAddr)] );
	return &pages[PX(0,virtAddr)];
}

/* 0000
0000
0001
0011
0000
0000


79000000
10000000

 */
/*
	I am choosing 48 bit addressing mode for PT
0001
0000
0000
0000
0000
*/
<<<<<<< HEAD

// void SetupPaging(){
//     unsigned long readSATP = satp_read();
//     my_printf("%d\n",readSATP);
//     // satp_write(0x8000000000000000); // enable sv39 mode(i am using as it looks more easier to use)
//     // we also have to save the addr of root page table into 44th bit
//     unsigned long* root_page_table = makepagetable();
// 	map_page(root_page_table, (unsigned long)0x10000000,(unsigned long) 0x10000000,((1<<2)| (1<<1)));
// 	unsigned long satp_value = (((unsigned long)root_page_table >> 12) | (0x8UL << 60));  // 0x8 sets Sv39 mode
// 	satp_write(satp_value);
// 	my_printf("satp write done\n");


// 	Println();;
// 	my_printf("verifying page table entry");
// 	verify_page_table_entry(root_page_table, (unsigned long) 0x10000000);


// }
// unsigned long* makepagetable(){
// 	unsigned long* pagetabledatastruct; // -> this is what holds the page table
// 	my_printf("called makepagetable done\n");
// 	pagetabledatastruct = (unsigned long*)memory_alloc(); // now we get the mem for our table!!
// 	// ok now page is already filled with our previous memset so :) lets make it to 7 (thala!)
// 	my_memset(pagetabledatastruct , 7 , PAGE_SIZE); //eventually set it to 0!!
// 	my_printf("page table done\n");
// 	return pagetabledatastruct; // pointer to table where we are going to map!
// }


// // sv39 -> 9bit for L1 , L2 & L3 = 27 bit and 12 bit for internal page offset
// // for now idk how exactly these per bit do , like the actual need of these bits
// void map_page(unsigned long* pagetabledatastruct , unsigned long virtualAddr , unsigned long physicAddr , unsigned long permissionBits)
// { 
// //since we get the VA -> break into 9-9-9 = 1FF
// 	// page number -> 73
// 	unsigned long VPN[3] ; // these are virtual page number we have to set
// 	//0-11 ->offset
// 	VPN[0] = (virtualAddr >> 12) & 0x1FF ;//12-20
// 	VPN[1] = (virtualAddr >> 21) & 0x1FF ;//21-29
// 	VPN[2] = (virtualAddr >> 30) & 0x1FF ; // 30-38
// 	my_printf("VPN 1 value : %d\n" ,VPN[0]);
// 	my_printf("VPN 2 value : %x\n" ,VPN[1]);
// 	my_printf("VPN 3 value : %d\n" ,VPN[2]);

// 	unsigned long* Level1PageTable = &pagetabledatastruct[VPN[2]];
// 	my_printf("created leve1 page\n");
// 	my_printf("* Level1PageTable  : %x\n",*Level1PageTable );
// 	if (((*Level1PageTable) & 0x1) == 0) {
// 	my_printf("Inside *Level1PageTable & (1 << 0)\n");
//     *Level1PageTable = ((unsigned long)makepagetable()) >> 12;  // Allocate level 2 table
//     *Level1PageTable |= (1 << 0);
//     my_printf("level 1 paging done\n");
//     my_printf("Allocated Level 2 table at: %d\n", (*Level1PageTable << 12));
//     }
//     unsigned long* Level2PageTable = (unsigned long*)(*Level1PageTable << 12);
//     if ((Level2PageTable[VPN[1]] & 0x01 == 0)){
//         Level2PageTable[VPN[1]] = (unsigned long)makepagetable() >> 12;  // Allocate level 3 table
//         Level2PageTable[VPN[1]] |= (1 << 0);
//         my_printf("Allocated Level 3 table at: %d\n", Level2PageTable[VPN[1]] << 12);
//     }
//     unsigned long* Level3PageTable = (unsigned long*)(Level2PageTable[VPN[1]] << 12);
//     Level3PageTable[VPN[0]] = (physicAddr >> 12) | permissionBits | (1 << 0);  // Map VA to PA with flags
//     my_printf("Mapped VPN[0] entry to PA: %d\n", physicAddr);
// }

// void verify_page_table_entry(unsigned long *root_page_table, unsigned long virtualAddr) {
//     unsigned long  vpn[3];
//     vpn[0] = (virtualAddr >> 12) & 0x1FF;   // Extract VPN[0]
//     vpn[1] = (virtualAddr >> 21) & 0x1FF;   // Extract VPN[1]
//     vpn[2] = (virtualAddr >> 30) & 0x1FF;   // Extract VPN[2]
    
//     my_printf("Verifying VA: %x -> VPN[2]: %x, VPN[1]: %x, VPN[0]: %x\n", virtualAddr, vpn[2], vpn[1], vpn[0]);

//     unsigned long *level1_table = &root_page_table[vpn[2]];
//     if (((unsigned long)*level1_table & 0x1) == 0) {
//         my_printf("Level 1 PTE not valid\n");
//         return;
//     }
    
//     unsigned long *level2_table = (unsigned long *)(*level1_table & ~0xFFF);  // Get level 2 table
//     if (((level2_table[vpn[1]] & 0x1) == 0)) {
//         my_printf("Level 2 PTE not valid\n");
//         return;
//     }

//     unsigned long *level3_table = (unsigned long *)(level2_table[vpn[1]] & ~0xFFF);  // Get level 3 table
//     if ((level3_table[vpn[0]] & 0x1) == 0) {
//         my_printf("Level 3 PTE not valid\n");
//         return;
//     }

//     unsigned long pa = (level3_table[vpn[0]] & ~0xFFF);  // Extract the physical address
//     my_printf("VA: 0x%x is mapped to PA: 0x%x\n", virtualAddr, pa);
// }
// #define SATP_SV39 (8L << 60)
// #define PTE_V (1L << 0) // valid
// #define PTE_R (1L << 1)
// #define PTE_W (1L << 2)
// #define PTE_X (1L << 3)
// #define PTE_U (1L << 4) // user can access
// #define PA2PTE(pa) ((((unsigned long)pa) >> 12) << 10)


// #define MAKE_SATP(pagetable) (SATP_SV39 | (((unsigned long)pagetable) >> 12))
// unsigned long* root_page_table ;
// void SetupPaging() {
//     unsigned long readSATP = satp_read();
//     my_printf("Current SATP value: %x\n", readSATP);

//     root_page_table = makepagetable();
//     // map_page(root_page_table, (unsigned long)UART_TX_ADDR, (unsigned long)UART_TX_ADDR, PAGE_SIZE,((1 << 2) | (1 << 1)));  // Example mapping with RW permissions
//     map_page(root_page_table, 0x10000000, 0x10000000, PAGE_SIZE, PTE_R | PTE_W);

//     asm volatile("sfence.vma zero, zero"); // flush all tlb
// 	my_printf("root table addr %d\n",root_page_table);
//     satp_write(MAKE_SATP(root_page_table));
//     my_printf("New SATP value : %d\n");

//     Println();
//     my_printf("Verifying page table entry:\n");
//     asm volatile("sfence.vma zero, zero");
// 	// verify_page_table_entry(root_page_table, (unsigned long)UART_TX_ADDR);


// }

// unsigned long* makepagetable() {
//     unsigned long* pagetabledatastruct;

//     my_printf("Allocating new page table...\n");
//     pagetabledatastruct = (unsigned long*)memory_alloc();  // Allocate memory for the page table
//     my_printf("pagetabledatastruct : %d\n",pagetabledatastruct);
//     my_memset(pagetabledatastruct, 0, PAGE_SIZE);  // Initialize the page table with zeros

//     my_printf("Page table creation done\n");
//     return pagetabledatastruct;  // Return pointer to the newly created page table
// }

// int map_page(unsigned long* pagetabledatastruct, unsigned long virtualAddr, unsigned long size, unsigned long physicalAddr, unsigned long permissionBits) {
//     unsigned long a, last;
//     unsigned long VPN[3];

//     // Check if the virtual address and size are aligned with the page size
//     if ((virtualAddr % PAGE_SIZE) != 0) {
//     }

//     if ((size % PAGE_SIZE) != 0) {
//     }

//     if (size == 0) {
//     }

//     a = virtualAddr;
//     last = virtualAddr + size - PAGE_SIZE;

//     // Loop through each page in the specified range
//     for (;;) {
//         // Break down the virtual address into VPN parts (Sv39 format)
//         VPN[0] = (a >> 12) & 0x1FF;  // Bits 12-20
//         VPN[1] = (a >> 21) & 0x1FF;  // Bits 21-29
//         VPN[2] = (a >> 30) & 0x1FF;  // Bits 30-38

//         // Level 1 page table (VPN[2])
//         unsigned long* Level1PageTable = &pagetabledatastruct[VPN[2]];
//         if ((*Level1PageTable & 0x1) == 0) {  // If Level 2 page table is not allocated
//             *Level1PageTable = (unsigned long)makepagetable() >> 12;
//             *Level1PageTable |= PTE_V;  // Set valid bit
//             my_printf("+Allocated Level 2 page table at: %x\n", (*Level1PageTable << 12));
//         }

//         // Level 2 page table (VPN[1])
//         unsigned long* Level2PageTable = (unsigned long*)(*Level1PageTable << 12);
//         if ((Level2PageTable[VPN[1]] & 0x01) == 0) {  // If Level 3 page table is not allocated
//             Level2PageTable[VPN[1]] = (unsigned long)makepagetable() >> 12;
//             Level2PageTable[VPN[1]] |= PTE_V;  // Set valid bit
//             my_printf("Allocated Level 3 page table at: %x\n", Level2PageTable[VPN[1]] << 12);
//         }

//         // Level 3 page table (VPN[0])
//         unsigned long* Level3PageTable = (unsigned long*)(Level2PageTable[VPN[1]] << 12);
        
//         // Check for existing mapping
//         if (Level3PageTable[VPN[0]] & PTE_V) {
//             // panic("map_pages: remap");
//         }

//         // Map the physical address to the final page table entry
//         Level3PageTable[VPN[0]] = PA2PTE(physicalAddr) | permissionBits | PTE_V;
//         my_printf("Mapped VA %x to PA %x with permissions %x\n", a, physicalAddr, permissionBits);

//         // Move to the next page
//         if (a == last) {
//             break;  // Exit the loop if we reached the last address
//         }
//         a += PAGE_SIZE;
//         physicalAddr += PAGE_SIZE;
//     }

//     return 0;  // Success
// }



=======
extern char _text_end[];

#define MASKNINEBIT          0x1FF // 9 bits
#define PHYSICALSHIFT(level)  (12+(9*(level)))
#define PX(level, va) ((((unsigned long) (va)) >> PHYSICALSHIFT(level)) & MASKNINEBIT)

unsigned long * k_pagetable;
void maketable(){
	k_pagetable = setupPagetable();
	asm volatile("sfence.vma zero, zero");
	satp_write(((8L << 60) | (((unsigned long)k_pagetable) >> 12)));
	// my_printf("satp : %d\n" , ((8L << 60) | (((unsigned long)k_pagetable) >> 12)));
	asm volatile("sfence.vma zero, zero");
	my_printf("Make table done succesfully!! \n");
}

unsigned long *setupPagetable(){

	unsigned long * pagetable;
	pagetable = (unsigned long*)memory_alloc();
	// my_printf("%d\n" , pagetable);
	my_memset(pagetable , 0 , PAGE_SIZE);

	map_pages(pagetable,(unsigned long)UART_TX_ADDR,(unsigned long)UART_TX_ADDR,4096,((1<<1)|(1<<2)));
	// map_pages(pagetable, 0x10001000, 0x10001000, 4096, ((1g<<1)|(1<<2)));
	// my_printf("text - kernal %d\n" ,_text_end-KERNBASE );
	map_pages(pagetable, KERNBASE, KERNBASE, mem_round_upto_pages((unsigned long)_text_end-KERNBASE), ((1<<1)|(1<<3)));


	return pagetable;
}

void map_pages(unsigned long *pagetable , unsigned long virtAddr , unsigned long phyAddr , unsigned long size , int perms){
	unsigned long start = 0 ; // start of virtual address!
	unsigned long end ;   // end of the virtual addr

	unsigned long *PTE;
	end = virtAddr + size - PAGE_SIZE;
	start =( unsigned long )virtAddr;
	// my_printf("end : %d\n", end);
	// my_printf("start : %d\n" , virtAddr);
  for(;;){
    if((PTE = moveThroughPages(pagetable, start, 1)) == 0){
    	return;}
    if(*PTE & (1<<0))
      my_printf(" i am panicked : mappages: remap\n");
    *PTE = ((((((unsigned long)phyAddr) >> 12) << 10)) | perms | (1<<0));
    unsigned long x = phyAddr;
	UNUSED(x);
    if(start == end){
    	// my_printf(" start == end \n");
    	// my_printf(" linker text end : %d\n" , linker_textAddr);
      break;
      
    }
    // my_printf("mapppig. .......%d to %d with perm %d\n ::" , start , x,perms);

    start =  start + PAGE_SIZE;
    phyAddr =phyAddr  + PAGE_SIZE;

  }
}


unsigned long* moveThroughPages(unsigned long * pages , unsigned long virtAddr , int check){
	for(int i = 2 ; i > 0 ; i--){
		unsigned long* pte = &pages[PX(i,virtAddr)];
		if(*pte  & (1<<0)){
			pages = (unsigned long *)(((*pte) >> 10) << 12);
		}
		else {
      if(!check || (pages = (unsigned long*)memory_alloc()) == 0)
        return 0;
      my_memset(pages, 0, PAGE_SIZE);
      *pte = (((((unsigned long)pages) >> 12) << 10)) | (1<<0);
    }
	}
	// my_printf("mobe return %d\n" ,&pages[PX(0,virtAddr)] );
	return &pages[PX(0,virtAddr)];
}
>>>>>>> 0724837fc22bc01f98fa21061ef9c01bbe60f241
