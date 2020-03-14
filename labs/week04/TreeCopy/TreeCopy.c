
#include "tree.h"

int FindTreeHeightRecur (Tree t, int height);
void copyTreeRecur (Tree t, Tree copy,  int depth, int currDepth);
static Tree newTreeNode(int value);

Tree TreeCopy(Tree t, int depth) {
	if (depth < 0) { //If the given depth is negative, 
	// you should return an empty tree
		return NULL;
	}
	int height = 0;
	height = FindTreeHeightRecur (t, height);
	if (depth < 0) { //If the given depth is negative, 
	// you should return an empty tree
		return NULL;
	} else if (depth > height) {
		return t;
	} else {
		int currDepth = 0;
		Tree copy = newTreeNode(t->value);
		Tree copyHead = copy;
		copyTreeRecur (t, copy, depth, currDepth);
		return copyHead;
	}
	return NULL;
}

static Tree newTreeNode(int value) {
	Tree t = malloc(sizeof(*t));
	if (t == NULL) {
		fprintf(stderr, "Insufficient memory!\n");
		exit(EXIT_FAILURE);
	}
	t->value = value;
	t->left = NULL;
	t->right = NULL;
	return t;
}

int FindTreeHeightRecur (Tree t, int height) {
	if (t->left == NULL && t->right == NULL) {
		return height;
	} else if (t->left != NULL && t->right != NULL) {
		height++;
		// create temp to store the value of height
		int temp = height;
		height =  FindTreeHeightRecur(t->left, height);
		temp = FindTreeHeightRecur(t->right, temp);
		if (temp > height) {
			return temp;
		} else {
			return height;
		}
	} else if (t->left != NULL && t->right == NULL) {
		height++;
		return  FindTreeHeightRecur(t->left, height);
	} else if (t->left == NULL && t->right != NULL) {
		height++;
		return  FindTreeHeightRecur(t->right, height);
	}
	return height;
}

void copyTreeRecur (Tree t, Tree copy, int depth, int currDepth) {
	if (currDepth < depth) {
		int temp = currDepth;
		if (t->left == NULL && t->right == NULL) {
			return;
		} 
		if (t->left != NULL) {
			copy->left = newTreeNode(t->left->value);
			copyTreeRecur (t->left, copy->left, depth, currDepth+1);
		} 
		if (t->right != NULL) {
			copy->right = newTreeNode(t->right->value);
			copyTreeRecur (t->right, copy->right, depth, temp+1);
		}
	}
}