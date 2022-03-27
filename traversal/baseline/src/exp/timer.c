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
#include <sys/time.h>

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
			stdout, "TreeType = %s , StorageType = %s , TraversalType = %s , Callback = %s , N = %d , Depth = %d, Leaves = %d , Density = %.3f , Samples = %d , Cycles = %ld , Seconds = %f , WallSeconds = %f , AvgCycles = %f , AvgSeconds = %f , AvgWallSeconds = %f\n",
			treeType, storageType, traversalType, callbackName, treeInfo.size, treeInfo.depth, treeInfo.leaves, treeInfo.density, timeInfo.samples, timeInfo.cycles, timeInfo.seconds, timeInfo.wallTime, timeInfo.avgCycles, timeInfo.avgSeconds, timeInfo.avgWallTime
		);
	}
	else
	{
		fprintf(
			stdout, "%s,%s,%s,%s,%d,%d,%d,%f,%d,%ld,%f,%f,%f,%f,%f\n",
			treeType, storageType, traversalType, callbackName, treeInfo.size, treeInfo.depth, treeInfo.leaves, treeInfo.density, timeInfo.samples, timeInfo.cycles, timeInfo.seconds, timeInfo.wallTime,  timeInfo.avgCycles, timeInfo.avgSeconds, timeInfo.avgWallTime
		);
	}
}

double wallTimeDiff(struct timeval start, struct timeval end)
{
    long seconds = (end.tv_sec - start.tv_sec);
    long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
	return (double) micros / 1000000;
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
	struct timeval startTime, endTime;

	// mem_flush(treeInfo.root, treeInfo.size * sizeof(Tree));

	gettimeofday(&startTime, NULL);
	tic = clock();
	for (i=0; i<samples; i++)
	{
		traversalFunc(treeInfo.root);
	}
	toc = clock();
	gettimeofday(&endTime, NULL);

	timeInfo.samples 		= samples;
	timeInfo.cycles			= toc - tic;
	timeInfo.seconds		= (double) (toc - tic) / CLOCKS_PER_SEC;
	timeInfo.wallTime		= wallTimeDiff(startTime, endTime);
	timeInfo.avgCycles		= (double) timeInfo.cycles / timeInfo.samples;
	timeInfo.avgSeconds		= timeInfo.seconds / timeInfo.samples;
	timeInfo.avgWallTime	= timeInfo.wallTime / timeInfo.samples;

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
	struct timeval startTime, endTime;

	gettimeofday(&startTime, NULL);
	tic = clock();
	for (i=0; i<samples; i++)
	{
		traversalFunc(treeInfo.root, callback);
	}
	toc = clock();
	gettimeofday(&endTime, NULL);

	timeInfo.samples 		= samples;
	timeInfo.cycles			= toc - tic;
	timeInfo.seconds		= (double) (toc - tic) / CLOCKS_PER_SEC;
	timeInfo.wallTime		= wallTimeDiff(startTime, endTime);
	timeInfo.avgCycles		= (double) timeInfo.cycles / timeInfo.samples;
	timeInfo.avgSeconds		= timeInfo.seconds / timeInfo.samples;
	timeInfo.avgWallTime	= timeInfo.wallTime / timeInfo.samples;

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
	struct timeval startTime, endTime;

	gettimeofday(&startTime, NULL);
	tic = clock();
	for (i=0; i<samples; i++)
	{
		traversalFunc(treeInfo.root, treeQueue);
	}
	toc = clock();
	gettimeofday(&endTime, NULL);

	timeInfo.samples 		= samples;
	timeInfo.cycles			= toc - tic;
	timeInfo.seconds		= (double) (toc - tic) / CLOCKS_PER_SEC;
	timeInfo.wallTime		= wallTimeDiff(startTime, endTime);
	timeInfo.avgCycles		= (double) timeInfo.cycles / timeInfo.samples;
	timeInfo.avgSeconds		= timeInfo.seconds / timeInfo.samples;
	timeInfo.avgWallTime	= timeInfo.wallTime / timeInfo.samples;


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
	struct timeval startTime, endTime;

	gettimeofday(&startTime, NULL);
	tic = clock();
	for (i=0; i<samples; i++)
	{
		traversalFunc(treeInfo.root, treeQueue, callback);
	}
	toc = clock();
	gettimeofday(&endTime, NULL);

	timeInfo.samples 		= samples;
	timeInfo.cycles			= toc - tic;
	timeInfo.seconds		= (double) (toc - tic) / CLOCKS_PER_SEC;
	timeInfo.wallTime		= wallTimeDiff(startTime, endTime);
	timeInfo.avgCycles		= (double) timeInfo.cycles / timeInfo.samples;
	timeInfo.avgSeconds		= timeInfo.seconds / timeInfo.samples;
	timeInfo.avgWallTime	= timeInfo.wallTime / timeInfo.samples;

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
	struct timeval startTime, endTime;

	gettimeofday(&startTime, NULL);
	tic = clock();
	for (i=0; i<samples; i++)
	{
		traversalFunc(btNodeArray, treeInfo.size);
	}
	toc = clock();
	gettimeofday(&endTime, NULL);

	timeInfo.samples 		= samples;
	timeInfo.cycles			= toc - tic;
	timeInfo.seconds		= (double) (toc - tic) / CLOCKS_PER_SEC;
	timeInfo.wallTime		= wallTimeDiff(startTime, endTime);
	timeInfo.avgCycles		= (double) timeInfo.cycles / timeInfo.samples;
	timeInfo.avgSeconds		= timeInfo.seconds / timeInfo.samples;
	timeInfo.avgWallTime	= timeInfo.wallTime / timeInfo.samples;

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
	struct timeval startTime, endTime;

	gettimeofday(&startTime, NULL);
	tic = clock();
	for (i=0; i<samples; i++)
	{
		traversalFunc(btNodeArray, treeInfo.size, callback);
	}
	toc = clock();
	gettimeofday(&endTime, NULL);


	timeInfo.samples 		= samples;
	timeInfo.cycles			= toc - tic;
	timeInfo.seconds		= (double) (toc - tic) / CLOCKS_PER_SEC;
	timeInfo.wallTime		= wallTimeDiff(startTime, endTime);
	timeInfo.avgCycles		= (double) timeInfo.cycles / timeInfo.samples;
	timeInfo.avgSeconds		= timeInfo.seconds / timeInfo.samples;
	timeInfo.avgWallTime	= timeInfo.wallTime / timeInfo.samples;

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