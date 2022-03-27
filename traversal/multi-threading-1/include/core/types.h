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

#ifndef	__BINARYTREE_TYPES_H
#define	__BINARYTREE_TYPES_H


/******************************************************************************* 
------------------------------- IMPORTS & PARAMS -------------------------------
*******************************************************************************/



/******************************************************************************* 
---------------------------------- TYPE DEFS -----------------------------------
*******************************************************************************/

/* basic binary tree (primary type used in module) */
typedef struct Tree Tree;
struct Tree
{
	int id;
	void *data;
	Tree *left;
	Tree *right;
};

/* type used while building binary tree from inversion table */
typedef struct ITNode ITNode;
struct ITNode
{
	int val;
	Tree *tree;
	ITNode *parent;
};

/* type used to get info about generated binary tree */
typedef struct TreeInfo
{
	int size;
	int leaves;
	int depth;
	float density;
	Tree *root;
} TreeInfo;

/* defines callback function type for performing actions during tree traversal */
typedef void (*TreeCallback)(Tree *);

/* binary tree queue, used for level-order traversal */
typedef struct TreeQueue
{
	int capacity;
	int size;
	int front;
	int back;
	Tree **queue;
} TreeQueue;

/* types for passing function pointer to traversal function */
typedef void (*TraversalFunc)(Tree *);
typedef void (*TraversalFuncCB)(Tree *, TreeCallback);
typedef void (*TraversalFuncLevel)(Tree *, TreeQueue *);
typedef void (*TraversalFuncLevelCB)(Tree *, TreeQueue *, TreeCallback);
typedef void (*TraversalFuncCont)(Tree *, int);
typedef void (*TraversalFuncContCB)(Tree *, int, TreeCallback);

/* types used for multi-threading */
typedef struct TraversalTask {
	Tree * root;
	TreeCallback callback;
} TraversalTask;

#endif
/******************************************************************************* 
--------------------------------- END OF FILE ----------------------------------
*******************************************************************************/