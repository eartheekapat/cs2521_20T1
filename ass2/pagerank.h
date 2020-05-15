#ifndef PAGERANK_H
#define PAGERANK_H

#define LINE_LEN 100
#define BUFSIZE 50

#include "graph.h"
#include "readData.h"

char ** calculatePageRank(Graph g, double d, double diffPR, int maxIterations);

double sum_PR (Graph g, char * vertex);

double calculateWin (Graph g, char * vertex, char * vertex2);
double calculateWout (Graph g, char * vertex, char * vertex2);

int numInDegree (Graph g, char * vertex);
int numOutDegree (Graph g, char * vertex);

char ** order(char **);

void output (char ** List, char * filename);

#endif