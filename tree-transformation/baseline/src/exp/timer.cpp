/******************************************************************************* 
------------------------------------- INFO -------------------------------------
*******************************************************************************/
/**
 * @file timer.cpp
 * @author Mitchell Young (mgyoung@ncsu.edu)
 * @brief Times experiments on tree transformations.
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
#include "splayTree.h"
#include "treeConversion.h"
#include "traversal.h"

#include "exp.h"


/******************************************************************************* 
------------------------------- HELPER FUNCTIONS -------------------------------
*******************************************************************************/
void printExpResults(
	TimeInfo timeInfo, const char treeType[], const char experType[],
	bool verbose
)
{
	if (verbose)
	{
		fprintf(
			stdout, "TreeType = %s , ExpType = %s , Samples = %d , Cycles = %ld , Seconds = %f , WallSeconds = %f , AvgCycles = %f , AvgSeconds = %f , AvgWallSeconds = %f\n",
			treeType, experType, timeInfo.samples, timeInfo.cycles, timeInfo.seconds, timeInfo.wallTime, timeInfo.avgCycles, timeInfo.avgSeconds, timeInfo.avgWallTime
		);
	}
	else
	{
		fprintf(
			stdout, "%s,%s,%d,%ld,%f,%f,%f,%f,%f\n",
			treeType, experType, timeInfo.samples, timeInfo.cycles, timeInfo.seconds, timeInfo.wallTime,  timeInfo.avgCycles, timeInfo.avgSeconds, timeInfo.avgWallTime
		);
	}
}

double wallTimeDiff(struct timeval start, struct timeval end)
{
    long seconds = (end.tv_sec - start.tv_sec);
    long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
	return (double) micros / 1000000;
}


/******************************************************************************* 
------------------------------- PRIMARY EXPORTS --------------------------------
*******************************************************************************/

/* ---------------------------- Plain Traversal ----------------------------- */

TimeInfo timeTraversal(
	node * root,
	bool printResults, bool verbose, 
	const char treeType[]
)
{
	TimeInfo timeInfo = {0};

	clock_t tic, toc;
	struct timeval startTime, endTime;

	gettimeofday(&startTime, NULL);
	tic = clock();
	splayTraversal(root);
	toc = clock();
	gettimeofday(&endTime, NULL);

	timeInfo.samples 		= 1;
	timeInfo.cycles			= toc - tic;
	timeInfo.seconds		= (double) (toc - tic) / CLOCKS_PER_SEC;
	timeInfo.wallTime		= wallTimeDiff(startTime, endTime);
	timeInfo.avgCycles		= (double) timeInfo.cycles / timeInfo.samples;
	timeInfo.avgSeconds		= timeInfo.seconds / timeInfo.samples;
	timeInfo.avgWallTime	= timeInfo.wallTime / timeInfo.samples;

	if (printResults)
	{
		printExpResults(timeInfo, treeType, "plain-traversal", verbose);
	}


	return timeInfo;
}

/* -------------------------------------------------------------------------- */


/* ----------------------- Transform With Mem. Alloc. ----------------------- */

TimeInfo timeTransformMalloc(
	node * root,
	bool printResults, bool verbose, 
	const char treeType[]
)
{
	TimeInfo timeInfo = {0};

	clock_t tic, toc;
	struct timeval startTime, endTime;
	node *transfRoot;

	gettimeofday(&startTime, NULL);
	tic = clock();
	transfRoot = td2buTransform(root);
	toc = clock();
	gettimeofday(&endTime, NULL);

	timeInfo.samples 		= 1;
	timeInfo.cycles			= toc - tic;
	timeInfo.seconds		= (double) (toc - tic) / CLOCKS_PER_SEC;
	timeInfo.wallTime		= wallTimeDiff(startTime, endTime);
	timeInfo.avgCycles		= (double) timeInfo.cycles / timeInfo.samples;
	timeInfo.avgSeconds		= timeInfo.seconds / timeInfo.samples;
	timeInfo.avgWallTime	= timeInfo.wallTime / timeInfo.samples;

	if (printResults)
	{
		printExpResults(timeInfo, treeType, "transform-malloc", verbose);
	}

	freeTree(transfRoot);

	return timeInfo;
}

/* -------------------------------------------------------------------------- */


/* --------------------- Transform Without Mem. Alloc. ---------------------- */

TimeInfo timeTransformNoMalloc(
	node * root, node *outputArray,
	bool printResults, bool verbose, 
	const char treeType[]
)
{
	TimeInfo timeInfo = {0};

	clock_t tic, toc;
	struct timeval startTime, endTime;

	gettimeofday(&startTime, NULL);
	tic = clock();
	td2buTransformCont(root, outputArray);
	toc = clock();
	gettimeofday(&endTime, NULL);

	timeInfo.samples 		= 1;
	timeInfo.cycles			= toc - tic;
	timeInfo.seconds		= (double) (toc - tic) / CLOCKS_PER_SEC;
	timeInfo.wallTime		= wallTimeDiff(startTime, endTime);
	timeInfo.avgCycles		= (double) timeInfo.cycles / timeInfo.samples;
	timeInfo.avgSeconds		= timeInfo.seconds / timeInfo.samples;
	timeInfo.avgWallTime	= timeInfo.wallTime / timeInfo.samples;

	if (printResults)
	{
		printExpResults(timeInfo, treeType, "transform-no-malloc", verbose);
	}

	return timeInfo;
}

/* -------------------------------------------------------------------------- */


/* ------------------ Cont. Transform Without Mem. Alloc. ------------------- */

TimeInfo timeTransformCont(
	node *inputArray, int inputSize, node *outputArray,
	bool printResults, bool verbose, 
	const char treeType[]
)
{
	TimeInfo timeInfo = {0};

	clock_t tic, toc;
	struct timeval startTime, endTime;

	gettimeofday(&startTime, NULL);
	tic = clock();
	td2buTransformCont2(inputArray, inputSize, outputArray);
	toc = clock();
	gettimeofday(&endTime, NULL);

	timeInfo.samples 		= 1;
	timeInfo.cycles			= toc - tic;
	timeInfo.seconds		= (double) (toc - tic) / CLOCKS_PER_SEC;
	timeInfo.wallTime		= wallTimeDiff(startTime, endTime);
	timeInfo.avgCycles		= (double) timeInfo.cycles / timeInfo.samples;
	timeInfo.avgSeconds		= timeInfo.seconds / timeInfo.samples;
	timeInfo.avgWallTime	= timeInfo.wallTime / timeInfo.samples;

	if (printResults)
	{
		printExpResults(timeInfo, treeType, "transform-cont", verbose);
	}

	return timeInfo;
}

/* -------------------------------------------------------------------------- */

/******************************************************************************* 
--------------------------------- END OF FILE ----------------------------------
*******************************************************************************/