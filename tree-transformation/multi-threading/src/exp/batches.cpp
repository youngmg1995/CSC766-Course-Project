/******************************************************************************* 
------------------------------------- INFO -------------------------------------
*******************************************************************************/
/**
 * @file batches.cpp
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
#include <iostream>
#include <unordered_map>

#include "types.h"
#include "splayTree.h"
#include "treeLoader.h"
#include "treeConversion.h"
#include "threadpool.h"

#include "exp.h"
#include "timer.h"


/******************************************************************************* 
------------------------------- PRIMARY EXPORTS --------------------------------
*******************************************************************************/

/* --------------------------- Forward Direction ---------------------------- */

void traversalBatch(
	const char tree_input_file[], const char treeType[], 
	int buTreeSize, int tdTreeSize,
	bool printResults, bool verbose
)
{
	int i;

    node *splayArray = NULL;
    node *original = NULL;
	node *buRoot = NULL;

    loadCompressedJSON(tree_input_file, &splayArray, &original);


// /* ---------------------------- Plain Traversal ----------------------------- */
// 	timeTraversal(original, true, false, treeType, "td-2-bu");
// /* -------------------------------------------------------------------------- */


/* ----------------------- Transform With Mem. Alloc. ----------------------- */
	timeTransformMalloc(original, &buRoot, true, false, treeType, "td-2-bu-cont");
	free(buRoot);
/* -------------------------------------------------------------------------- */


	node *tmp;
	node *buNodeArray = (node *) malloc(buTreeSize * sizeof(node));


/* --------------------- Transform Without Mem. Alloc. ---------------------- */
	resetThreadLoads();
	for (i=0, tmp=buNodeArray; i<buTreeSize; i++, tmp++)
	{
		initNode(tmp);
	}
	timeTransformNoMalloc(original, buNodeArray, true, false, treeType, "td-2-bu-cont");
	printf("Thread Loads: ");
	for (i=0; i<NUM_THREADS+1; i++)
	{
		printf("%d ", threadLoads[i]);
	}
	printf("\n");
/* -------------------------------------------------------------------------- */


/* -------------- Transform Without Mem. Alloc. and No Locking -------------- */
	if (NUM_THREADS <= 1)
	{
		for (i=0, tmp=buNodeArray; i<buTreeSize; i++, tmp++)
		{
			initNode(tmp);
		}
		node *passedPointer = buNodeArray;
		timeTransformNoMalloc2(original, &passedPointer, true, false, treeType, "td-2-bu-cont");
		free(buNodeArray);
	}
	else
	{
		free(buNodeArray);
		node **buNodeArrays = (node **) malloc((NUM_THREADS+1) * sizeof(node *));
		node **passedPointer = (node **) malloc((NUM_THREADS+1) * sizeof(node *));
		int j;
		for (j=0; j<(NUM_THREADS+1); j++)
		{
			buNodeArrays[j] = (node *) malloc(threadLoads[j] * sizeof(node));
			passedPointer[j] = buNodeArrays[j];
			for (i=0, tmp=buNodeArrays[j]; i<threadLoads[j]; i++, tmp++)
			{
				initNode(tmp);
			}
		}
		timeTransformNoMalloc2(original, passedPointer, true, false, treeType, "td-2-bu-cont");
		for (j=0; j<(NUM_THREADS+1); j++) { free(buNodeArrays[j]); }
		free(buNodeArrays);
	}
/* -------------------------------------------------------------------------- */


// /* ------------------ Cont. Transform Without Mem. Alloc. ------------------- */
// 	for (i=0, tmp=buNodeArray; i<buTreeSize; i++, tmp++)
// 	{
// 		initNode(tmp);
// 	}
// 	timeTransformCont(splayArray, treeSize, buNodeArray, true, false, treeType, "td-2-bu-cont");
// /* -------------------------------------------------------------------------- */


	free(splayArray);
	// free(buNodeArray);
}

/* -------------------------------------------------------------------------- */




// /* --------------------------- Backwards Direction (Fragmented) ---------------------------- */

// void traversalBatch2(
// 	const char tree_input_file[], const char treeType[], 
// 	int buTreeSize, int tdTreeSize,
// 	bool printResults, bool verbose
// )
// {
// 	int i;

//     node *splayArray = NULL;
//     node *original = NULL;
// 	node *buRoot = NULL;
// 	node *tdRoot = NULL;

//     loadCompressedJSON(tree_input_file, &splayArray, &original);

// 	timeTransformMalloc(original, &buRoot, true, false, treeType, "td-2-bu-cont");
// 	free(splayArray);



// /* ---------------------------- Plain Traversal ----------------------------- */
// 	timeTraversal(buRoot, true, false, treeType, "bu-2-td-frag");
// /* -------------------------------------------------------------------------- */


// /* ----------------------- Transform With Mem. Alloc. ----------------------- */
// 	timeTransformMalloc(buRoot, &tdRoot, true, false, treeType, "bu-2-td-frag");
// 	free(tdRoot);
// /* -------------------------------------------------------------------------- */


// 	node *tmp;
// 	node *tdNodeArray = (node *) malloc(tdTreeSize * sizeof(node));


// /* --------------------- Transform Without Mem. Alloc. ---------------------- */
// 	for (i=0, tmp=tdNodeArray; i<tdTreeSize; i++, tmp++)
// 	{
// 		initNode(tmp);
// 	}
// 	timeTransformNoMalloc(buRoot, tdNodeArray, true, false, treeType, "bu-2-td-frag");
// /* -------------------------------------------------------------------------- */


// 	free(buRoot);
// 	free(tdNodeArray);
// }




// /* --------------------------- Backwards Direction (Contiguous) ---------------------------- */

// void traversalBatch3(
// 	const char tree_input_file[], const char treeType[], 
// 	int buTreeSize, int tdTreeSize,
// 	bool printResults, bool verbose
// )
// {
// 	int i;

//     node *splayArray = NULL;
//     node *original = NULL;

//     loadCompressedJSON(tree_input_file, &splayArray, &original);

// 	node *tmp;
// 	node *buNodeArray = (node *) malloc(buTreeSize * sizeof(node));
// 	for (i=0, tmp=buNodeArray; i<buTreeSize; i++, tmp++)
// 	{
// 		initNode(tmp);
// 	}
	
// 	timeTransformNoMalloc(original, buNodeArray, true, false, treeType, "bu-2-td-frag");
// 	free(splayArray);
// 	int treeSize = getTreeSize(buNodeArray);



// /* ---------------------------- Plain Traversal ----------------------------- */
// 	timeTraversal(buNodeArray, true, false, treeType, "bu-2-td-cont");
// /* -------------------------------------------------------------------------- */


// /* ----------------------- Transform With Mem. Alloc. ----------------------- */
// 	timeTransformMalloc(buNodeArray, &tmp, true, false, treeType, "bu-2-td-cont");
// 	free(tmp);
// /* -------------------------------------------------------------------------- */


// 	node *tdNodeArray = (node *) malloc(tdTreeSize * sizeof(node));


// /* --------------------- Transform Without Mem. Alloc. ---------------------- */
// 	for (i=0, tmp=tdNodeArray; i<tdTreeSize; i++, tmp++)
// 	{
// 		initNode(tmp);
// 	}
// 	timeTransformNoMalloc(buNodeArray, tdNodeArray, true, false, treeType, "bu-2-td-cont");
// /* -------------------------------------------------------------------------- */


// /* ------------------ Cont. Transform Without Mem. Alloc. ------------------- */
// 	for (i=0, tmp=tdNodeArray; i<tdTreeSize; i++, tmp++)
// 	{
// 		initNode(tmp);
// 	}
// 	timeTransformCont(buNodeArray, treeSize, tdNodeArray, true, false, treeType, "bu-2-td-cont");
// /* -------------------------------------------------------------------------- */


// 	free(buNodeArray);
// 	free(tdNodeArray);
// }

// /* -------------------------------------------------------------------------- */

/******************************************************************************* 
--------------------------------- END OF FILE ----------------------------------
*******************************************************************************/