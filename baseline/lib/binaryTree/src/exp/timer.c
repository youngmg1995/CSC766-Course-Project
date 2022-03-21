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
#include <time.h>

#include "types.h"
#include "queue.h"

#include "exp.h"


/******************************************************************************* 
------------------------------- HELPER FUNCTIONS -------------------------------
*******************************************************************************/
void printExpResults(
	TreeInfo treeInfo, TimeInfo timeInfo, const char treeType[], 
	const char storageType[], const char traversalType[], const char callbackName[], 
	bool verbose
)
{
	if (verbose)
	{
		fprintf(
			stderr, "TreeType = %s , StorageType = %s , TraversalType = %s , Callback = %s , N = %d , Depth = %d, Leaves = %d , Density = %.3f , Samples = %d , Cycles = %ld , Seconds = %f, AvgCycles = %f , AvgSeconds = %f\n",
			treeType, storageType, traversalType, callbackName, treeInfo.size, treeInfo.depth, treeInfo.leaves, treeInfo.density, timeInfo.samples, timeInfo.cycles, timeInfo.seconds, timeInfo.avgCycles, timeInfo.avgSeconds 
		);
	}
	else
	{
		fprintf(
			stderr, "%s,%s,%s,%s,%d,%d,%d,%f,%d,%ld,%f,%f,%f\n",
			treeType, storageType, traversalType, callbackName, treeInfo.size, treeInfo.depth, treeInfo.leaves, treeInfo.density, timeInfo.samples, timeInfo.cycles, timeInfo.seconds, timeInfo.avgCycles, timeInfo.avgSeconds 
		);
	}
}

// void mem_flush(const void *p, unsigned int allocation_size){
//     const size_t cache_line = 64;
//     const char *cp = (const char *)p;
//     size_t i = 0;

//     if (p == NULL || allocation_size <= 0)
// 		return;

//     for (i = 0; i < allocation_size; i += cache_line) 
// 	{
// 		asm volatile("clflush (%0)\n\t"
// 						: 
// 						: "r"(&cp[i])
// 						: "memory");
//     }

//     asm volatile("sfence\n\t"
//                  :
//                  :
//                  : "memory");
// }

// void clearCache()
// {
// 	long N = 1<<40;
// 	char *lotsofmem = (char *) malloc(N * sizeof(char));
// 	int i;
// 	for (i=0; i<N; i++)
// 	{
// 		lotsofmem[i] = 0;
// 	}
// 	free(lotsofmem);
// }


/******************************************************************************* 
------------------------------- PRIMARY EXPORTS --------------------------------
*******************************************************************************/

/* -------------------------------------------------------------------------- */

TimeInfo timeTraversal(
	TreeInfo treeInfo, TraversalFunc traversalFunc, int samples, 
	bool printResults, bool verbose, const char treeType[], const char storageType[],
	const char traversalName[], const char callbackName[]
)
{
	TimeInfo timeInfo = {0};

	int i;
	clock_t tic, toc;

	// mem_flush(treeInfo.root, treeInfo.size * sizeof(Tree));

	tic = clock();
	for (i=0; i<samples; i++)
	{
		traversalFunc(treeInfo.root);
	}
	toc = clock();

	timeInfo.samples 	= samples;
	timeInfo.cycles		= toc - tic;
	timeInfo.seconds	= (double) (toc - tic) / CLOCKS_PER_SEC;
	timeInfo.avgCycles	= (double) timeInfo.cycles / timeInfo.samples;
	timeInfo.avgSeconds	= timeInfo.seconds / timeInfo.samples;

	if (printResults)
	{
		printExpResults(
			treeInfo, timeInfo, treeType, storageType, traversalName, 
			callbackName, verbose
		);
	}

	return timeInfo;
}

/* -------------------------------------------------------------------------- */

TimeInfo timeTraversalCB(
	TreeInfo treeInfo, TraversalFuncCB traversalFunc, TreeCallback callback, int samples, 
	bool printResults, bool verbose, const char treeType[], const char storageType[],
	const char traversalName[], const char callbackName[]
)
{
	TimeInfo timeInfo = {0};

	int i;
	clock_t tic, toc;

	tic = clock();
	for (i=0; i<samples; i++)
	{
		traversalFunc(treeInfo.root, callback);
	}
	toc = clock();

	timeInfo.samples 	= samples;
	timeInfo.cycles		= toc - tic;
	timeInfo.seconds	= (double) (toc - tic) / CLOCKS_PER_SEC;
	timeInfo.avgCycles	= (double) timeInfo.cycles / timeInfo.samples;
	timeInfo.avgSeconds	= timeInfo.seconds / timeInfo.samples;

	if (printResults)
	{
		printExpResults(
			treeInfo, timeInfo, treeType, storageType, traversalName, 
			callbackName, verbose
		);
	}

	return timeInfo;
}

TimeInfo timeTraversalLevel(
	TreeInfo treeInfo, TreeQueue *treeQueue, TraversalFuncLevel traversalFunc, int samples,
	bool printResults, bool verbose, const char treeType[], const char storageType[],
	const char traversalName[], const char callbackName[]
)
{
	TimeInfo timeInfo = {0};

	resetTQ(treeQueue);

	int i;
	clock_t tic, toc;

	tic = clock();
	for (i=0; i<samples; i++)
	{
		traversalFunc(treeInfo.root, treeQueue);
	}
	toc = clock();

	timeInfo.samples 	= samples;
	timeInfo.cycles		= toc - tic;
	timeInfo.seconds	= (double) (toc - tic) / CLOCKS_PER_SEC;
	timeInfo.avgCycles	= (double) timeInfo.cycles / timeInfo.samples;
	timeInfo.avgSeconds	= timeInfo.seconds / timeInfo.samples;

	if (printResults)
	{
		printExpResults(
			treeInfo, timeInfo, treeType, storageType, traversalName, 
			callbackName, verbose
		);
	}

	return timeInfo;
}

/* -------------------------------------------------------------------------- */

TimeInfo timeTraversalLevelCB(
	TreeInfo treeInfo, TreeQueue *treeQueue, TraversalFuncLevelCB traversalFunc, TreeCallback callback, int samples, 
	bool printResults, bool verbose, const char treeType[], const char storageType[],
	const char traversalName[], const char callbackName[]
)
{
	TimeInfo timeInfo = {0};

	resetTQ(treeQueue);

	int i;
	clock_t tic, toc;

	tic = clock();
	for (i=0; i<samples; i++)
	{
		traversalFunc(treeInfo.root, treeQueue, callback);
	}
	toc = clock();

	timeInfo.samples 	= samples;
	timeInfo.cycles		= toc - tic;
	timeInfo.seconds	= (double) (toc - tic) / CLOCKS_PER_SEC;
	timeInfo.avgCycles	= (double) timeInfo.cycles / timeInfo.samples;
	timeInfo.avgSeconds	= timeInfo.seconds / timeInfo.samples;

	if (printResults)
	{
		printExpResults(
			treeInfo, timeInfo, treeType, storageType, traversalName, 
			callbackName, verbose
		);
	}

	return timeInfo;
}

/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */

TimeInfo timeTraversalCont(
	TreeInfo treeInfo, Tree *btNodeArray, TraversalFuncCont traversalFunc, int samples, 
	bool printResults, bool verbose, const char treeType[], const char storageType[],
	const char traversalName[], const char callbackName[]
)
{
	TimeInfo timeInfo = {0};

	int i;
	clock_t tic, toc;

	tic = clock();
	for (i=0; i<samples; i++)
	{
		traversalFunc(btNodeArray, treeInfo.size);
	}
	toc = clock();

	timeInfo.samples 	= samples;
	timeInfo.cycles		= toc - tic;
	timeInfo.seconds	= (double) (toc - tic) / CLOCKS_PER_SEC;
	timeInfo.avgCycles	= (double) timeInfo.cycles / timeInfo.samples;
	timeInfo.avgSeconds	= timeInfo.seconds / timeInfo.samples;

	if (printResults)
	{
		printExpResults(
			treeInfo, timeInfo, treeType, storageType, traversalName, 
			callbackName, verbose
		);
	}

	return timeInfo;
}

/* -------------------------------------------------------------------------- */

TimeInfo timeTraversalContCB(
	TreeInfo treeInfo,  Tree *btNodeArray, TraversalFuncContCB traversalFunc, TreeCallback callback, int samples, 
	bool printResults, bool verbose, const char treeType[], const char storageType[],
	const char traversalName[], const char callbackName[]
)
{
	TimeInfo timeInfo = {0};

	int i;
	clock_t tic, toc;

	tic = clock();
	for (i=0; i<samples; i++)
	{
		traversalFunc(btNodeArray, treeInfo.size, callback);
	}
	toc = clock();

	timeInfo.samples 	= samples;
	timeInfo.cycles		= toc - tic;
	timeInfo.seconds	= (double) (toc - tic) / CLOCKS_PER_SEC;
	timeInfo.avgCycles	= (double) timeInfo.cycles / timeInfo.samples;
	timeInfo.avgSeconds	= timeInfo.seconds / timeInfo.samples;

	if (printResults)
	{
		printExpResults(
			treeInfo, timeInfo, treeType, storageType, traversalName, 
			callbackName, verbose
		);
	}

	return timeInfo;
}

/* -------------------------------------------------------------------------- */

/******************************************************************************* 
--------------------------------- END OF FILE ----------------------------------
*******************************************************************************/