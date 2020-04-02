
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "list.h"

// TODO: Add your code here and change the return
	//       statement if needed.  You may add helper
	//       functions if you wish.

// MY HELPER FUNCTION
// insert Node n into the List l 
void insertNode (Node n, List l);

List listGetAbnormals (List l, int threshold) {
	// create abn to store abnormal value and return
	List abn = newList();
	if (l->first == NULL) { // if list is empty
		return l; // return empty list
	} else if (l->first == l->last) { // there's only one node  
		return abn;		
	}
	// skip the first node cause never satisfy both cond. for abns
	Node curr = l->first->next;	
	while (curr != l->last) { // loop until the node of the list
		// check if a value is abn
		if ( (abs (curr->value - curr->prev->value) >= threshold) &&
			(abs (curr->value - curr->next->value) >= threshold) ) {
				if (abn->first == NULL) { // List abn is empty
					abn->first = abn->last = newNode (curr->value);
					abn->size++;
				} else {
					Node n = newNode (curr->value);
					insertNode (n, abn);
				}	
		} 
		curr = curr->next;
	}
	return abn;
}

void insertNode (Node n, List l) {
	if (l->first == NULL) {
		l->first = l->last = n;
		l->size++;
		return;
	} else {
		if (l->first->next == NULL) { // if there is only one node in the list
			l->first->next = n;
			l->first->next->prev = l->first;
			l->last = n;
			l->size++;
			return;
		} else { // if there are more than one nodes in the list
			// loop to the last node of the list and insert
			l->last->next = n;
			l->last->next->prev = l->last;
			l->last = n;
			l->size++;
			return;
		}
	}
}