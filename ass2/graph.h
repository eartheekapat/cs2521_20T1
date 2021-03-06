// graph.h ... Interface to Graph of strings

#ifndef GRAPH_H
#define GRAPH_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <err.h>
#include <sysexits.h>
#include <sys/types.h>

typedef struct GraphRep *Graph;

// Function signatures

Graph newGraph (size_t);
void dropGraph (Graph);
bool addEdge (Graph, char *, char *);
size_t nVertices (Graph);
bool isConnected (Graph, char *, char *);
void showGraph (Graph, int);
void addPageRank (Graph g, char *vertex, double PR);
ssize_t vertexID (char *str, char **names, size_t N);
double getPR (Graph g, char *vertex);
char* mystrdup(const char* s);	//in case it is not included in string.h
#endif