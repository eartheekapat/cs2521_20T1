#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <err.h>
#include <sysexits.h>
#include <ctype.h>

#include "readData.h"
#include "invertedIndex.h"

extern int numUrl = 0;
extern char ** List_of_Urls;
Graph urlGraph;

char *normaliseWord(char *str) {
    //remove leading & trailing space 
    // https://codeforwin.org/2016/04/c-program-to-trim-both-leading-and-trailing-white-spaces-in-string.html
    int index, i;
    //Trim leading white spaces
    index = 0;
    while(str[index] == ' ' || str[index] == '\t' || str[index] == '\n') {
        index++;
    }
    // Shift all trailing characters to its left
    i = 0;
    while(str[i + index] != '\0') {
        str[i] = str[i + index];
        i++;
    }
    str[i] = '\0'; // Terminate string with NULL
    // Trim trailing white spaces
    i = 0;
    index = -1;
    while(str[i] != '\0') {
        if(str[i] != ' ' && str[i] != '\t' && str[i] != '\n') {
            index = i;
        }
        i++;
    }
    // Mark the next character to last non white space character as NULL 
    str[index + 1] = '\0';

    int len = strlen(str);
    for (i = 0; i < len+1; i++) {
        // check if str[i] is the 4 punc and is at the end of the word
        if ((str[i] == '.' || str[i] == ',' || str[i] == ';' || str[i] == '?')
        && i == len - 1) 
        {
            str[i] = '\0';
        }
    }   
    return toLow(str);
}

char *toLow(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if(str[i] >= 'A' && str[i] <= 'Z'){
            str[i] = str[i] + 32;
        }
    }
    return str;
}

char ** GetCollection () {
    List_of_Urls = malloc (MAX_CHAR * MAX_CHAR);
    numUrl = storeUrlInArray (readFile("collection.txt"), List_of_Urls);
    return List_of_Urls;
}   

char * readFile (char *filename) {
    int str_size, read_size;
    FILE * fp = fopen(filename, "r");
    if(fp == NULL) {
        printf("Error!, can't open the file\n");
        exit(1); 
    }
    // find last byte of the file
    fseek (fp, 0, SEEK_END);
    // str_size = filesize
    str_size = ftell(fp);
    // move pointer back to the start of the file
    rewind (fp);

    // allocate memory to store all char + '\0'
    char * buffer = malloc (sizeof(char) * (str_size + 1));
    // read all
    read_size = fread (buffer, sizeof(char), str_size, fp);
    // add '\0' at the end of buffer
    buffer[str_size] = '\0';
    // check if there is something wrong
    if (str_size != read_size) { 
        // sth's worng, clear (free) buffer 
        free(buffer);
    }

    fclose(fp);

    return buffer;
}

// store words (url) into array return number of url (N)
int storeUrlInArray (char *text, char *List_of_Url[]) {
    // declare array of string to store url 
    char *buffer[MAX_CHAR];

    char *word;
    word = strtok(text, " ,  \n");
    int i = 0;
    while ( word != NULL) {
        word = normaliseWord (word);
        buffer[i] = malloc (sizeof(char) * (strlen(word + 1)));
        strcpy (buffer[i], word);
        word = strtok (NULL, " ,  \n");
        i++;
    }
    // copy buffer to List_of_Urls
    for (int j = 0; j < i; j++) {
        List_of_Url[j] = malloc (sizeof(char) * strlen (buffer[j] + 1));
        strcpy (List_of_Url[j], buffer[j]);
        free (buffer[j]);
    }
    // return N ( number of url )
    return i;
}

Graph GetGraph (char ** List_of_Urls) {
    // declare graph g as new graph
    Graph g = newGraph (numUrl);
    // loop through each url in List of Url
    for (int i = 0; i < numUrl; i++) {
        updateGraph (g, List_of_Urls[i]);
    }
}

// read section 1 and put url into the graph
void updateGraph (Graph g, char * filename) {
    char ** url = malloc (sizeof(char *) * MAX_URL);
    char * filename_txt = malloc (sizeof (char) * MAX_URL);
    // copyt filename.txt into filename_txt
    strcpy (filename_txt, strcat(filename, ".txt"));
    // declare buffer to store content from filename(url).txt
    char * buffer = readFile (filename_txt);
    // move pointer 16 bits so it skips "#start Section-1"
    buffer = buffer + 16;
    free (filename_txt);
    // find the end of section 1 and add null-terminated '\0'
    char *endOfSec1 = strstr (buffer, "#end Section-1");
    *endOfSec1 = '\0';
    // count numberOfUrl in sec1 of each url.txt file 
    // then loop through and add edge
    int countUrl = storeUrlInArray (buffer, url);
    for (int i = 0; i < countUrl; i++) {
        addEdge (g, filename, url[i]);
    }
}

