// testList.c - testing DLList data type
// Written by John Shepherd, March 2013

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "DLList.h"

int main(void)
{
	// get list from stdin
	DLList myList = getDLList(stdin);
	// print Sanity Test
	fprintf(stdout, "\nSanity Test\n");
	// Display a DLList to file, one item per line
	putDLList(stdout, myList);
	// check internal consistency
	assert(validDLList(myList));

	// TODO: more tests needed here
	fprintf(stdout, "\nTest 1: Insert before First\n");
	// print current and lenth of the list
	fprintf(stdout, "before: curr = '%s', nitems = %zu\n",
			DLListCurrent(myList), DLListLength(myList));
	// insert test line 1 before currrent
	DLListBefore(myList, "Test Line 1");
	// Display a DLList to file, one item per line
	putDLList(stdout, myList);
	// print current and lenth of the list
	fprintf(stdout, "after: curr = '%s', nitems = %zu\n",
			DLListCurrent(myList), DLListLength(myList));
	// check internal consistency
	assert(validDLList(myList));

	fprintf(stdout, "\nTest 2: Insert before Last\n");
	// print current and lenth of the list
	fprintf(stdout, "before: curr = '%s', nitems = %zu\n",
			DLListCurrent(myList), DLListLength(myList));
	// move to last
	DLListMoveTo(myList, (int)DLListLength(myList));
	// insert test line 2 before currrent
	DLListBefore(myList, "Test Line 2");
	// Display a DLList to file, one item per line
	putDLList(stdout, myList);
	// print current and lenth of the list
	fprintf(stdout, "after: curr = '%s', nitems = %zu\n",
			DLListCurrent(myList), DLListLength(myList));
	// check internal consistency
	assert(validDLList(myList));

	fprintf(stdout, "\nTest 3: Insert after First\n");
	// print current and lenth of the list
	fprintf(stdout, "before: curr = '%s', nitems = %zu\n",
			DLListCurrent(myList), DLListLength(myList));
	// move to first
	DLListMoveTo(myList, 1);
	// insert test Line 3
	DLListAfter(myList, "Test Line 3");
	// print list line by line
	putDLList(stdout, myList);
	// print current and lenth of the list
	fprintf(stdout, "after: curr = '%s', nitems = %zu\n",
			DLListCurrent(myList), DLListLength(myList));
	// check internal consistency
	assert(validDLList(myList));

	fprintf(stdout, "\nTest 4: Insert after Last\n");
	// move to last
	DLListMoveTo(myList, (int)DLListLength(myList));
	// print current and lenth of the list
	fprintf(stdout, "before: curr = '%s', nitems = %zu\n",
			DLListCurrent(myList), DLListLength(myList));
	// insert Test Line 4 after current
	DLListAfter(myList, "Test Line 4");
	// print list to stdout
	putDLList(stdout, myList);
	// print current and lenth of the list
	fprintf(stdout, "after: curr = '%s', nitems = %zu\n",
			DLListCurrent(myList), DLListLength(myList));
	// check internal consistency
	assert(validDLList(myList));

	fprintf(stdout, "\nTest 5: Delete somewhere in Middle\n");
	// move curr pointer to line 3
	DLListMoveTo(myList, 3);
	// print current and lenth of the list
	fprintf(stdout, "before: curr = '%s', nitems = %zu\n",
			DLListCurrent(myList), DLListLength(myList));
	// delete curr node 
	DLListDelete(myList);
	// print list to stdout
	putDLList(stdout, myList);
	// print current and lenth of the list
	fprintf(stdout, "after: curr = '%s', nitems = %zu\n",
			DLListCurrent(myList), DLListLength(myList));
	// check internal consistency
	assert(validDLList(myList));

	fprintf(stdout, "\nTest 6: Delete Last\n");
	// move curr to last
	DLListMoveTo(myList, (int)DLListLength(myList));
	// print current and lenth of the list
	fprintf(stdout, "before: curr = '%s', nitems = %zu\n",
			DLListCurrent(myList), DLListLength(myList));
	// delete curr node
	DLListDelete(myList);
	// print list to stdout
	putDLList(stdout, myList);
	// print current and lenth of the list
	fprintf(stdout, "after: curr = '%s', nitems = %zu\n",
			DLListCurrent(myList), DLListLength(myList));
	// check internal consistency
	assert(validDLList(myList));

	fprintf(stdout, "\nTest 7: Delete First\n");
	// move curr pointer to first
	DLListMoveTo(myList, 1);
	// print current and lenth of the list
	fprintf(stdout, "before: curr = '%s', nitems = %zu\n",
			DLListCurrent(myList), DLListLength(myList));
	// delete curr node 
	DLListDelete(myList);
	// print list to stdout
	putDLList(stdout, myList);
	// print current and lenth of the list
	fprintf(stdout, "after: curr = '%s', nitems = %zu\n",
			DLListCurrent(myList), DLListLength(myList));
	// check internal consistency
	assert(validDLList(myList));

	printf("\n----------\n");
	printf("\ndelete items until only one remaining\n");
	printf("\n----------\n");
	//delete items until only one remaining
	while (DLListLength(myList) != 1)
		DLListDelete(myList);

	fprintf(stdout, "\nTest 8: Delete w/ 1 item on list\n");
	// move curr pointer to first node 
	DLListMoveTo(myList, 1);
	// print current and lenth of the list
	fprintf(stdout, "before: curr = '%s', nitems = %zu\n",
			DLListCurrent(myList), DLListLength(myList));
	// delete curr node
	DLListDelete(myList);
	// print list stdout
	putDLList(stdout, myList);
	// print current and lenth of the list
	fprintf(stdout, "after: curr = '%s', nitems = %zu\n",
			DLListCurrent(myList), DLListLength(myList));
	// check internal consistency
	assert(validDLList(myList));

	fprintf(stdout, "\nTest 9: Delete w/ empty list\n");
	// print current and lenth of the list
	fprintf(stdout, "before: curr = '%s', nitems = %zu\n",
			DLListCurrent(myList), DLListLength(myList));
	// delete curr node 
	DLListDelete(myList); //LeakSanitizer: detected memory leaks
	// print list stdout
	putDLList(stdout, myList);
	// print current and lenth of the list
	fprintf(stdout, "after: curr = '%s', nitems = %zu\n",
			DLListCurrent(myList), DLListLength(myList));
	// check internal consistency
	assert(validDLList(myList));

	fprintf(stdout, "\nTest 10: Insert before w/ empty list\n");
	// print current and lenth of the list
	fprintf(stdout, "before: curr = '%s', nitems = %zu\n",
			DLListCurrent(myList), DLListLength(myList));
	// insert Test line ten before curr node 
	DLListBefore(myList, "Test line 10");
	// print list out stdout
	putDLList(stdout, myList);
	// print current and lenth of the list
	fprintf(stdout, "after: curr = '%s', nitems = %zu\n",
			DLListCurrent(myList), DLListLength(myList));
	// check internal consistency
	assert(validDLList(myList));

	printf("\n----------\n");
	printf("\ndelete items until only 0 item remaining\n");
	printf("\n----------\n");
	//delete items until empty
	while (DLListLength(myList) != 0)
		DLListDelete(myList);

	fprintf(stdout, "\nTest 11: Insert after w/ empty list\n");
	// print current and lenth of the list
	fprintf(stdout, "before: curr = '%s', nitems = %zu\n",
			DLListCurrent(myList), DLListLength(myList));
	// insert Test line 11 after curr pointer
	DLListAfter(myList, "Test line 11");
	// pirnt list out stdout
	putDLList(stdout, myList);
	// print current and lenth of the list
	fprintf(stdout, "after: curr = '%s', nitems = %zu\n",
			DLListCurrent(myList), DLListLength(myList));
	// check internal consistency
	assert(validDLList(myList));

	freeDLList(myList);
	return EXIT_SUCCESS;
}
