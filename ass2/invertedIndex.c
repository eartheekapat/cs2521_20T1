#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
 
#include "invertedIndex.h"

#define MAXCHAR 1000

// create new inverted index node
InvertedIndexBST newInvertedIndexNode (char *key);
// create new file list node
urlList newUrlListNode (char *url);
// find the right position to insert node2 into the tree
void compareKeyToInsertRecur (InvertedIndexBST node1, InvertedIndexBST node2);
// insert filename into the node->fileList in the right order
void insertUrlListNode (InvertedIndexBST node, char *filename);
// find the matched key node in the tree and return the node
InvertedIndexBST findKeyRecur (InvertedIndexBST node, char *str);
// loop through buffer to get nodes in the right order to print to invertedIndex.txt
void loopThroughArrayNprintii  (char buffer[][MAXCHAR], int nitem, InvertedIndexBST node, FILE *fp);
// put the whole tree keys into array
int putTreeIntoArrayRecur (InvertedIndexBST t, char buffer[][MAXCHAR], int nitem);
// sort array components in the lexicographical order
void arraySortAscendLexi (char buffer[][MAXCHAR], int i);
// code for strdup from // code from https://stackoverflow.com/questions/37132549/implementation-of-strdup-in-c-programming
char *myStrdup(const char *s1);
// converting all characters to lowercase code from https:
// codeforwin.org/2015/04/c-program-convert-upper-case-string-to-lower.html
char *toLow(char *str);

InvertedIndexBST generateInvertedIndex (char *collectionFilename) {
    FILE *fp1, *fp2;
    char str1[MAXCHAR], str2[MAXCHAR];
    fp1 = fopen (collectionFilename, "r");
     // declare head to store the value of the first node
    InvertedIndexBST head = newInvertedIndexNode("head");
    while (fscanf(fp1, "%s", str1) != EOF) {
        char *newstr1 = myStrdup(str1);
        fp2 = fopen (str1, "r");
        while (fscanf(fp2, "%s", str2) != EOF) { 
            char *newstr2 = myStrdup(str2);
            if (strcmp(normaliseWord(newstr2), "design") == 0) {}
            // create new node which has str2 as a key
            if (head->right == NULL) { // head->right is just the head node of the tree
                // create head node
                head->right = newInvertedIndexNode (normaliseWord(newstr2));
                head->right->urlList = newUrlListNode (newstr1);
            } else { 
                //check if the key already exists in the tree
                InvertedIndexBST temp = findKeyRecur (head->right, newstr2);
                if (temp == NULL) { // if not exist
                    // create new node which has str2 as a key
                    InvertedIndexBST node = newInvertedIndexNode (normaliseWord(newstr2));
                    node->urlList = newUrlListNode (newstr1);
                    // then insert the node into the tree
                    compareKeyToInsertRecur (head->right, node);
                } else { // if exist
                        // insert into the fileList of the node
                        insertUrlListNode (temp, newstr1);
                }
            }       
        }
        fclose(fp2);
    }
    fclose(fp1);
    return head->right;
}

InvertedIndexBST newInvertedIndexNode (char *key) {
    InvertedIndexBST node = malloc(sizeof(*node));
    if (node == NULL) {
        fprintf(stderr, "Insufficient memory!\n");
        exit(EXIT_FAILURE);
    }
    node->word = key;
    node->urlList = NULL;
    node->left = NULL;
    node->right = NULL;
    return node;
}

urlList newUrlListNode (char *url) {
    urlList node = malloc(sizeof(*node));
    if (node == NULL) {
        fprintf(stderr, "Insufficient memory!\n");
        exit(EXIT_FAILURE);
    }
    node->url = url;
    node->next = NULL;
    return node;
}

void compareKeyToInsertRecur (InvertedIndexBST node1, InvertedIndexBST node2) {
    if (strcmp(node1->word, node2->word) < 0) {
        if (node1->right == NULL) {
            node1->right = node2;
        } else {
            compareKeyToInsertRecur (node1->right, node2);
        }
    } else if (strcmp(node1->word, node2->word) > 0) {
        if (node1->left == NULL) {
            node1->left = node2;
        } else {
            compareKeyToInsertRecur (node1->left, node2);
        }
    } else {
        return free(node2);
    }
}

void insertUrlListNode (InvertedIndexBST node, char *url) {
    //loop to find the right order 
    urlList before_curr, curr = node->urlList;
    while (curr != NULL) {
        // compare filename with the exist file name to insert in the right order
        int cmp = strcmp (url, curr->url);
        if (cmp == 0) {
            //do sth in the future but now do nth
            return;
        } else if (cmp < 0) { // insert 
            // check if the node to insert is the first node of the fileList
            if (node->urlList == curr) {
                urlList temp = node->urlList;
                node->urlList = newUrlListNode (url);
                node->urlList->next = temp;
                return;
            } else { // in the middle
                before_curr->next = newUrlListNode (url);
                before_curr->next->next = curr;
                return;
            }
        } else if (cmp>0) {
            if (curr->next == NULL) {
                curr->next = newUrlListNode (url);
                return;
            }
        }
        before_curr = curr;
        curr = curr->next;
    }
}

InvertedIndexBST findKeyRecur (InvertedIndexBST node, char *str) {
    if (node == NULL) {
        return NULL;
    }
    int cmp = strcmp(str, node->word);
    if (cmp == 0) {
        return node;
    } else if (cmp < 0) {
        return findKeyRecur (node->left, str);
    } else if (cmp > 0) {
        return findKeyRecur (node->right, str);
    }
    return NULL;
}

void loopThroughArrayNprintii (char buffer[][MAXCHAR], int nitem, InvertedIndexBST node, FILE *fp) {
    if (node == NULL) {
        return;
    } else {
        // find the smallest value in tree recursively
        for (int k = 0; k < nitem; ++k) {
            InvertedIndexBST temp = findKeyRecur (node, buffer[k]);
            fprintf(fp, "%s ", temp->word);
            urlList curr = temp->urlList;
            while (curr != NULL) {
                fprintf(fp, "%s ", curr->url);
                curr = curr->next;
            }
            fprintf(fp, "%c", '\n');
        }
    }
}

int putTreeIntoArrayRecur (InvertedIndexBST t, char buffer[][MAXCHAR], int nitem) {
    strcpy(buffer[nitem], t->word);
    nitem++;
    if (t->left != NULL) {
        nitem = putTreeIntoArrayRecur (t->left, buffer, nitem);
    }
    if (t->right != NULL) {
        nitem = putTreeIntoArrayRecur (t->right, buffer, nitem);
    }
    if (t->left == NULL && t->right == NULL) {
        return nitem;
    }
    return nitem;
}

void arraySortAscendLexi (char buffer[][MAXCHAR], int i) {
    char temp [MAXCHAR];
    for (int k = 0; k < i; ++k) {
            for (int j = k + 1; j < i; ++j) {
                if (strcmp(buffer[k], buffer[j]) > 0) {
                    strcpy(temp, buffer[k]);
                    strcpy(buffer[k], buffer[j]);
                    strcpy(buffer[j], temp);
                }
            }
        }
}

char *normaliseWord(char *str) {
    //remove leading & trailing space 
    // https://codeforwin.org/2016/04/c-program-to-trim-both-leading-and-trailing-white-spaces-in-string.html
    int index, i;
    //Trim leading white spaces
    index = 0;
    while(str[index] == ' ' || str[index] == '\t' || str[index] == '\n') {
        index++;
    }
    // Shift all trailing characters to its left
    i = 0;
    while(str[i + index] != '\0') {
        str[i] = str[i + index];
        i++;
    }
    str[i] = '\0'; // Terminate string with NULL
    // Trim trailing white spaces
    i = 0;
    index = -1;
    while(str[i] != '\0') {
        if(str[i] != ' ' && str[i] != '\t' && str[i] != '\n') {
            index = i;
        }
        i++;
    }
    // Mark the next character to last non white space character as NULL 
    str[index + 1] = '\0';

    int len = strlen(str);
    for (i = 0; i < len+1; i++) {
        // check if str[i] is the 4 punc and is at the end of the word
        if ((str[i] == '.' || str[i] == ',' || str[i] == ';' || str[i] == '?')
        && i == len - 1) 
        {
            str[i] = '\0';
        }
    }   
    return toLow(str);
}

char *toLow(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if(str[i] >= 'A' && str[i] <= 'Z'){
            str[i] = str[i] + 32;
        }
    }
    return str;
}

char *myStrdup(const char *s1) {
  char *str;
  size_t size = strlen(s1) + 1;

  str = malloc(size);
  if (str) {
    memcpy(str, s1, size);
  }
  return str;
}