// equalBST.c ... implementation of equalBST function

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"

/* 
    You will submit only this one file.

    Implement the function "equalBST" below. Read the exam paper for a
    detailed specification and description of your task.  

    - DO NOT modify the code in any other files. 
    - You can add static helper functions to this file.  
    - DO NOT add a "main" function to this file. 
*/

int findDifference (BSTree t1, BSTree t2);

int equalBST(BSTree t1, BSTree t2) {
    int isDiffer = findDifference (t1, t2);
    // isDiffer is true return 0, isDiffer is false return 1.
    if (isDiffer != 0) {
        return 0;
    } else {
        return 1;
    }
}

int findDifference (BSTree t1, BSTree t2) {
    // check both nodes
    if (t1 == NULL && t2 == NULL) {
        return 0;
    } else if ((t1 != NULL && t2 == NULL) || (t1 == NULL && t2 != NULL)) {
        return 1;
    } else { // both nodes are not NULL 
        if (t1->key != t2->key) {
            return 1;
        }
        if ((t1->left != NULL && t2->left == NULL) ||
            (t1->left == NULL && t2->left != NULL)) {
                return 1;
        }
        if ((t1->right != NULL && t2->right == NULL) ||
            (t1->right == NULL && t2->right != NULL)) {
                return 1;
            }
        int left = findDifference (t1->left, t2->left);
        int right = findDifference (t1->right, t2->right);
        return left + right;
    }
    return 0;
}
