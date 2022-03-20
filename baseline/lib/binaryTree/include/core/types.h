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

// /* binary tree queue, used for level-order traversal */
// typedef struct TreeQueue TreeQueue;
// struct TreeQueue
// {
//   int size;

// }

/* defines callback function type for performing actions during tree traversal */
typedef void (*TreeCallback)(Tree *);

#endif
/******************************************************************************* 
--------------------------------- END OF FILE ----------------------------------
*******************************************************************************/