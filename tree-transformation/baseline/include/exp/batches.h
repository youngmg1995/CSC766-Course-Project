/******************************************************************************* 
------------------------------------- INFO -------------------------------------
*******************************************************************************/
/**
 * @file types.h
 * @author Mitchell Young (mgyoung@ncsu.edu)
 * @brief Defines binary tree types and other types used to create/draw them.
 * @version 0.1
 * @date 2022-03-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef	__BINARYTREE_BATCH_H
#define	__BINARYTREE_BATCH_H


/******************************************************************************* 
------------------------------- IMPORTS & PARAMS -------------------------------
*******************************************************************************/
#include "exp.h"


/******************************************************************************* 
---------------------------------- FUNC DECL -----------------------------------
*******************************************************************************/

/* functions for timing each tree traversal */
extern void traversalBatch(
	const char tree_input_file[], const char treeType[], 
	int buTreeSize, int tdTreeSize,
	bool printResults, bool verbose
);
extern void traversalBatch2(
	const char tree_input_file[], const char treeType[], 
	int buTreeSize, int tdTreeSize,
	bool printResults, bool verbose
);
extern void traversalBatch3(
	const char tree_input_file[], const char treeType[], 
	int buTreeSize, int tdTreeSize,
	bool printResults, bool verbose
);



#endif
/******************************************************************************* 
--------------------------------- END OF FILE ----------------------------------
*******************************************************************************/