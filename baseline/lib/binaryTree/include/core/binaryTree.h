/******************************************************************************* 
------------------------------------- INFO -------------------------------------
*******************************************************************************/
/**
 * @file binaryTree.h
 * @author Mitchell Young (mgyoung@ncsu.edu)
 * @brief Includes the types and functionalites necessary to create and
 * 	manipulate binary trees.
 * @version 0.1
 * @date 2022-03-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef	__BINARYTREE_H
#define	__BINARYTREE_H



/******************************************************************************* 
------------------------------- IMPORTS & PARAMS -------------------------------
*******************************************************************************/
#include "types.h"



/******************************************************************************* 
--------------------------------- DECLARATIONS ---------------------------------
*******************************************************************************/

/* basic methods for the tree type */
extern void initTree(Tree *t);
extern Tree * make_empty(Tree *t);
extern Tree * find_min(Tree *t);
extern Tree * find_max(Tree *t);
extern Tree * find(int id, Tree *t);
extern Tree * insert(int id, void *data, Tree *t);
extern Tree * delete(int id, Tree * t, void *data);
extern void printNode(Tree *t);
extern void incrementID(Tree *t);

/* traversals */
extern void preOrder(Tree *root);
extern void inOrder(Tree *root);
extern void postOrder(Tree *root);
extern void contiguousOrder(Tree *treeArray, int N);
extern void preOrderCB(Tree *root, TreeCallback callBack);
extern void inOrderCB(Tree *root, TreeCallback callBack);
extern void postOrderCB(Tree *root, TreeCallback callBack);
extern void contiguousOrderCB(Tree *treeArray, int N, TreeCallback callBack);



#endif
/******************************************************************************* 
--------------------------------- END OF FILE ----------------------------------
*******************************************************************************/