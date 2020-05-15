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

// if found a different key return number != 0
int CompareKeyRecur (BSTree t1, BSTree t2);

int equalBST(BSTree t1, BSTree t2) {
    int differ = CompareKeyRecur (t1, t2);
    return differ == 0? 1 : 0;
}

int CompareKeyRecur (BSTree t1, BSTree t2) {
    // check the node
    if (t1 == NULL && t2 == NULL) {
        return 0;
    } else if ((t1 != NULL && t2 == NULL) ||
            (t1 == NULL && t2 != NULL)) {
        return 1;        
    } else if (t1->key != t2->key) { // compare key
        return 1;
    } else { // compare recur
        int compLeft = CompareKeyRecur (t1->left, t2->left);
        int compRight = CompareKeyRecur (t1->left, t2->left);
        return compLeft + compRight;
    }
}
  


