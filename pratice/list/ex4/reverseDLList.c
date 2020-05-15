#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

void reverseDLList(List l) {
	// TODO
	assert(l != NULL);
	if (l->first == NULL || l->first->next == NULL) {
		return;
	} else if (l->size == 2) {
		Node a = l->first;
		Node z = l->last;
		z->prev = NULL;
		z->next = a;
		a->prev = z;
		a->next = NULL;
	    l->first = z;
		l->last = a;
	} else {
		l->first = l->last;

		Node prev = l->last;
		Node curr = l->last->prev;
		Node next = l->last->prev->prev;

		while (next != NULL) {
			if (prev == l->last) {
				prev->prev = NULL;
				prev->next = curr;
				curr->prev = prev;
			} else {
				prev->next = curr;
				curr->prev = prev;
			}
			prev = curr;
			curr = next;
			next = next->prev;
		}
		prev->next = curr;
		curr->prev = prev;
		curr->next = NULL;
		l->last = curr;
	}
}

