
#include "stdlib.h"
#include "stdio.h"

#include "list.h"

void listInsert (List l, int comp); 

List listSetDifference(List l1, List l2) {
	List l = newList();
    
	if (l1->head == NULL && l2->head == NULL) {
		return l;
	} else if (l1->head != NULL && l2->head == NULL) {
        //List l = listSortedCopy(l1);
        return l1;
    } else if (l1->head == NULL && l2->head != NULL) {
        // List l = listSortedCopy(l2);
        return l2;
	} else {
        Node currL1 = l1->head;
		Node currL2 = l2->head;
        // iterate through to the end of l1
        for (; currL1 != NULL; currL1 = currL1->next) {
			// iterate through to the end of l2
            for (currL2 = l2->head; currL2 != NULL; currL2 = currL2->next) {
				// if any value of l1 matches a value in l2, end the loop
                if (currL1->value == currL2->value) {
                    break;
                }
            }              
            // if l2_node passes the end of l2
            if (currL2 == NULL) {
                Node currL3 = newNode(currL1->value);
                currL3->next = l->head;
                l->head = currL3;
            }
        }
        return l;
    }
}