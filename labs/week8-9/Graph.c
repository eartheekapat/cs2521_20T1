// Graph.c ... implementation of Graph ADT
// Written by John Shepherd, May 2013

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "Graph.h"
#include "Queue.h"

#define NUM_VERTICES 100

// graph representation (adjacency matrix)
typedef struct GraphRep {
	int nV;		 // #vertices
	int nE;		 // #edges
	int **edges; // matrix of weights (0 == no edge)
} GraphRep;

// check validity of Vertex
int validV (Graph g, Vertex v)
{
	return (g != NULL && v >= 0 && v < g->nV);
}

// make an edge
static Edge mkEdge (Graph g, Vertex v, Vertex w)
{
	assert (g != NULL && validV (g, v) && validV (g, w));
	Edge new = {v, w}; // struct assignment
	return new;
}

// insert an Edge
// - sets (v,w) and (w,v)
void insertEdge (Graph g, Vertex v, Vertex w, int wt)
{
	assert (g != NULL && validV (g, v) && validV (g, w));

	if (g->edges[v][w] != 0 && g->edges[w][v] != 0)
		// an edge already exists; do nothing.
		return;

	g->edges[v][w] = wt;
	g->edges[w][v] = wt;
	g->nE++;
}

// remove an Edge
// - unsets (v,w) and (w,v)
void removeEdge (Graph g, Vertex v, Vertex w)
{
	assert (g != NULL && validV (g, v) && validV (g, w));
	if (g->edges[v][w] == 0 && g->edges[w][v] == 0)
		// an edge doesn't exist; do nothing.
		return;

	g->edges[v][w] = 0;
	g->edges[w][v] = 0;
	g->nE--;
}

// create an empty graph
Graph newGraph (int nV)
{
	assert (nV > 0);

	GraphRep *new = malloc (sizeof *new);
	assert (new != NULL);
	*new = (GraphRep){ .nV = nV, .nE = 0 };

	new->edges = calloc ((size_t) nV, sizeof (int *));
	assert (new->edges != NULL);
	for (int v = 0; v < nV; v++) {
		new->edges[v] = calloc ((size_t) nV, sizeof (int));
		assert (new->edges[v] != 0);
	}

	return new;
}

// free memory associated with graph
void dropGraph (Graph g)
{
	assert (g != NULL);
	for (int v = 0; v < g->nV; v++)
		free (g->edges[v]);
	free (g->edges);
	free (g);
}

// display graph, using names for vertices
void showGraph (Graph g, char **names)
{
	assert (g != NULL);
	printf ("#vertices=%d, #edges=%d\n\n", g->nV, g->nE);
	int v, w;
	for (v = 0; v < g->nV; v++) {
		printf ("%d %s\n", v, names[v]);
		for (w = 0; w < g->nV; w++) {
			if (g->edges[v][w]) {
				printf ("\t%s (%d)\n", names[w], g->edges[v][w]);
			}
		}
		printf ("\n");
	}
}

// find a path between two vertices using breadth-first traversal
// only allow edges whose weight is less than "max"
int findPath (Graph g, Vertex src, Vertex dest, int max, int *path)
{
	assert (g != NULL);

    // Initialise visited array to -1
    int visited[NUM_VERTICES] = {0};
    for (int i = 0; i < g->nV; i++) {
        visited[i] = -1;
    }
 
    visited[src] = src;
    bool isFound = false;
    Queue q = newQueue();
    QueueJoin(q, src);
 
    while (!isFound && !QueueIsEmpty(q)) {
		// declare V = item from front of Queue
        Item v = QueueLeave(q);
        if (v == dest) {
			isFound = true;
		} else {
			// loop through all vertexs
            for (int vertex_id = 0; vertex_id < g->nV; vertex_id++) {
                // For each edge connecting to v
                Vertex w = g->edges[v][vertex_id];
                // Valid edge is (<= max distance N distance is > 0 N unvisited).
                if (w <= max && w != 0 && visited[vertex_id] == -1) {
                    visited[vertex_id] = v;
                    QueueJoin(q, vertex_id);
                }
            }
        }
    }
    dropQueue(q);
 
    Vertex curr = dest;
    int temp[NUM_VERTICES] = {dest};
    // Number of vertices 
	int pathLength = 1;  

    while (curr != src && curr != -1) { 
 		// Store path from dest to src
        temp[pathLength] = visited[curr];
        curr = visited[curr];
    	pathLength++;
    }

    if (curr == -1)	{	
	 return 0;
	}

    // Return min length path
    int j = 0;
    for (int i = pathLength - 1; i >= 0; i--, j++) {
        path[j] = temp[i];
    }

    return pathLength;
}

