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
extern TimeInfo timeTraversal(
	TreeInfo treeInfo, TraversalFunc traversalFunc, int samples, 
	bool printResults, bool verbose, const char treeType[], const char storageType[],
	const char traversalName[], const char callbackName[]
);

extern TimeInfo timeTraversalCB(
	TreeInfo treeInfo, TraversalFuncCB traversalFunc, TreeCallback callback, int samples, 
	bool printResults, bool verbose, const char treeType[], const char storageType[],
	const char traversalName[], const char callbackName[]
);

extern TimeInfo timeTraversalCont(
	TreeInfo treeInfo, Tree *btNodeArray, TraversalFuncCont traversalFunc, int samples, 
	bool printResults, bool verbose, const char treeType[], const char storageType[],
	const char traversalName[], const char callbackName[]
);

extern TimeInfo timeTraversalContCB(
	TreeInfo treeInfo,  Tree *btNodeArray, TraversalFuncContCB traversalFunc, TreeCallback callback, int samples, 
	bool printResults, bool verbose, const char treeType[], const char storageType[],
	const char traversalName[], const char callbackName[]
);


#endif
/******************************************************************************* 
--------------------------------- END OF FILE ----------------------------------
*******************************************************************************/