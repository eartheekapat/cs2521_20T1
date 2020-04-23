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
#include "invertedIndex.c"

#define LINE_LENGTH 100
#define BUFSIZE 50

#define MAXCHAR 1000

void GetCollection ();

// int main(int argc, char *argv[])
int main () 
{
	// if (argc < 4) {
	// 	fprintf(stderr, "Usage: %s  <damping factor> <difference in PageRank sum> <maximum iterations>\n", argv[0]);
	// 	return EXIT_FAILURE;
	// }

    // char **List_of_Urls = 
    GetCollection();
    // Graph g = GetGraph(List_of_Urls);
    // char **List = calculatePageRank(g, atof(argv[1]),  atof(argv[2]),  atof(argv[3]));
    // char **OrderedList = order(List);
    // outToFile(OrderedList, "pagerankList.txt");

    return EXIT_SUCCESS;
}

void GetCollection () {
    FILE *fp1, *fp2;
        char collectionFilename[MAXCHAR] = "collection.txt";
        char txt[MAXCHAR] = ".txt";
        char str1[MAXCHAR], str2[MAXCHAR];
        fp1 = fopen (collectionFilename, "r");
        while (fscanf(fp1, "%s", str1) != EOF) {
            fp2 = fopen (strcat(str1, txt), "r");
            while (fscanf(fp2, "%s", str2) != EOF) {
                if (strcmp(str2, "#start") == 0 || strcmp(str2, "Section-1") == 0 ||
                    strcmp(str2, "#end") == 0) {
                    continue;
                } else if (strcmp(str2, "Section-2") == 0) {
                    break;
                }
                printf("%s\n", str2);
            }
        }
}   