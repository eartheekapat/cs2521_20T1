// rankPopularity.c ... implementation of rankPopularity function

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Graph.h"

#define MAX_NODE 1000

/* 
    You will submit only this one file.

    Implement the function "rankPopularity" below. Read the exam paper for a
    detailed specification and description of your task.  

    - DO NOT modify the code in any other files. 
    - You can add static helper functions to this file.  
    - DO NOT add a "main" function to this file. 
*/

// calculate PopRank and then insert into array mnV
void calNinsertPopRank (Graph g, double *mnV, Vertex v);
// code from lecture 5a
bool dfsPathCheck (Graph g, Vertex src, Vertex dest);
bool findPathDFS (Graph g, Vertex src, Vertex dest); 

int visited[MAX_NODE];

void rankPopularity(Graph g, int src, double *mnV) {
    // loop through each vertex
	for (Vertex v = 0; v < g->nV; v++) {
        if (v == src) { // if it's soure call func. instantly
            calNinsertPopRank (g, mnV, v);
        }
        bool isReachable = findPathDFS (g, src, v);
        if (!isReachable) {
            continue;
        }
        calNinsertPopRank (g, mnV, v);
    }
}

void calNinsertPopRank (Graph g, double *mnV, Vertex v) {
    double countInDeg = 0;
    int i;
    // count In degree
    for (i = 0; i < g->nV; i++) {
        if (g->edges[i][v] == 1) {
            countInDeg++;
        }
    }
    // count out degree
    double countOutDeg = 0;
    for (i = 0; i < g->nV; i++) {
        if (g->edges[v][i] == 1) {
            countOutDeg++;
        }
    }
    // after count 
    if (countOutDeg == 0) {
        countOutDeg = 0.5;
    }
    double popRank = countInDeg / countOutDeg;
    mnV[v] = popRank;
}

bool dfsPathCheck (Graph g, Vertex src, Vertex dest) {
    for (Vertex j = 0; j < g->nV; j++) {
        if (visited[j] == -1 && adjacent(g, src, j)) {
            visited[j] = src;
            if (j == dest) {
                return true;
            } else if (dfsPathCheck (g, j, dest)) {
                return true;
            }
        }
    }
    return false;
}

bool findPathDFS (Graph g, Vertex src, Vertex dest) {
    for (Vertex v = 0; v < g->nV; v++) {
        visited[v] = -1;
    }
    visited[src] = 1;
    return dfsPathCheck (g, src, dest);
}