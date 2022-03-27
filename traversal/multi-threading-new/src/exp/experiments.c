/******************************************************************************* 
------------------------------------- INFO -------------------------------------
*******************************************************************************/
/**
 * @file experiments.c
 * @author Mitchell Young (mgyoung@ncsu.edu)
 * @brief Runs experiments on binary trees.
 * @version 0.1
 * @date 2022-03-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */


/******************************************************************************* 
------------------------------- IMPORTS & PARAMS -------------------------------
*******************************************************************************/
#include <stdbool.h>
#include <stdio.h>

#include "binaryTree.h"
#include "util.h"

#include "batches.h"



/******************************************************************************* 
------------------------------------- MAIN -------------------------------------
*******************************************************************************/
int main(int argc, char *argv[])
{
	/* ---------------------------------------------------------------------- */

	// printf("\n");
	// printf("###############################################################################\n");
	// printf("########################### Binary Tree Experiments ###########################\n");
	// printf("###############################################################################\n");
	// printf("\n");

	init_genrand64(time(0));

	TreeCallback incrementCallback = &incrementID;
	TreeCallback printCallback = &printNodeStdErr;
	TreeCallback searchCallback = &searchKey;
	TreeCallback sleepCallback = &sleepNode;

	bool printResults = true;
	bool verbose = false;

	/* ---------------------------------------------------------------------- */
	int depth, i, runs;

	int minDepth = 18;
	int maxDepth = 18;
	int samples = 1;

	for (depth = minDepth; depth<=maxDepth; depth++)
	{
		for (i=0; i<samples; i++)
		{
			// if (depth <=10) 		{runs = 1000;}
			// else if (depth <=15)	{runs = 100;}
			// else if (depth <=20)	{runs = 10;}
			// else 					{runs = 1;}
			runs = 1;

			// traversalBatch(depth, runs, printResults, verbose);

			traversalBatchCB(depth, runs, incrementCallback, "increment-id", printResults, verbose);

			traversalBatchCB(depth, runs, searchCallback, "search-id", printResults, verbose);

			traversalBatchCB(depth, runs, printCallback, "print-id", printResults, verbose);

			// traversalBatchCB(depth, runs, sleepCallback, "sleep-10ms", printResults, verbose);
		}
	}

	/* ---------------------------------------------------------------------- */
	
	// printf("\n");
	// printf("###############################################################################\n");
	// printf("############################# End of Experiments ##############################\n");
	// printf("###############################################################################\n");
	// printf("\n");
	
	/* ---------------------------------------------------------------------- */

	return (0);
}


/******************************************************************************* 
--------------------------------- END OF FILE ----------------------------------
*******************************************************************************/