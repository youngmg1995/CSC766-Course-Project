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

#ifndef	__BINARYTREE_TIMER_H
#define	__BINARYTREE_TIMER_H


/******************************************************************************* 
------------------------------- IMPORTS & PARAMS -------------------------------
*******************************************************************************/
#include "exp.h"


/******************************************************************************* 
---------------------------------- FUNC DECL -----------------------------------
*******************************************************************************/

/* functions for timing each tree traversal */
// extern TimeInfo timeTraversal(
// 	node * root,
// 	bool printResults, bool verbose, 
// 	const char treeType[], const char direction[]
// );
extern TimeInfo timeTransformMalloc(
	node * root, node **outputRoot,
	bool printResults, bool verbose, 
	const char treeType[], const char direction[]
);
extern TimeInfo timeTransformNoMalloc(
	node * root, node *outputArray,
	bool printResults, bool verbose, 
	const char treeType[], const char direction[]
);
// extern TimeInfo timeTransformCont(
// 	node *inputArray, int inputSize, node *outputArray,
// 	bool printResults, bool verbose, 
// 	const char treeType[], const char direction[]
// );


#endif
/******************************************************************************* 
--------------------------------- END OF FILE ----------------------------------
*******************************************************************************/