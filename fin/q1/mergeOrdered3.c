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

Node * insertSortedRecur (Node * node, int val);

List mergeOrdered(List list1, List list2) {
	// TODO
    // Implement this function
	// if list1 is empty, return list2
	// if (list1->first == NULL && list2->first != NULL) {
	// 	List list3 = zipList(list1, list2);
	// 	return list3;
	// // else if list2 is empty, return list1
	// } else if (list1->first != NULL && list2->first == NULL) {
	// 	List list3 = zipList(list1, list2);
	// 	return list3;
	// // else if list1 and list2 are empty, return new empty list
	// } else 
	if (list1->first == NULL && list2->first == NULL) {
		List list3 = newList();
		return list3;
	// else generic case
	} else {
		Node *list1Node = list1->first;
		Node *list2Node = list2->first;
		List list3 = newList();
		// loop to insert list1 into list3 in ascending order
		while (list1Node != NULL) {
			list3->first = insertSortedRecur (list3->first, list1Node->value);
			list1Node = list1Node->next;
		} 
        // loop to insert list2 into list3 in ascending order
        while (list2Node != NULL) {
            list3->first =  insertSortedRecur (list3->first, list2Node->value);
            list2Node = list2Node->next;
        }
        return list3;
	}
}

Node * insertSortedRecur (Node * node, int val) {
    if (node == NULL || val <= node->value) {
        // insert before
        Node * new = newNode(val);
        new->next = node;   
        return new;     
    } else { // call recur
        node->next = insertSortedRecur (node->next, val);
        return node;
    }
}
