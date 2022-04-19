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
	TimeInfo timeInfo, const char treeType[], const char experType[], const char direction[],
	bool verbose
)
{
	if (verbose)
	{
		fprintf(
			stdout, "TreeType = %s , ExpType = %s , Direction = %s , Samples = %d , Cycles = %ld , Seconds = %f , WallSeconds = %f , AvgCycles = %f , AvgSeconds = %f , AvgWallSeconds = %f\n",
			treeType, experType, direction, timeInfo.samples, timeInfo.cycles, timeInfo.seconds, timeInfo.wallTime, timeInfo.avgCycles, timeInfo.avgSeconds, timeInfo.avgWallTime
		);
	}
	else
	{
		// fprintf(
		// 	stdout, "%s,%s,%s,%d,%ld,%f,%f,%f,%f,%f\n",
		// 	treeType, experType, direction, timeInfo.samples, timeInfo.cycles, timeInfo.seconds, timeInfo.wallTime,  timeInfo.avgCycles, timeInfo.avgSeconds, timeInfo.avgWallTime
		// );
		// fprintf(
		// 	stdout, "%d,%f\n",
		// 	treeInfo.size, timeInfo.avgWallTime
		// );
		fprintf(
			stdout, "%f\n",
			timeInfo.avgWallTime
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

// /* ---------------------------- Plain Traversal ----------------------------- */

// TimeInfo timeTraversal(
// 	node * root,
// 	bool printResults, bool verbose, 
// 	const char treeType[], const char direction[]
// )
// {
// 	TimeInfo timeInfo = {0};

// 	clock_t tic, toc;
// 	struct timeval startTime, endTime;

// 	gettimeofday(&startTime, NULL);
// 	tic = clock();
// 	splayTraversal(root);
// 	toc = clock();
// 	gettimeofday(&endTime, NULL);

// 	timeInfo.samples 		= 1;
// 	timeInfo.cycles			= toc - tic;
// 	timeInfo.seconds		= (double) (toc - tic) / CLOCKS_PER_SEC;
// 	timeInfo.wallTime		= wallTimeDiff(startTime, endTime);
// 	timeInfo.avgCycles		= (double) timeInfo.cycles / timeInfo.samples;
// 	timeInfo.avgSeconds		= timeInfo.seconds / timeInfo.samples;
// 	timeInfo.avgWallTime	= timeInfo.wallTime / timeInfo.samples;

// 	if (printResults)
// 	{
// 		printExpResults(timeInfo, treeType, "plain-traversal", direction, verbose);
// 	}


// 	return timeInfo;
// }

// /* -------------------------------------------------------------------------- */


/* ----------------------- Transform With Mem. Alloc. ----------------------- */

TimeInfo timeTransformMalloc(
	node * root, node **outputRoot,
	bool printResults, bool verbose, 
	const char treeType[], const char direction[]
)
{
	TimeInfo timeInfo = {0};

	clock_t tic, toc;
	struct timeval startTime, endTime;

	gettimeofday(&startTime, NULL);
	tic = clock();
	*outputRoot = td2buTransformMain(root);
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
		printExpResults(timeInfo, treeType, "transform-malloc", direction, verbose);
	}

	return timeInfo;
}

/* -------------------------------------------------------------------------- */


/* --------------------- Transform Without Mem. Alloc. ---------------------- */

TimeInfo timeTransformNoMalloc(
	node * root, node *outputArray,
	bool printResults, bool verbose, 
	const char treeType[], const char direction[]
)
{
	TimeInfo timeInfo = {0};

	clock_t tic, toc;
	struct timeval startTime, endTime;

	gettimeofday(&startTime, NULL);
	tic = clock();
	td2buTransformContMain(root, outputArray);
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
		printExpResults(timeInfo, treeType, "transform-no-malloc", direction, verbose);
	}

	return timeInfo;
}

/* -------------------------------------------------------------------------- */


/* --------------------- Transform Without Mem. Alloc. ---------------------- */

TimeInfo timeTransformNoMalloc2(
	node * root, node **outputArrays,
	bool printResults, bool verbose, 
	const char treeType[], const char direction[]
)
{
	TimeInfo timeInfo = {0};

	clock_t tic, toc;
	struct timeval startTime, endTime;

	gettimeofday(&startTime, NULL);
	tic = clock();
	td2buTransformContMain2(root, outputArrays);
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
		printExpResults(timeInfo, treeType, "transform-no-malloc-2", direction, verbose);
	}

	return timeInfo;
}

/* -------------------------------------------------------------------------- */


































// /* --------------------- Transform Without Mem. Alloc. ---------------------- */

// TimeInfo timeTransformNoMalloc2(
// 	node * root, node *outputArray,
// 	bool printResults, bool verbose, 
// 	const char treeType[], const char direction[]
// )
// {
// 	TimeInfo timeInfo = {0};

// 	clock_t tic, toc;
// 	struct timeval startTime, endTime;

// 	gettimeofday(&startTime, NULL);
// 	tic = clock();
// 	td2buTransformContMain2(root, outputArray);
// 	toc = clock();
// 	gettimeofday(&endTime, NULL);

// 	timeInfo.samples 		= 1;
// 	timeInfo.cycles			= toc - tic;
// 	timeInfo.seconds		= (double) (toc - tic) / CLOCKS_PER_SEC;
// 	timeInfo.wallTime		= wallTimeDiff(startTime, endTime);
// 	timeInfo.avgCycles		= (double) timeInfo.cycles / timeInfo.samples;
// 	timeInfo.avgSeconds		= timeInfo.seconds / timeInfo.samples;
// 	timeInfo.avgWallTime	= timeInfo.wallTime / timeInfo.samples;

// 	if (printResults)
// 	{
// 		printExpResults(timeInfo, treeType, "transform-no-malloc-2", direction, verbose);
// 	}

// 	return timeInfo;
// }

// /* -------------------------------------------------------------------------- */


// /* ------------------ Cont. Transform Without Mem. Alloc. ------------------- */

// TimeInfo timeTransformCont(
// 	node *inputArray, int inputSize, node *outputArray,
// 	bool printResults, bool verbose, 
// 	const char treeType[], const char direction[]
// )
// {
// 	TimeInfo timeInfo = {0};

// 	clock_t tic, toc;
// 	struct timeval startTime, endTime;

// 	gettimeofday(&startTime, NULL);
// 	tic = clock();
// 	td2buTransformCont2(inputArray, inputSize, outputArray);
// 	toc = clock();
// 	gettimeofday(&endTime, NULL);

// 	timeInfo.samples 		= 1;
// 	timeInfo.cycles			= toc - tic;
// 	timeInfo.seconds		= (double) (toc - tic) / CLOCKS_PER_SEC;
// 	timeInfo.wallTime		= wallTimeDiff(startTime, endTime);
// 	timeInfo.avgCycles		= (double) timeInfo.cycles / timeInfo.samples;
// 	timeInfo.avgSeconds		= timeInfo.seconds / timeInfo.samples;
// 	timeInfo.avgWallTime	= timeInfo.wallTime / timeInfo.samples;

// 	if (printResults)
// 	{
// 		printExpResults(timeInfo, treeType, "transform-cont", direction, verbose);
// 	}

// 	return timeInfo;
// }

// /* -------------------------------------------------------------------------- */

/******************************************************************************* 
--------------------------------- END OF FILE ----------------------------------
*******************************************************************************/