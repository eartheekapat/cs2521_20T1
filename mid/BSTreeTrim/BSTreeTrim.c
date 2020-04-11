
#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"

// TODO: Add your code here and change the return
	//       statement if needed.  You may add helper
	//       functions if you wish.

BSTree deleteNode (BSTree node, int value);
BSTree findMin (BSTree t);

// apply https://www.geeksforgeeks.org/remove-bst-keys-in-a-given-range/?fbclid=IwAR1LBQQH6N69oG0o3-HGavGxi8ohyR_JAMn-HLndVwtFs2z7hBfnTeZWk5Y
// and https://helloacm.com/how-to-delete-a-node-from-a-binary-search-tree/?fbclid=IwAR15TQ-UlYzedC6xuwXcCVv7zh97-24h1tXOQCG6uJ5-eiYZUkh27PhQ6f0
BSTree BSTreeTrim(BSTree t, int lower, int upper) {
	if (t == NULL) {
		return NULL;
	} 

	t->left = BSTreeTrim (t->left, lower, upper);
	t->right = BSTreeTrim (t->right, lower, upper);

	if (t->value >= lower && t->value <= upper) 
        return deleteNode (t, t->value); 
 
	return t;
}

// function to find the left most node
BSTree findMin (BSTree t) {
    if (t == NULL) {
        return NULL;
    }
    while (t->left != NULL) {
        t = t->left;
    }
    return t;
}

BSTree deleteNode (BSTree t, int value) {
	if (t == NULL) {
		return NULL;
	}
	if (value < t->value) {  // value is in the left sub tree.
		t->left = deleteNode (t->left, value);
	} else if (value > t->value) { // value is in the right sub tree.
		t->right = deleteNode (t->right, value);
	} else {
		// case 1: no children
		if (t->left == NULL && t->right == NULL) {
			free(t);
			t = NULL;
		}
		// case 2: one child (right)
		else if (t->left == NULL) {
			// back up current node in temp
			BSTree temp = t; 
			t = t->right;
			free(temp);
		}
		// case 3: one child (left)
		else if (t->right == NULL) {
			// back up current node in temp
			BSTree temp = t; 
			t = t->left;
			free(temp);
		}
		// case 4: two children
		else {
			BSTree temp = findMin(t->right); // find minimal value of right sub tree
			t->value = temp->value; // duplicate the node
			t->right = deleteNode (t->right, temp->value); // delete the duplicate node
		}
	}
	return t; 
}
