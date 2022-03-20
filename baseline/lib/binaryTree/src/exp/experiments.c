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
#include <stdlib.h>
#include <time.h>

#include "binaryTree.h"
#include "binaryTreeGen.h"
#include "exp.h"
#include "types.h"
#include "util.h"


/******************************************************************************* 
------------------------------- HELPER FUNCTIONS -------------------------------
*******************************************************************************/

TimeInfo timeTraversal(Tree *root, TraversalFunc traversalFunc, int samples)
{
	TimeInfo timeInfo = {0};

	int i;
	clock_t tic, toc;

	tic = clock();
	for (i=0; i<samples; i++)
	{
		traversalFunc(root);
	}
	toc = clock();

	timeInfo.samples 	= samples;
	timeInfo.cycles		= toc - tic;
	timeInfo.seconds	= (double) (toc - tic) / CLOCKS_PER_SEC;

	return timeInfo;
}

TimeInfo timeTraversalCB(Tree *root, TraversalFuncCB traversalFunc, TreeCallback callback, int samples)
{
	TimeInfo timeInfo = {0};

	int i;
	clock_t tic, toc;

	tic = clock();
	for (i=0; i<samples; i++)
	{
		traversalFunc(root, callback);
	}
	toc = clock();

	timeInfo.samples 	= samples;
	timeInfo.cycles		= toc - tic;
	timeInfo.seconds	= (double) (toc - tic) / CLOCKS_PER_SEC;

	return timeInfo;
}

void timingSample(int N, int samples)
{
	int *invTable;
	Tree *btNodeArray;
	ITNode *itNodeArray;

	N = 1<<10;
	invTable = (int *) malloc(N * sizeof(int));
	btNodeArray = (Tree *) malloc(N * sizeof(Tree));
	itNodeArray = (ITNode *) malloc(N * sizeof(ITNode)); 

	TreeInfo treeInfo, treeInfoCont; 
	TimeInfo timeInfo, timeInfoCont;
	
	TraversalFunc inOrderTraversal = &inOrder;


	treeInfo = genRandomTreeOptimized(invTable, itNodeArray, N, false);
	treeInfoCont = genContRandomTreeOptimized(invTable, btNodeArray, itNodeArray, N, false);

	timeInfo = 	timeTraversal(treeInfo.root, inOrderTraversal, samples);
	timeInfoCont = 	timeTraversal(treeInfoCont.root, inOrderTraversal, samples);
	fprintf(
		stderr, "N = %d , Depth = %d, Leaves = %d , Density = %.3f , Traversal = %s , Samples = %d , Cycles = %ld , Seconds = %f\n",
		treeInfo.size, treeInfo.depth, treeInfo.leaves, treeInfo.density, "In-Order", timeInfo.samples, timeInfo.cycles, timeInfo.seconds 
	);
	fprintf(
		stderr, "N = %d , Depth = %d, Leaves = %d , Density = %.3f , Traversal = %s , Samples = %d , Cycles = %ld , Seconds = %f\n",
		treeInfoCont.size, treeInfoCont.depth, treeInfoCont.leaves, treeInfoCont.density, "In-Order", timeInfoCont.samples, timeInfoCont.cycles, timeInfoCont.seconds 
	);

	free(invTable);
	make_empty(treeInfo.root);
	free(btNodeArray);
	free(itNodeArray);
}


/******************************************************************************* 
------------------------------------- MAIN -------------------------------------
*******************************************************************************/
int main(int argc, char *argv[])
{
	/* ---------------------------------------------------------------------- */

	printf("\n");
	printf("###############################################################################\n");
	printf("########################### Binary Tree Experiments ###########################\n");
	printf("###############################################################################\n");
	printf("\n");

	init_genrand64(time(0));

	/* ---------------------------------------------------------------------- */

	timingSample(1<<10, 1<<10);

	/* ---------------------------------------------------------------------- */
	
	printf("\n");
	printf("###############################################################################\n");
	printf("############################# End of Experiments ##############################\n");
	printf("###############################################################################\n");
	printf("\n");
	
	/* ---------------------------------------------------------------------- */

	return (0);
}


/******************************************************************************* 
--------------------------------- END OF FILE ----------------------------------
*******************************************************************************/