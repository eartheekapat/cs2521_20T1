#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

int listDeleteLargest(List l) {
	assert(l != NULL);
	// if list only has one node
	int max = l->head->value;
	if (l->head->next == NULL) {
		l->head = NULL;
		free(l->head);
		return max;
	// generic ca
	} else {
		// max store largest value
		Node prev = l->head;
		Node curr = l->head->next;
		Node next = l->head->next->next;
		for (curr = l->head->next; curr != NULL; curr = curr->next) {
			if (max < curr->value) {
				max = curr->value;
			}
		}
		// delete a node with max as value out of the list
		curr = l->head->next;
		while (curr != NULL) {
            // if the node to delete is the first node 
			if (l->head->value == max) {
				// delete the first node 
				l->head = l->head->next;
				free(prev);
				return max;
			} else if (curr->next == NULL && curr->value == max) { 
				// cond. to check for last node
					prev->next = NULL;
					free(next);
					free(curr);
					return max;
			} else { // the node is somewhere in the middle of the list
			    if (curr->value == max) {
					prev->next = next;
					free(curr);		
					return max;
				}	
			}
			prev = curr;
			curr = next;
			next = next->next;
		}
	}
	return max;
}
