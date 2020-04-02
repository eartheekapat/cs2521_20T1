
#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"

// TODO: Add your code here and change the return
	//       statement if needed.  You may add helper
	//       functions if you wish.

BSTree findMin (BSTree t);

// apply  https://helloacm.com/how-to-delete-a-node-from-a-binary-search-tree/?fbclid=IwAR1YCUr7VQj_HCFdNeP4HtDoiFltzeQfSlzN-8l58n1qr1alVktTCxXyc48
BSTree Delete(BSTree root, int value) {
	if (root == NULL) {
		return NULL;
	}
	if (value < root->value) {  // value is in the left sub tree.
		root->left = Delete(root->left, value);
	} else if (value > root->value) { // value is in the right sub tree.
		root->right = Delete(root->right, value);
	} else {
		// case 1: no children
		if (root->left == NULL && root->right == NULL) {
			free(root);
			root = NULL;
		}
		// case 2: one child (right)
		else if (root->left == NULL) {
			// back up current node in temp
			BSTree temp = root; 
			root = root->right;
			free(temp);
		}
		// case 3: one child (left)
		else if (root->right == NULL) {
			// back up current node in temp
			BSTree temp = root; 
			root = root->left;
			free(temp);
		}
		// case 4: two children
		else {
			BSTree temp = findMin(root->right); // find minimal value of right sub tree
			root->value = temp->value; // duplicate the node
			root->right = Delete(root->right, temp->value); // delete the duplicate node
		}
	}
	return root; // parent node can update reference
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