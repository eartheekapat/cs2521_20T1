// readData.h ... read data function from the collection
// Written by Theekapat Charnvitayapong April 2020

#ifndef READDATA_H
#define READDATA_H

#define MAX_WORD 5000
#define MAX_CHAR 1000
#define MAX_URL 100
#define p(...) printf(__VA_ARGS__)

#include "graph.h"

extern int numUrl;
extern char ** List_of_Urls;

//normalise a word
char * normaliseWord(char *str);

// convert string to lower case
char * toLow(char *str);

// read from collection.txt and return a linked list of url
char ** GetCollection();

// read data from a file and put it into strings
char * readFile (char * filename);

// read words seperated by tabs or spaces or newline and put it into destination array
int storeUrlInArray(char *content, char**);

// read from collection.txt and return an array of string (url)
char ** GetCollection ();

// Create a graph from List of URLs
Graph GetGraph (char **);

// read the url from the file and put it into graph
void updateGraph (Graph , char* filename);

#endif