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

#include "exp.h"
#include "timer.h"


/******************************************************************************* 
------------------------------- PRIMARY EXPORTS --------------------------------
*******************************************************************************/

/* -------------------------------------------------------------------------- */

void traversalBatch(int depth, int samples, bool printResults, bool verbose)
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
	
	TraversalFunc preOrderTraversal = &preOrder;
	TraversalFunc inOrderTraversal = &inOrder;
	TraversalFunc postOrderTraversal = &postOrder;
	TraversalFuncLevel levelOrderTraversal = &levelOrder;
	TraversalFuncCont contiguousOrderTraversal = &contiguousOrder;


	/* ---------------------------------------------------------------------- */
	/* ---------------------------- Random Tree ----------------------------- */
	/* ---------------------------------------------------------------------- */

	// treeInfo = genRandomTreeOptimized(invTable, itNodeArray, N, false);

	// timeTraversal(
	// 	treeInfo, preOrderTraversal, samples, printResults, verbose, 
	// 	"random", "fragmented", "pre-order", "NULL"
	// );
	// timeTraversal(
	// 	treeInfo, inOrderTraversal, samples, printResults, verbose, 
	// 	"random", "fragmented", "in-order", "NULL"
	// );
	// timeTraversal(
	// 	treeInfo, postOrderTraversal, samples, printResults, verbose, 
	// 	"random", "fragmented", "post-order", "NULL"
	// );
	// timeTraversalLevel(
	// 	treeInfo, treeQueue, levelOrderTraversal, samples, printResults, verbose, 
	// 	"random", "fragmented", "level-order", "NULL"
	// );

	// make_empty(treeInfo.root);

	/* ---------------------------------------------------------------------- */
	/* ----------------------- Contiguous Random Tree ----------------------- */
	/* ---------------------------------------------------------------------- */

	treeInfo = genContRandomTreeOptimized(invTable, btNodeArray, itNodeArray, N, false);

	timeTraversal(
		treeInfo, preOrderTraversal, samples, printResults, verbose, 
		"random", "contiguous", "pre-order", "NULL"
	);
	timeTraversal(
		treeInfo, inOrderTraversal, samples, printResults, verbose, 
		"random", "contiguous", "in-order", "NULL"
	);
	timeTraversal(
		treeInfo, postOrderTraversal, samples, printResults, verbose, 
		"random", "contiguous", "post-order", "NULL"
	);
	timeTraversalLevel(
		treeInfo, treeQueue, levelOrderTraversal, samples, printResults, verbose, 
		"random", "contiguous", "level-order", "NULL"
	);
	timeTraversalCont(
		treeInfo, btNodeArray, contiguousOrderTraversal, samples, printResults, verbose, 
		"random", "contiguous", "contiguous-order", "NULL"
	);

	/* ---------------------------------------------------------------------- */
	/* --------------------------- Balanced Tree ---------------------------- */
	/* ---------------------------------------------------------------------- */

	treeInfo = genBalancedTreeOptimized(invTable, itNodeArray, depth, false);

	timeTraversal(
		treeInfo, preOrderTraversal, samples, printResults, verbose, 
		"balanced", "fragmented", "pre-order", "NULL"
	);
	timeTraversal(
		treeInfo, inOrderTraversal, samples, printResults, verbose, 
		"balanced", "fragmented", "in-order", "NULL"
	);
	timeTraversal(
		treeInfo, postOrderTraversal, samples, printResults, verbose, 
		"balanced", "fragmented", "post-order", "NULL"
	);
	timeTraversalLevel(
		treeInfo, treeQueue, levelOrderTraversal, samples, printResults, verbose, 
		"balanced", "fragmented", "level-order", "NULL"
	);

	make_empty(treeInfo.root);

	/* ---------------------------------------------------------------------- */
	/* ---------------------- Contiguous Balanced Tree ---------------------- */
	/* ---------------------------------------------------------------------- */

	treeInfo = genContBalancedTreeOptimized(invTable, btNodeArray, itNodeArray, depth, false);

	timeTraversal(
		treeInfo, preOrderTraversal, samples, printResults, verbose, 
		"balanced", "contiguous", "pre-order", "NULL"
	);
	timeTraversal(
		treeInfo, inOrderTraversal, samples, printResults, verbose, 
		"balanced", "contiguous", "in-order", "NULL"
	);
	timeTraversal(
		treeInfo, postOrderTraversal, samples, printResults, verbose, 
		"balanced", "contiguous", "post-order", "NULL"
	);
	timeTraversalLevel(
		treeInfo, treeQueue, levelOrderTraversal, samples, printResults, verbose, 
		"balanced", "contiguous", "level-order", "NULL"
	);
	timeTraversalCont(
		treeInfo, btNodeArray, contiguousOrderTraversal, samples, printResults, verbose, 
		"balanced", "contiguous", "contiguous-order", "NULL"
	);

	/* ---------------------------------------------------------------------- */

	free(invTable);
	free(btNodeArray);
	free(itNodeArray);
}

/* -------------------------------------------------------------------------- */

void traversalBatchCB(
	int depth, int samples, TreeCallback callback, const char callbackName[], 
	bool printResults, bool verbose
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
	
	TraversalFuncCB preOrderTraversalCB = &preOrderCB;
	TraversalFuncCB inOrderTraversalCB = &inOrderCB;
	TraversalFuncCB postOrderTraversalCB = &postOrderCB;
	TraversalFuncLevelCB levelOrderTraversalCB = &levelOrderCB;
	TraversalFuncContCB contiguousOrderTraversalCB = &contiguousOrderCB;


	/* ---------------------------------------------------------------------- */
	/* --------------------- Random Tree with Callback ---------------------- */
	/* ---------------------------------------------------------------------- */

	// treeInfo = genRandomTreeOptimized(invTable, itNodeArray, N, false);

	// timeTraversalCB(
	// 	treeInfo, preOrderTraversalCB, callback, samples, printResults, verbose, 
	// 	"random", "fragmented", "pre-order", callbackName
	// );
	// timeTraversalCB(
	// 	treeInfo, inOrderTraversalCB, callback, samples, printResults, verbose, 
	// 	"random", "fragmented", "in-order", callbackName
	// );
	// timeTraversalCB(
	// 	treeInfo, postOrderTraversalCB, callback, samples, printResults, verbose, 
	// 	"random", "fragmented", "post-order", callbackName
	// );
	// timeTraversalLevelCB(
	// 	treeInfo, treeQueue, levelOrderTraversalCB, callback, samples, printResults, verbose, 
	// 	"random", "fragmented", "level-order", callbackName
	// );

	// make_empty(treeInfo.root);

	/* ---------------------------------------------------------------------- */
	/* ---------------- Contiguous Random Tree with Callback ---------------- */
	/* ---------------------------------------------------------------------- */

	treeInfo = genContRandomTreeOptimized(invTable, btNodeArray, itNodeArray, N, false);

	// timeTraversalCB(
	// 	treeInfo, preOrderTraversalCB, callback, samples, printResults, verbose, 
	// 	"random", "contiguous", "pre-order", callbackName
	// );
	// timeTraversalCB(
	// 	treeInfo, inOrderTraversalCB, callback, samples, printResults, verbose, 
	// 	"random", "contiguous", "in-order", callbackName
	// );
	timeTraversalCB(
		treeInfo, postOrderTraversalCB, callback, samples, printResults, verbose, 
		"random", "contiguous", "post-order", callbackName
	);
	// timeTraversalLevelCB(
	// 	treeInfo, treeQueue, levelOrderTraversalCB, callback, samples, printResults, verbose, 
	// 	"random", "contiguous", "level-order", callbackName
	// );
	// timeTraversalContCB(
	// 	treeInfo, btNodeArray, contiguousOrderTraversalCB, callback, samples, printResults, verbose, 
	// 	"random", "contiguous", "contiguous-order", callbackName
	// );

	// /* ---------------------------------------------------------------------- */
	// /* -------------------- Balanced Tree with Callback --------------------- */
	// /* ---------------------------------------------------------------------- */

	// treeInfo = genBalancedTreeOptimized(invTable, itNodeArray, depth, false);

	// timeTraversalCB(
	// 	treeInfo, preOrderTraversalCB, callback, samples, printResults, verbose, 
	// 	"balanced", "fragmented", "pre-order", callbackName
	// );
	// timeTraversalCB(
	// 	treeInfo, inOrderTraversalCB, callback, samples, printResults, verbose, 
	// 	"balanced", "fragmented", "in-order", callbackName
	// );
	// timeTraversalCB(
	// 	treeInfo, postOrderTraversalCB, callback, samples, printResults, verbose, 
	// 	"balanced", "fragmented", "post-order", callbackName
	// );
	// timeTraversalLevelCB(
	// 	treeInfo, treeQueue, levelOrderTraversalCB, callback, samples, printResults, verbose, 
	// 	"balanced", "fragmented", "level-order", callbackName
	// );

	// make_empty(treeInfo.root);

	// /* ---------------------------------------------------------------------- */
	// /* --------------- Contiguous Balanced Tree with Callback --------------- */
	// /* ---------------------------------------------------------------------- */

	// treeInfo = genContBalancedTreeOptimized(invTable, btNodeArray, itNodeArray, depth, false);

	// timeTraversalCB(
	// 	treeInfo, preOrderTraversalCB, callback, samples, printResults, verbose, 
	// 	"balanced", "contiguous", "pre-order", callbackName
	// );
	// timeTraversalCB(
	// 	treeInfo, inOrderTraversalCB, callback, samples, printResults, verbose, 
	// 	"balanced", "contiguous", "in-order", callbackName
	// );
	// timeTraversalCB(
	// 	treeInfo, postOrderTraversalCB, callback, samples, printResults, verbose, 
	// 	"balanced", "contiguous", "post-order", callbackName
	// );
	// timeTraversalLevelCB(
	// 	treeInfo, treeQueue, levelOrderTraversalCB, callback, samples, printResults, verbose, 
	// 	"balanced", "contiguous", "level-order", callbackName
	// );
	// timeTraversalContCB(
	// 	treeInfo, btNodeArray, contiguousOrderTraversalCB, callback, samples, printResults, verbose, 
	// 	"balanced", "contiguous", "contiguous-order", callbackName
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