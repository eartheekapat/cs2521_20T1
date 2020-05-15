#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

bool listIsOrdered(List l) {
	// TODO
	// if list is empty, or contains one or two elements, it is ordered
	assert(l != NULL);
	if (l->head == NULL || l->head->next == NULL || 
	l->head->next->next == NULL) {
		return true;
	// generic case
	} else {
		Node prev = l->head;
		Node curr = l->head->next;
		while (curr != NULL) {
			// if pair of values is equal
			if (prev->value == curr->value) {
				prev = curr;
				curr = curr->next;
			} else if (prev->value < curr->value) {
				Node prev_asce = prev;
        		Node curr_asce = curr;
        		while (curr_asce != NULL) {
					// if not ascending order, false
            		if (curr_asce->value < prev_asce->value) {
                		return false;
            		}
            		prev_asce = curr_asce;
            		curr_asce = curr_asce->next;
        		}
				return true;
			} else if (prev->value > curr->value) {
				Node prev_desc = prev;
				Node curr_desc = curr;
				while (curr_desc != NULL) {
					// if not descending order, false
					if (curr_desc->value > prev_desc->value) {
						return false;
					}
					prev_desc = curr_desc;
					curr_desc = curr_desc->next;
				}
				return true;
			} 
		}
	}
	return true;
}

