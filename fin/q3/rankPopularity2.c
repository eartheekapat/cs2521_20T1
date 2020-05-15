// rankPopularity.c ... implementation of rankPopularity function

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

/* 
    You will submit only this one file.

    Implement the function "rankPopularity" below. Read the exam paper for a
    detailed specification and description of your task.  

    - DO NOT modify the code in any other files. 
    - You can add static helper functions to this file.  
    - DO NOT add a "main" function to this file. 
*/

// Create a "global" visited array - doesn't need to be global since arrays are pass by reference
int visited[1000] = {0};

// insert Popularity Rank into array mnV
void insertPopRank (double *mnV, Vertex v, double popRank);
//  calulate Popularity Rank
double calPopRank (Graph g, Vertex v);
// check if dest if reachable by src
bool findPathDFS (Graph g, Vertex src, Vertex dest);
bool dfsPathCheck (Graph g, Vertex src, Vertex dest);

void rankPopularity(Graph g, int src, double *mnV) {
    // loop through each vertex
	for (Vertex v = 0; v <= g->nV; v++) { 
        if (v == src) {
            double popRank = calPopRank (g, v);
            insertPopRank (mnV, v, popRank);
        }
        if (!findPathDFS (g, src, v)) {
            continue;
        }
        double popRank = calPopRank (g, v);
        insertPopRank (mnV, v, popRank);
    }
}

double calPopRank (Graph g, Vertex v) {
    // count in by count #1 in y so fix x
    double countInDeg = 0;
    int i;
    for (i = 0; i < g->nV; i++) {
        if (g->edges[i][v] == 1) {
            countInDeg++;
        }
    }
    // count in by count #1 in y so fix y
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
    return popRank; 
}

void insertPopRank (double *mnV, Vertex v, double popRank) {
    mnV[v] = popRank;
}

bool dfsPathCheck (Graph g, Vertex src, Vertex dest) {
    for (Vertex w = 0; w < g->nV; w++) {
        if (visited[w] == -1 && adjacent(g, src, w)) {
            visited[w] = src;
            if (w == dest) {
                return true;
            } else if (dfsPathCheck (g, w, dest)) {
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