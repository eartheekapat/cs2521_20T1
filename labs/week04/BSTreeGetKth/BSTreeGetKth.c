
#include <stdlib.h>
#include <stdio.h>

#include "BSTree.h"

int putTreeIntoArrayRecursively (BSTree t, int buffer[], int i);
int *arraySortingAscending (int buffer[], int nitem);

int BSTreeGetKth(BSTree t, int k) {
	// put the value in the tree into array
	// counting the value
	// if tree is NULL;
	int buffer[MAX_BST_SIZE];
	if (t == NULL) {
		return 0;
	} else if (t->left == NULL && t->right == NULL && k == 0) {
		return t->value;
	} else { // put value in tree into buffer
		int nitem = 0;
		nitem = putTreeIntoArrayRecursively(t, buffer, nitem);
		int *buffer_arranged = arraySortingAscending (buffer, nitem);
		return buffer_arranged[k];
	}
	return 0;
}

int putTreeIntoArrayRecursively (BSTree t, int buffer[], int nitem) {
	buffer[nitem] = t->value;
	nitem++;
	if (t->left != NULL) {
        nitem = putTreeIntoArrayRecursively(t->left, buffer, nitem);
    }
    if (t->right != NULL) {
        nitem = putTreeIntoArrayRecursively(t->right, buffer, nitem);
    }
    if (t->left == NULL && t->right == NULL) {
        return nitem;
    }
    return nitem;
}

int *arraySortingAscending (int buffer[], int nitem) {
	for (int i = 0; i < nitem; i++) {
			for (int j = 0; j < nitem; j++) {
				if (buffer[j] > buffer[i]) {
					int tmp = buffer[i];
					buffer[i] = buffer[j];
					buffer[j] = tmp;
				}
			}
		}
	return buffer;
}