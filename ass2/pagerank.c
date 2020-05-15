// Calculate PageRank from a List of Page
// Written by Theekapat Charnvitayapong April 2020

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <err.h>
#include <sysexits.h>

#include "pagerank.h"

double pageRank[MAX_URL];

int main(int argc, char *argv[]) {
	if (argc < 4) {
		fprintf(stderr, "Usage: %s  <damping factor> <difference in PageRank sum> <maximum iterations>\n", argv[0]);
		return EXIT_FAILURE;
	}

    char ** List_of_Urls = GetCollection();
    Graph g = GetGraph(List_of_Urls);
    double d = atof(argv[1]);
    double diffPR = atof(argv[2]);
    double maxIterations = atof(argv[3]);
    char ** List_Urls_PageRanks = calculatePageRank(g, d, diffPR, maxIterations);
    char ** Ordered_List_Urls_PageRanks = order(List_Urls_PageRanks);

    output (Ordered_List_Urls_PageRanks, "pagerankList.txt");

    return EXIT_SUCCESS;
}

char ** calculatePageRank (Graph g, double d, double diffPR, int maxIterations) {
    char ** List_Urls_PageRanks = malloc (sizeof(char*) * MAX_URL);
    double PR = 1/numUrl;
    int i;

    // loop through listUrlsPageRanks to allocate memory
    for (i = 0; i < numUrl; i++) {
        List_Urls_PageRanks[i] = malloc (sizeof(char) * LINE_LEN);
        addPageRank (g, List_of_Urls[i], PR);
    }
    // loop through pageRank amd assign
    for (i = 0; i < numUrl; i++) {
        pageRank[i] = PR;
    }   

    int iter = 0;
    double diff = diffPR;

    while (iter < maxIterations && diff >= diffPR) {
        for (i = 0; i < numUrl; i++) {
            PR = (1-d)/(double)numUrl + (d *sum_PR(g, List_of_Urls[i]));
            addPageRank(g, List_of_Urls[i], PR);
            PR = 0;
        }
        //update PageRank for prev iteration
        for (i = 0; i < numUrl; i++) {
            pageRank[i] = getPR(g, List_of_Urls[i]);
        }
        iter++;
    }
    // loop to put data into ListUrlPageRanks
    for (int i = 0; i < numUrl; i++) {
        char line[BUFSIZE];
        sprintf(line, "%s, %d, %.7f", List_of_Urls[i], numOutDegree(g, List_of_Urls[i]), pageRank[i]);
        strcpy(List_Urls_PageRanks[i], line);
    }
    return List_Urls_PageRanks;  
}

//calculate the sum of pagerank 
double sum_PR(Graph g, char *vertex) {
    double sum = 0;
    for (int i = 0; i < numUrl; i++) {
        sum += pageRank[i] * calculateWin(g, List_of_Urls[i], vertex) * calculateWout(g, List_of_Urls[i], vertex);
    }
    return sum;
}

//return the out degree of a vertex
int numOutDegree(Graph g, char *vertex) {
    int count = 0;
    for (int i = 0; i < numUrl; i++) {
        if (isConnected(g, vertex, List_of_Urls[i])) {
            if (strcmp(vertex, List_of_Urls[i]) == 0) {
                continue;
            }
            count++;
        }
    }
    return count;
}

// return the In degree of a vertex
int numInDegree (Graph g, char * vertex) {
    int count = 0;
    for (int i = 0; i < numUrl; i++) {
        if (isConnected(g, List_of_Urls[i], vertex )) {
            if (strcmp(vertex, List_of_Urls[i]) == 0) {
                continue;
            }
            count++;
        }
    }
    return count;
}

// output the list to the file with filename
void output (char ** List, char * filename) {
    FILE * fp = fopen(filename, "w");
    if (fp == NULL) {
      fprintf(stderr, "Can't create %s file", filename);
      exit(1);
   }
    int i = 0;
    while(i < numUrl) {
        fprintf(fp, "%s\n", List[i]);
        i++;
    }
    fclose(fp);
}