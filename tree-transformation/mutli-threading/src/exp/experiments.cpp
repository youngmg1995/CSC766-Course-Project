/******************************************************************************* 
------------------------------------- INFO -------------------------------------
*******************************************************************************/
/**
 * @file experiments.cpp
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

#include "treeLoader.h"
#include "treeConversion.h"

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

	bool printResults = true;
	bool verbose = false;

	/* ---------------------------------------------------------------------- */

	traversalBatch(
		tiny_tree_file_compressed, "tiny", 
		TINY_TREE_SIZE_BU, TINY_TREE_SIZE_TD,
		printResults, verbose
	);
	traversalBatch2(
		tiny_tree_file_compressed, "tiny", 
		TINY_TREE_SIZE_BU, TINY_TREE_SIZE_TD,
		printResults, verbose
	);
	traversalBatch3(
		tiny_tree_file_compressed, "tiny", 
		TINY_TREE_SIZE_BU, TINY_TREE_SIZE_TD,
		printResults, verbose
	);

	/* ---------------------------------------------------------------------- */

	traversalBatch(
		small_tree_file_compressed, "small", 
		SMALL_TREE_SIZE_BU, SMALL_TREE_SIZE_TD,
		printResults, verbose
	);
	traversalBatch2(
		small_tree_file_compressed, "small", 
		SMALL_TREE_SIZE_BU, SMALL_TREE_SIZE_TD,
		printResults, verbose
	);
	traversalBatch3(
		small_tree_file_compressed, "small", 
		SMALL_TREE_SIZE_BU, SMALL_TREE_SIZE_TD,
		printResults, verbose
	);

	/* ---------------------------------------------------------------------- */

	traversalBatch(
		big_tree_file_compressed, "big", 
		BIG_TREE_SIZE_BU, BIG_TREE_SIZE_TD,
		printResults, verbose
	);
	traversalBatch2(
		big_tree_file_compressed, "big", 
		BIG_TREE_SIZE_BU, BIG_TREE_SIZE_TD,
		printResults, verbose
	);
	traversalBatch3(
		big_tree_file_compressed, "big", 
		BIG_TREE_SIZE_BU, BIG_TREE_SIZE_TD,
		printResults, verbose
	);

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