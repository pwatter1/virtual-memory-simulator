#include "swapfile.h"
#include "stats.h"
#include "pagetable.h"
#include "macros.h"

#define NULL 0

/*******************************************************************************
 * Looks up an address in the current page table. If the entry for the given
 * page is not valid, traps to the OS.
 *
 * @param vpn The virtual page number to lookup.
 * @param write If the access is a write, this is 1. Otherwise, it is 0.
 * @return The physical frame number of the page we are accessing.
 */

pfn_t pagetable_lookup(vpn_t vpn, int write)
{
	/* TASK 3: Within the current process's pagetable, look for the entry corresponding to vpn. 
	* 	      If the entry is valid, return the physical page (or frame). Otherwise, you have 
	*	      encountered a pagefault. Increment the counter and invoke the pagefault_handler to
	* 	      get the physical page. Finally return the page.
	*/

	/* pfn_t entry = 0; */
	
	if(IS_SET(current_pagetable[vpn].flags, VALID)){ return current_pagetable[vpn].pfn;}

	else{
		pagefaults_count++;
		return pagefault_handler(vpn, write);
	}
}
