#include <stdlib.h>

#include "types.h"
#include "pagetable.h"
#include "global.h"
#include "process.h"
#include "macros.h"

/*******************************************************************************
 * Finds a free physical frame. If none are available, uses a clock sweep
 * algorithm to find a used frame for eviction.
 *
 * @return The physical frame number of a free (or evictable) frame.
 */

/* A physical page is also called a physical frame or frame */
pfn_t get_free_frame(void)
{
	/* TASK 4a: Iterate through the reverse lookup table to see if there is a free frame. If so, return it. */

	int    i;
	pcb_t *pr;
	pte_t  page;
	
	for(i = 0; i < NUM_PHYS_PAGES; i++){
		if(!((rlt+i)->pcb)){ 
			return (pfn_t) i;
		}	
	}

	/* TASK 4b: If none of the frames are free, we must evict a frame.
	 * For each frame, if it is used, set it as unused. If it is already unused, return the frame. 
	 * Repeat the previous step till you find an unused frame. 
	 */ 
	for(;;){	
		for(i = 0; i < NUM_PHYS_PAGES; i++){
			pr = (rlt+i)->pcb;
			page = pr->pagetable[(rlt+i)->vpn];
		
			/* if(IS_SET(page.pfn, VALID){return i;} */
			
			if(IS_SET(page.pfn, USED)){ 
				CLEAR_BIT(page.pfn, USED);
			}else{ 
				return current_pagetable[i].pfn; 
			}
		}		
	}

	/* to satisfy the compiler */
	return 0;
}
