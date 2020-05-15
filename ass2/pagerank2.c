// In this assignment, the task is to implement simple search engines 
// using the well known algorithm (Weighted) PageRank
// The main focus of this assignment is to build a graph structure and 
// calculate Weighted PageRanks, and rank pages based on these values

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// #include "readData.h"
// #include "pagerank.h"
// #include "graph.h"

#define MAXCHAR 100

struct urlListNode {
	char *url;
	struct urlListNode *next;
};
typedef struct urlListNode *url_list;

url_list GetCollection();
url_list new_url_list_node (char * url);
void insert_url_list_node(url_list List_of_Urls, char *url);

int main(void) {
    url_list List_of_Urls = GetCollection();
}

url_list GetCollection() {
    FILE * fp1;
    char collection_filename[MAXCHAR] = "collection.txt";
    char str1[MAXCHAR];
    fp1 = fopen(collection_filename, "r");
    // declaring url_list data type with a "null" value
    url_list List_of_Urls = new_url_list_node("null");
    // scan word by word in collection.txt
    while (fscanf(fp1, "%s", str1) != EOF) {
        char *newstr1 = strdup(str1);
        if (strcmp(List_of_Urls->url, "null") ==0) {
            List_of_Urls->url = newstr1;
        } else {
            insert_url_list_node(List_of_Urls, newstr1);
        }
    }
    return List_of_Urls;
}

url_list new_url_list_node (char * url) {
    url_list node = malloc(sizeof(*node));
    if (node == NULL) {
        fprintf(stderr, "Insufficient memory!\n");
        exit(EXIT_FAILURE);
    }
    node->url = url;
    node->next = NULL;
    return node;
}

void insert_url_list_node(url_list List_of_Urls, char *url) {
    url_list curr = List_of_Urls;
    // loop to the last node of the url_list
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = new_url_list_node (url);
}