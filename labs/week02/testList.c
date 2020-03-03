// testList.c - testing DLList data type
// Written by John Shepherd, March 2013

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "DLList.h"

int main (void)
{
	// get list from stdin
	DLList myList = getDLList (stdin);
	// print Sanity Test
	fprintf(stdout, "\nSanity Test\n");
	// Display a DLList to file, one item per line
	putDLList (stdout, myList);
	// check internal consistency
	assert (validDLList (myList));

	// TODO: more tests needed here
	fprintf(stdout, "\nTest 1: Insert before First\n");
	// print current and lenth of the list
	fprintf(stdout, "Initially: curr = '%s', nitems = %zu\n", 
            DLListCurrent(myList), DLListLength(myList));
	// insert test line 1 before currrent 
    DLListBefore (myList, "Test Line 1");
	// Display a DLList to file, one item per line
    putDLList (stdout, myList);
	// check internal consistency
	assert (validDLList (myList));
	
    fprintf(stdout, "\nTest 2: Insert before Last\n");
	fprintf(stdout, "Initially: curr = '%s', nitems = %zu\n", 
            DLListCurrent(myList), DLListLength(myList));
	// move to current
    DLListMoveTo (myList, (int)DLListLength(myList));
	// insert test line 2 before currrent 
    DLListBefore (myList, "Test Line 2");
	// Display a DLList to file, one item per line
    putDLList (stdout, myList);
	// check internal consistency
	assert (validDLList (myList));
	
	fprintf(stdout, "\nTest 3: Insert after First\n");
	fprintf(stdout, "Initially: curr = '%s', nitems = %zu\n", 
            DLListCurrent(myList), DLListLength(myList));
    DLListMoveTo (myList, 1);
    DLListAfter (myList, "Test Line 3");
    putDLList (stdout, myList);
	assert (validDLList (myList));
	
	fprintf(stdout, "\nTest 4: Insert after Last\n");
	DLListMoveTo (myList, (int)DLListLength(myList));
	fprintf(stdout, "Initially: curr = '%s', nitems = %zu\n", 
            DLListCurrent(myList), DLListLength(myList));
    DLListAfter (myList, "Test Line 4");
    putDLList (stdout, myList);
	assert (validDLList (myList));
	
	fprintf(stdout, "\nTest 5: Delete somewhere in Middle\n");
	DLListMoveTo (myList, 3);
	fprintf(stdout, "Initially: curr = '%s', nitems = %zu\n", 
            DLListCurrent(myList), DLListLength(myList));
    DLListDelete (myList);
    putDLList (stdout, myList);
	assert (validDLList (myList));

    fprintf(stdout, "\nTest 6: Delete Last\n");
	DLListMoveTo (myList, (int)DLListLength(myList));
	fprintf(stdout, "Initially: curr = '%s', nitems = %zu\n", 
            DLListCurrent(myList), DLListLength(myList));
    DLListDelete (myList);
    putDLList (stdout, myList);
	assert (validDLList (myList));
	
	fprintf(stdout, "\nTest 7: Delete First\n");
	DLListMoveTo (myList, 1);
	fprintf(stdout, "Initially: curr = '%s', nitems = %zu\n", 
            DLListCurrent(myList), DLListLength(myList));
    DLListDelete (myList);
    putDLList (stdout, myList);
	assert (validDLList (myList));
	
	//delete items until only one remaining
	while (DLListLength(myList) != 1)
	   DLListDelete (myList); 
	
	fprintf(stdout, "\nTest 8: Delete w/ 1 item on list\n");
	DLListMoveTo (myList, 1);
	fprintf(stdout, "Initially: curr = '%s', nitems = %zu\n", 
            DLListCurrent(myList), DLListLength(myList));
    DLListDelete (myList);
    putDLList (stdout, myList);
	assert (validDLList (myList));
	
	fprintf(stdout, "\nTest 9: Delete w/ empty list\n");
	fprintf(stdout, "Initially: curr = '%s', nitems = %zu\n", 
            DLListCurrent(myList), DLListLength(myList));
    DLListDelete (myList); //LeakSanitizer: detected memory leaks
    putDLList (stdout, myList);
	assert (validDLList (myList));
	
	fprintf(stdout, "\nTest 10: Insert before w/ empty list\n");
	fprintf(stdout, "Initially: curr = '%s', nitems = %zu\n", 
            DLListCurrent(myList), DLListLength(myList));
    DLListBefore(myList, "Test line 10"); 
    putDLList (stdout, myList);
	assert (validDLList (myList));
	
	//delete items until empty
	while (DLListLength(myList) != 0) 
	   DLListDelete (myList); 
	
	fprintf(stdout, "\nTest 11: Insert after w/ empty list\n");
	fprintf(stdout, "Initially: curr = '%s', nitems = %zu\n", 
            DLListCurrent(myList), DLListLength(myList));
    DLListAfter(myList, "Test line 11"); 
    putDLList (stdout, myList);
	assert (validDLList (myList));
	
	freeDLList (myList);
	return EXIT_SUCCESS;
}



