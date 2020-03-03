// testList.c - testing DLList data type
// Written by John Shepherd, March 2013

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "DLList.h"

#define STR_LEN 50

// insert before and after 
// assert length and expected current value
void test_1 (DLList myList);
// Testing delete
void test_2 (DLList myList);
// Prints entire List in a certain format
void printList (DLList myList);
// Test from lab partner
void test_Eric (DLList myList);

int main (void)
{
    DLList myList = getDLList (stdin);
    test_1(myList);
    test_Eric(myList);
    test_2(myList);
    DLListDelete(myList);
    printList(myList);
    assert(validDLList(myList));
    freeDLList (myList);
    return EXIT_SUCCESS;
}

void test_1 (DLList myList)
{
	// variable hold initial length of the list
    size_t init_len = DLListLength(myList);
	// check internal consistency
    assert(validDLList (myList));
	// create 4 strings
	// first_string
    char *st_str = "I'm Ethan";
	// second_string    
    char *nd_str = "I'm from Thailand";
	// third_string    
    char *rd_str = "I'm Thai";
	// fourth_string
	char *th_str = "I'm Thai";    

	// print initial value of current and nitem of myList
    printf("The list before operations\n");
    printf("current is %s\n", DLListCurrent(myList));
    printf("nitem is %d\n",(int)DLListLength(myList));
    printList(myList);
    
    printf("Moving Current halfway (%d)\n",(int)(init_len/2));
	// move pointer curr to the middle of the list
    DLListMove(myList, (int)(init_len/2)); 
	// print the value of curr
    printf("Currrent is %s\n", DLListCurrent(myList));
    printf("Insert a string %s after curr\n", st_str);
	// Inserts first string in the list following current
    DLListAfter(myList, st_str);
	// check if the value of len is valid
    assert(DLListLength(myList) == init_len + 1);
	// check internal consistency
    assert(validDLList(myList));
	// print list
    printList(myList);

	// print the present value of current
    printf("Current is now == %s\n", DLListCurrent(myList));
    printf("Moving current forward 1 node\n");
	// move forward 1 node 
    DLListMove(myList,1); 
    printf("Doing 2 insertions\n");
	// insert second_string after current
    DLListAfter(myList, nd_str);
	// print the value of current
    printf("current is now %s\n", DLListCurrent(myList));
	// check if the length is valid
    assert(DLListLength(myList) == init_len+2);
	// insert third_string after current
    DLListAfter(myList, rd_str);
	// print the value of current
    printf("current is now %s\n", DLListCurrent(myList));
	// check if the length is valid
    assert(DLListLength(myList) == init_len+3);
	// insert fourth_string after current
    DLListAfter(myList, th_str);
	// print the value of current
    printf("Current is now %s\n", DLListCurrent(myList));
	// check if the value of length is valid
    assert(DLListLength(myList) == init_len+4);
	// print myList
    printList(myList);
	// compare value at current to third_string
    assert(strcmp(DLListCurrent(myList), rd_str) == 0);

    printf("Move pointer to the first node and insert %s at the beginning\n", st_str);
	// move pointer to the first node
    DLListMoveTo(myList, 1);
	// insert first_string before the first node 
    DLListBefore(myList, st_str);
	// check if the value of length is valid
    assert(DLListLength(myList) == init_len+5);
	// comparing the value at courrent with second_string
    assert(strcmp(DLListCurrent(myList), nd_str) == 0);
	// print the value of current
    printf("current is now %s\n", DLListCurrent(myList));
	// check internal consistency
    assert(validDLList(myList));
	// print list
    printList(myList);

    printf("Moving Current halfway (%d)\n",(int)(DLListLength(myList)/2));
	// move pointer current to the middle of the list
    DLListMove(myList,(int)(DLListLength(myList)/2));
    printf("Inserting before and after current\n");
	// inserting before current
    DLListBefore(myList, "bruhhhhhhhhh");
	// move 1 forward
    DLListMove(myList,1);
	// inserting after current
    DLListAfter(myList, "I'm quite tired now");
	// move 2 backwards
    DLListMove(myList,-2);
	// comparing the value at current to 
    assert(strcmp(DLListCurrent(myList),"I'm quite tired now")==0);
    // print list
	printList(myList);
	// print the value of nitem
    printf("ntem is %d\n", (int) DLListLength(myList));
	// check internal consistency of the list
    assert(validDLList(myList));
    printf("\nTest 1 Completed\n");
}

// Testing delete
void test_2 (DLList myList) {
    
    printf("Starting test 2\n");
	// print list
    printList(myList);
	//chek internal consistency
    assert(validDLList(myList));
	// print the value of current
    printf("Current is %s\n", DLListCurrent(myList)); 
	printf("nitems is %d\n", (int)DLListLength(myList));

    //Delete last and then first until the list is empty;
    //And print the list at the end of every loop
    while((int)DLListLength(myList)!=0) {
        assert(!DLListIsEmpty(myList));
        DLListMoveTo(myList,(int)DLListLength(myList));
        DLListDelete(myList);
        assert(validDLList(myList));
        DLListMoveTo(myList,1);
        DLListDelete(myList);
        assert(validDLList(myList));
        printList(myList);
    }
    assert(validDLList(myList));
    assert(DLListIsEmpty(myList));
    printf("\nTest 2 Completed\n");
}

// Prints entire List in a certain format
void printList (DLList myList) {
    printf("\n------\n");
    putDLList (stdout, myList);
    printf("------\n\n");
}

