/*
	My basic intutition to do this 

	* page table is just represention of pages in memory 
	* so it will just return a memory location (means a pointer to a specifc memory)

CURRENT LOCATION --->>      | Page 1 | 
							| Page 2 | -> Next location counter will shift here if we use a page 
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





*/ 