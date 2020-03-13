
#include "list.h"
#include <assert.h>

List listSetDifference(List l1, List l2) {
	// Make new list 'l3' to be returned
	List l3 = listSortedCopy(l1);
	// if l3 is empty > l2 itself is the answer
	if (l3->head == NULL) {
		return l2;
	} else {
		// loop to compare each of l3 = l1 component with l2 component
		// declare currL2 as pointer to move along list L2
		Node currL2 = l2->head;
		while (currL2 != NULL) {
			Node currL3 = l3->head;
			Node beforeCurrL3 = currL3;
			while (currL3 != NULL)  {
				// check if the number exists in List l2
				// if exist, delete the node which contains the value
				if (currL3->value == currL2->value) {
					// check if we are going to delete the first node of the list
					// which is the head of the list so we have to assign new head 
					if (currL3 == l3->head) {
						// if there is only one node left
						if (currL3->next == NULL) {
							Node temp = currL3;
							l3->head = l3->head->next = NULL;
							free(temp);
							return l3;
						} else { // if the node is head but not the only node 
							Node temp = currL3;							// move head
							l3->head = l3->head->next;
							// currL3->next = NULL;
							free(temp);		
						}
					} else { // if the node we are going to delete is not the head				
						// if the node is the last node of the list
						if (currL3->next == NULL) { // the node is the last node 
							// set it to be the last node 
							Node temp = currL3;
							beforeCurrL3->next = NULL;
							free(temp);
						} else { // if the node is somewhere in the middle 
							Node temp = currL3; 
							beforeCurrL3->next = currL3->next;
							free(temp);
						}
					}
				}
				beforeCurrL3 = currL3;
				currL3 = currL3->next;
			}
			currL2 = currL2->next;
		}
		free(currL2);
		return l3;
	}	
}

