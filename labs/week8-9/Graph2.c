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
    // declare visited array
    int *visited = calloc(g->nV, sizeof(int));
    int *pred = calloc(g->nV, sizeof(int));
    int index_counter = 0;
    // loop to change all value in visited array to -1
    while (index_counter < g->nV) {
        pred[index_counter] = -1;
        index_counter++;
    }
    // declare a queue
    Queue q = newQueue();
    // add src to q
    QueueJoin(q, src);
    // while the queue is not empty
    while (!QueueIsEmpty(q)) {
        // declare x = item from front of Queue
        Vertex x = QueueLeave(q);
        // if x has been visited, ignore it
        if (visited[x]) {
            continue;
        }
        visited[x] = 1;
        // traversing the graph
        for (Vertex y = 0; y < g->nV; y++) {
            // if there is no edge between x and y, ignore it
            if (!g->edges[x][y]) {
                continue;
            }
            // if the edge between x and y exceeds max, ignore it again
            if (g->edges[x][y] > max) {
                continue;
            }
            // if y has not been visited, it joins the queue
            if (!visited[y]) {
                QueueJoin(q, y);
                // if y remains unchanged, then predecessor is updated
                if (pred[y] == -1) {
                    pred[y] = x;
                }
            }
            // if y is at the destination, then the loop is ended
            if (y == dest) {
                break;
            }
        }
    }
    int counter = 0;
    Vertex curr = dest;
    // traverse backwards through the path array
    while (curr != src) {
        curr = pred[curr];
        // if there is no path to curr, then free memory and return
        if (curr == -1) {
            dropQueue(q);
            free(visited);
            free(pred);
            return 0; // never find a path
        }
        counter++;
    }
    // and then reverses the path array
    int index = counter;
    curr = dest;
    // copy all paths, except src vertex
    while (index >= 1) {
        path[index] = curr;
        curr = pred[curr];
        index--;
    }
    path[0] = src;
    // counting the src
    counter++;
    dropQueue(q);
    free(visited);
    free(pred);
    return counter;
}