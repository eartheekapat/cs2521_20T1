// mergeOrdered.c ... implementation of mergeOrdered function

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

/* 
    You will submit only this one file.

    Implement the function "mergeOrdered" below. Read the exam paper for a
    detailed specification and description of your task.  

    - DO NOT modify the code in any other files. 
    - You can add static helper functions to this file.  
    - DO NOT add a "main" function to this file. 
*/

// function do like its name from exercise listSetUnion
Node * sortedInsert (Node * head, int val);
List listSortedCopy(List l);


List mergeOrdered(List list1, List list2) {
    if (list1->first == NULL && list2->first == NULL) {
        List l = newList ();
        return l;
    } else if (list1->first != NULL && list2->first == NULL) {
        List l = listSortedCopy (list1);
        Node *curr = l->first;
        while (curr->next != NULL) { 
            curr = curr->next;
        }
        l->last = curr;    
        return l;
    } else if (list1->first == NULL && list2->first != NULL) {
        List l = listSortedCopy (list2);
        Node *curr = l->first;
        while (curr->next != NULL) { 
            curr = curr->next;
        }
        l->last = curr;    
        return l;
    } else {  
        // 1st loop to put list1 into l 
        List l = listSortedCopy (list1); 
        // 2nd loop to put list 2 into l
        for (Node *currL2 = list2->first; currL2 != NULL; currL2 = currL2->next) {
            l->first = sortedInsert(l->first, currL2->value);     
        }
        return l;
    }
}

Node * sortedInsert (Node * head, int val) {
	if (head == NULL || val <= head->value) {
		Node * n = newNode (val);
		n->next = head;
		return n;
	} else {
		head->next = sortedInsert(head->next, val);
		return head;
	}
}

List listSortedCopy(List l) {
	List copy = newList();
    // loop through every element in the list
	for (Node *curr = l->first; curr != NULL; curr = curr->next) {
		copy->first = sortedInsert(copy->first, curr->value);
	}
	return copy;
}
