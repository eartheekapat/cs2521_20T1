// Implementation of the BST ADT using an AVL tree

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Time.h"
#include "Tree.h"

typedef struct node *Node;
struct node {
    Time time;
    int  height;
    Node left;
    Node right;
};

struct tree {
    Node root;
};

////////////////////////////////////////////////////////////////////////
// Function Prototypes

static void doFree(Node n);
static Node doInsert(Node n, Time time);
static Node rotateLeft(Node n);
static Node rotateRight(Node n);
static int  height(Node n);
static int  max(int a, int b);
static Node newNode(Time time);

// function to find height of the tree
bool checkIfNodeIsPerfectlyBalanced (Node t);
bool checkNodeRecursively (Node t);
int countNitemsRecursively (Node t, int nitems);
Node rebalanceTreeRecur (Node n);
Node partitionTreeRecur (Node n, int i);
Time CompareTimeEarlierRecur (Node n, Time time);
Time CompareTimeLaterRecur (Node n, Time time);


////////////////////////////////////////////////////////////////////////
// Constructor and Destructor

// Creates a new empty tree
Tree TreeNew(void) {
    Tree t = malloc(sizeof(*t));
    if (t == NULL) {
        fprintf(stderr, "Insufficient memory!\n");
        exit(EXIT_FAILURE);
    }
    t->root = NULL;
    return t;
}

// Frees all memory associated with the given tree
void TreeFree(Tree t) {
    doFree(t->root);
    free(t);
}

static void doFree(Node n) {
    if (n != NULL) {
        doFree(n->left);
        doFree(n->right);
        TimeFree(n->time);
        free(n);
    }
}

////////////////////////////////////////////////////////////////////////
// Insertion

// Inserts  a  copy of the given time into the tree if it is not already
// in the tree
void TreeInsert(Tree t, Time time) {
    t->root = doInsert(t->root, time);
}

static Node doInsert(Node n, Time time) {
    if (n == NULL) {
        return newNode(time);
    }

    // insert recursively
    int cmp = TimeCmp(time, n->time);
    if (cmp < 0) {
        n->left = doInsert(n->left, time);
    } else if (cmp > 0) {
        n->right = doInsert(n->right, time);
    } else { // (cmp == 0)
        // if time is already in the tree,
        // we can return straight away
        return n;
    }

    int hL = height(n->left);
    int hR = height(n->right);
    if ((hL - hR) > 1) {
        int cmp = TimeCmp(time, n->left->time);
        if (cmp > 0) {
            n->left = rotateLeft(n->left);
        }
        n = rotateRight(n);
    } else if ((hR - hL) > 1) {
        int cmp = TimeCmp(time, n->right->time);
        if (cmp < 0) {
            n->right = rotateRight(n->right);
        }
        n = rotateLeft(n);
    }

    // insertion done
    // correct the height of the current subtree
    n->height = 1 + max(height(n->left), height(n->right));
    return n;
    // rebalance the tree
    // TODO: Add your code here and change
    //       the return statement if needed

    // check if the tree is balanced or not
    // bool answer = checkNodeRecursively(n);
    // if (answer == true) {
    //     return n;
    // } else { // if not balance
    //     // rebalancing tree
    //     return rebalanceTreeRecur (n);
    // } 
}

Node partitionTreeRecur (Node n, int i) {
    // nitemLeft is #nodes in left subtree
    int nitemLeft = 0;
    nitemLeft = countNitemsRecursively(n->left, nitemLeft);
    if (i < nitemLeft) {
        n->left = partitionTreeRecur (n->left, i);
        n = rotateRight (n);
    } else if (i > nitemLeft) {
        n->right = partitionTreeRecur (n->right, i-nitemLeft-1);
        n = rotateLeft (n);
    }
    return n;
}

Node rebalanceTreeRecur (Node n) {
    int nitem = 0;
    nitem = countNitemsRecursively (n, nitem);
    if (nitem >= 3) {
        n = partitionTreeRecur (n, nitem/2);
        n->left = rebalanceTreeRecur (n->left);
        n->right = rebalanceTreeRecur (n->right);
    } 
    return n;
}

int countNitemsRecursively (Node t, int nitems) {
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

bool checkIfNodeIsPerfectlyBalanced (Node t) {
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

bool checkNodeRecursively (Node t) {
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
			answer = checkNodeRecursively (t->left);
		}
	}
	if (t->right != NULL) {
		answer = checkIfNodeIsPerfectlyBalanced (t->right);
		if (answer == false) {
			return false;
		} else {
			answer = checkNodeRecursively (t->right);
		}
	}
	return answer;
}

static Node newNode(Time time) {
    Node n = malloc(sizeof(*n));
    if (n == NULL) {
        fprintf(stderr, "Insufficient memory!\n");
        exit(EXIT_FAILURE);
    }

    n->time = TimeCopy(time);
    n->height = 0;
    n->left = NULL;
    n->right = NULL;
    return n;
}

// Rotates  the  given  subtree left and returns the root of the updated
// subtree.
static Node rotateLeft(Node n) {
    if (n == NULL || n->right == NULL) {
        return n;
    }
    Node n2 = n->right;
    n->right = n2->left;
    n2->left = n;

    n->height = max(height(n->left), height(n->right)) + 1;
    n2->height = max(height(n2->left), height(n2->right)) + 1;

    return n2;
}

// Rotates the given subtree right and returns the root of  the  updated
// subtree.
static Node rotateRight(Node n) {
    if (n == NULL || n->left == NULL) {
        return n;
    }
    Node n2 = n->left;
    n->left = n2->right;
    n2->right = n;

    n->height = max(height(n->left), height(n->right)) + 1;
    n2->height = max(height(n2->left), height(n2->right)) + 1;

    return n2;
}

// Returns  the height of a subtree while assuming that the height field
// of the root node of the subtree is correct
static int height(Node n) {
    if (n == NULL) {
        return -1;
    } else {
        return n->height;
    }
}

static int max(int a, int b) {
    return a > b ? a : b;
}

////////////////////////////////////////////////////////////////////////
// Specialised Operations

// Returns the latest time in the tree that is earlier than or equal  to
// the  given  time,  or  NULL if no such time exists. The returned time
// should not be modified or freed.
Time TreeFloor(Tree t, Time time) {
    // TODO: Add your code here and change
    //       the return statement if needed
    //       You can create helper functions
    //       if needed
    if (t == NULL) {
        return NULL;
    }

    int cmp = TimeCmp(time, t->root->time);
    if (cmp < 0) {
        if (t->root->left == NULL) {
            return NULL;
        } else {
            return CompareTimeEarlierRecur (t->root->left, time);
        }
    } else if (cmp > 0) {
        if (t->root->right == NULL) {
            return t->root->time;
        } else {
            Time answer = CompareTimeLaterRecur (t->root->right, time); 
            if (answer == NULL) {
                return t->root->time;
            } else {
                return answer;
            }
        } 
    } else { // (cmp == 0)
        // if time is already in the tree,
        // we can return straight away
        return t->root->time;
    }
    
    return NULL;
}

Time CompareTimeEarlierRecur (Node n, Time time) {
    int cmp = TimeCmp(time, n->time);
    if (cmp < 0) {
        if (n->left == NULL) {
            return NULL;
        } else {
            return CompareTimeEarlierRecur (n->left, time);
        }
    } else if (cmp > 0) {
        if (n->right == NULL) {
            return n->time;
        } else {
            Time answer = CompareTimeLaterRecur (n->right, time); 
            if (answer == NULL) {
                return n->time;
            } else {
                return answer;
            }
        }
    }
    return NULL;
}

Time CompareTimeLaterRecur (Node n, Time time) {
    int cmp = TimeCmp(time, n->time);
    if (cmp < 0) {
        if (n->left == NULL) {
            return NULL;
        } else {
            return CompareTimeEarlierRecur (n->left, time);
        }
    } else if (cmp > 0) {
        if (n->right == NULL) {
            return n->time;
        } else {
            Time answer = CompareTimeLaterRecur (n->right, time); 
            if (answer == NULL) {
                return n->time;
            } else {
                return answer;
            }
        }
    }
    return NULL;
}

// Returns the earliest time in the tree that is later than or equal  to
// the  given  time,  or  NULL if no such time exists. The returned time
// should not be modified or freed.
Time TreeCeiling(Tree t, Time time) {
    // TODO: Add your code here and change
    //       the return statement if needed
    //       You can create helper functions
    //       if needed

    return NULL;
}

////////////////////////////////////////////////////////////////////////
// Printing

//////////////////
// List the items

static void doList(Node n);

void TreeList(Tree t) {
    doList(t->root);
}

static void doList(Node n) {
    if (n != NULL) {
        doList(n->left);
        TimeShow(n->time);
        printf("\n");
        doList(n->right);
    }
}

///////////////////////////
// Show the tree structure

typedef unsigned long long uint64;
static void doShow(Node n, int level, uint64 arms);

void TreeShow(Tree t) {
    if (t->root != NULL && t->root->height >= 64) {
        printf("Tree is too tall!\n");
    } else {
        doShow(t->root, 0, 0);
    }
}

// This  function  uses a hack to determine when to draw the arms of the
// tree and relies on the tree being reasonably balanced. Don't  try  to
// use this function if the tree is not an AVL tree!
static void doShow(Node n, int level, uint64 arms) {
    if (n == NULL) return;

    TimeShow(n->time);
    printf(" (height: %d)\n", n->height);

    if (n->left != NULL) {
        for (int i = 0; i < level; i++) {
            if ((1LLU << i) & arms) {
                printf("│     ");
            } else {
                printf("      ");
            }
        }
        printf("%s", n->right != NULL ? "┝━╸L: " : "┕━╸L: ");
        if (n->right != NULL) {
            arms |= (1LLU << level);
        } else {
            arms &= ~(1LLU << level);
        }
        doShow(n->left, level + 1, arms);
    }

    if (n->right != NULL) {
        // if (n->left != NULL) {
        //     for (int i = 0; i <= level; i++) {
        //         if ((1LLU << i) & arms) {
        //             printf("│     ");
        //         } else {
        //             printf("      ");
        //         }
        //     }
        //     printf("\n");
        // }
        for (int i = 0; i < level; i++) {
            if ((1LLU << i) & arms) {
                printf("│     ");
            } else {
                printf("      ");
            }
        }
        printf("┕━╸R: ");
        arms &= ~(1LLU << level);
        doShow(n->right, level + 1, arms);
    }
}

////////////////////////////////////////////////////////////////////////
// Testing
// All  functions below exist for testing purposes ONLY. Do NOT use them
// in your code.

static Node doInsertLeaf(Node n, Time time);

void TreeRotateLeftAtRoot(Tree t) {
    t->root = rotateLeft(t->root);
}

void TreeRotateRightAtRoot(Tree t) {
    t->root = rotateRight(t->root);
}

void TreeInsertLeaf(Tree t, Time time) {
    t->root = doInsertLeaf(t->root, time);
}

static Node doInsertLeaf(Node n, Time time) {
    if (n == NULL) {
        return newNode(time);
    }

    int cmp = TimeCmp(time, n->time);
    if (cmp < 0) {
        n->left = doInsertLeaf(n->left, time);
    } else if (cmp > 0) {
        n->right = doInsertLeaf(n->right, time);
    }

    n->height = 1 + max(height(n->left), height(n->right));
    return n;
}
