
#include <stdlib.h>

#include "tree.h"

int countNitemsRecursively (Tree t, int nitems);
bool checkIfNodeIsPerfectlyBalanced (Tree t);
bool checkNodeRecursively (Tree t);

bool TreeIsPerfectlyBalanced(Tree t) {
	// for every node, count nitemsLeft and nitemsRight and compare them
	if (t == NULL) { // case empty tree
		return true;
	}
	bool answer = checkNodeRecursively(t);
	return answer;
}

int countNitemsRecursively (Tree t, int nitems) {
	if (t == NULL) {
		return nitems;
	} else {
		nitems++;
		if (t->left != NULL) {
			nitems = countNitemsRecursively(t->left, nitems);
		} 
		if (t->right != NULL) {
			nitems = countNitemsRecursively(t->right, nitems);
		}
		if (t->left == NULL && t->right == NULL) {
			return nitems;
		} 
	}
	return nitems;
}

bool checkIfNodeIsPerfectlyBalanced (Tree t) {
	if (t->left == NULL && t->right == NULL) {
		return true;
	}
	int nitemsLeft = 0;
	int nitemsRight = 0;
	nitemsLeft = countNitemsRecursively(t->left, nitemsLeft);
	nitemsRight = countNitemsRecursively(t->right, nitemsRight);
	if ((nitemsRight-1) <= nitemsLeft && nitemsLeft <= (nitemsRight+1)) {
		return true;
	} else {
		return false;
	}
}

bool checkNodeRecursively (Tree t) {
	bool answer = checkIfNodeIsPerfectlyBalanced (t);
	if (answer == false) {
		return false;
	}
	if (t->left == NULL && t->right == NULL) {
		return true;
	} 
	if (t->left != NULL) {
		answer = checkIfNodeIsPerfectlyBalanced (t->left);
		if (answer == false) {
			return false;
		} else {
			answer = checkNodeRecursively(t->left);
		}
	}
	if (t->right != NULL) {
		answer = checkIfNodeIsPerfectlyBalanced(t->right);
		if (answer == false) {
			return false;
		} else {
			answer = checkNodeRecursively(t->right);
		}
	}
	return answer;
}





