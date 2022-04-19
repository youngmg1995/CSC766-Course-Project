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
#include <stdlib.h>

#include "binaryTree.h"
#include "binaryTreeGen.h"
#include "types.h"
#include "queue.h"
#include "threadpool.h"

#include "exp.h"
#include "timer.h"


/******************************************************************************* 
------------------------------- PRIMARY EXPORTS --------------------------------
*******************************************************************************/

/* -------------------------------------------------------------------------- */

void traversalBatchMT(
	int depth, int samples, TreeCallback callback, 
	ThreadPool *threadPool, StartThreadArgs *startArgs,
	const char callbackName[], bool printResults, bool verbose
)
{
	int N = (1<<(depth+1)) - 1;

	int *invTable;
	Tree *btNodeArray;
	ITNode *itNodeArray;
	TreeInfo treeInfo; 

	invTable = (int *) malloc(N * sizeof(int));
	btNodeArray = (Tree *) malloc(N * sizeof(Tree));
	itNodeArray = (ITNode *) malloc(N * sizeof(ITNode)); 

	TreeQueue tq = {0};
	TreeQueue *treeQueue = &tq;
	initTQ(treeQueue, N);
	
	TraversalFuncMTWrapper preOrderTraversalMT = &preOrderMTWrapper;
	TraversalFuncMTWrapper postOrderTraversalMT = &postOrderMTWrapper;


	// /* ---------------------------------------------------------------------- */
	// /* --------------------- Random Tree with Callback ---------------------- */
	// /* ---------------------------------------------------------------------- */

	// treeInfo = genRandomTreeOptimized(invTable, itNodeArray, N, false);

	// timeTraversalMT(
	// 	treeInfo, preOrderTraversalMT, callback, threadPool, startArgs,
	// 	samples, printResults, verbose,
	// 	"random", "fragmented", "pre-order", callbackName
	// );
	// timeTraversalMT(
	// 	treeInfo, postOrderTraversalMT, callback, threadPool, startArgs,
	// 	samples, printResults, verbose, 
	// 	"random", "fragmented", "post-order", callbackName
	// );

	// make_empty(treeInfo.root);

	/* ---------------------------------------------------------------------- */
	/* ---------------- Contiguous Random Tree with Callback ---------------- */
	/* ---------------------------------------------------------------------- */

	treeInfo = genContRandomTreeOptimized(invTable, btNodeArray, itNodeArray, N, false);

	// timeTraversalMT(
	// 	treeInfo, preOrderTraversalMT, callback, threadPool, startArgs,
	// 	samples, printResults, verbose, 
	// 	"random", "contiguous", "pre-order", callbackName
	// );
	timeTraversalMT(
		treeInfo, postOrderTraversalMT, callback, threadPool, startArgs,
		samples, printResults, verbose, 
		"random", "contiguous", "post-order", callbackName
	);

	// /* ---------------------------------------------------------------------- */
	// /* -------------------- Balanced Tree with Callback --------------------- */
	// /* ---------------------------------------------------------------------- */

	// treeInfo = genBalancedTreeOptimized(invTable, itNodeArray, depth, false);

	// timeTraversalMT(
	// 	treeInfo, preOrderTraversalMT, callback, threadPool, startArgs,
	// 	samples, printResults, verbose, 
	// 	"balanced", "fragmented", "pre-order", callbackName
	// );
	// timeTraversalMT(
	// 	treeInfo, postOrderTraversalMT, callback, threadPool, startArgs,
	// 	samples, printResults, verbose, 
	// 	"balanced", "fragmented", "post-order", callbackName
	// );

	// make_empty(treeInfo.root);

	// /* ---------------------------------------------------------------------- */
	// /* --------------- Contiguous Balanced Tree with Callback --------------- */
	// /* ---------------------------------------------------------------------- */

	// treeInfo = genContBalancedTreeOptimized(invTable, btNodeArray, itNodeArray, depth, false);

	// timeTraversalMT(
	// 	treeInfo, preOrderTraversalMT, callback, threadPool, startArgs,
	// 	samples, printResults, verbose, 
	// 	"balanced", "contiguous", "pre-order", callbackName
	// );
	// timeTraversalMT(
	// 	treeInfo, postOrderTraversalMT, callback, threadPool, startArgs,
	// 	samples, printResults, verbose, 
	// 	"balanced", "contiguous", "post-order", callbackName
	// );

	// /* ---------------------------------------------------------------------- */

	free(invTable);
	free(btNodeArray);
	free(itNodeArray);
}

/* -------------------------------------------------------------------------- */

/******************************************************************************* 
--------------------------------- END OF FILE ----------------------------------
*******************************************************************************/