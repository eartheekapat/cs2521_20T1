#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "list.h"

void insertNumber (List new, int val);

List listSetUnion(List s1, List s2) {
	if (s1->head == NULL && s2->head != NULL) {
        return s2;
    // if s2 is empty, but s1 is not
    } else if (s1->head != NULL && s2->head == NULL) {
        return s1;
    // if s1 and s2 are both empty
    } else if (s1->head == NULL && s2->head == NULL) {
        List s = newList();
        return s;
    // generic case
    } else {
		List s = listSortedCopy(s1);
        int comp, match;
		for (Node currS2 = s2->head; currS2 != NULL; currS2 = currS2->next) {
			// loop to find if comp exist in	List new = s1
			comp = currS2->value;
			match = 0;
			for (Node currS1 = s1->head; currS1 != NULL; currS1 = currS1) {
				if (comp == currS1->value) {
					match = 1;
				}
				currS1 = currS1->next;
			}
			if (match == 0) {
				insertNumber (s, comp);
		    }		
		}
		return s;
	}
}

void insertNumber (List	new, int val) {
	// loop to the last node of the list	List new and insert 
	Node currNew = new->head;
	while (currNew->next != NULL) {
		currNew = currNew->next;
	} 
	currNew->next = newNode(val);
}
