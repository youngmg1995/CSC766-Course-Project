/******************************************************************************* 
------------------------------------- INFO -------------------------------------
*******************************************************************************/
/**
 * @file tests.cpp
 * @author Mitchell Young (mgyoung@ncsu.edu)
 * @brief Runs unit tests for generating binary trees.
 * @version 0.1
 * @date 2022-03-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */


/******************************************************************************* 
------------------------------- IMPORTS & PARAMS -------------------------------
*******************************************************************************/
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "types.h"
#include "splayTree.h"
#include "treeLoader.h"
#include "treeConversion.h"
#include "util.h"


/******************************************************************************* 
------------------------------- HELPER FUNCTIONS -------------------------------
*******************************************************************************/
void printUnitTestMsg(int *testNum, const char message[])
{
	const char delimiter[] = "================================================================================";
	int n = strlen(delimiter);
	int m = strlen(message);

	int p = (n-m-8)/2;
	p = p <= 0 ? 0 : p;
	int q = p <= 0 ? 0 : n - m - p - 8;

	char *spacer1 = (char *) malloc((p+1) *sizeof(char));
	int i;
	for (i=0; i<p; i++)
	{
		spacer1[i] = ' ';
	}
	spacer1[p] = '\0';

	char *spacer2 = (char *) malloc((q+1) *sizeof(char));
	for (i=0; i<q; i++)
	{
		spacer2[i] = ' ';
	}
	spacer2[q] = '\0';


	printf("\n");
	printf("%s\n", delimiter);
	printf("%s\n", delimiter);
	printf("%sTest %d: %s%s\n", spacer1, *testNum, message, spacer2);
	printf("%s\n", delimiter);
	printf("%s\n", delimiter);
	printf("\n");

	free(spacer1);
	free(spacer2);

	(*testNum)++;
}



/******************************************************************************* 
------------------------------------- MAIN -------------------------------------
*******************************************************************************/
int main(int argc, char *argv[])
{
	/* ---------------------------------------------------------------------- */
	printf("\n");
	printf("###############################################################################\n");
	printf("####################### Tree Transformation Unit Tests ########################\n");
	printf("###############################################################################\n");
	printf("\n");

	int testNum = 1;

	/* ---------------------------------------------------------------------- */
	
	// printUnitTestMsg(&testNum, "Validate Splay Tree");
	// splayTreeUnitTest();

	/* ---------------------------------------------------------------------- */
	
	// printUnitTestMsg(&testNum, "Validate Tree Loader");
	// treeLoaderUnitTest(tiny_tree_file);

	/* ---------------------------------------------------------------------- */
	
	printUnitTestMsg(&testNum, "Validate Tree Conversion");
	treeConvUnitTest(small_tree_file_compressed);

	/* ---------------------------------------------------------------------- */

	return (0);
}


/******************************************************************************* 
--------------------------------- END OF FILE ----------------------------------
*******************************************************************************/