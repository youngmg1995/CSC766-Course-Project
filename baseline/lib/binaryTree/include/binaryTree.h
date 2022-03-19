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
extern void initTree(Tree *t);
extern Tree * make_empty(Tree *t);
extern Tree * find_min(Tree *t);
extern Tree * find_max(Tree *t);
extern Tree * find(int id, Tree *t);
extern Tree * insert(int id, void *data, Tree *t);
extern Tree * delete(int id, Tree * t, void *data);



#endif
/******************************************************************************* 
--------------------------------- END OF FILE ----------------------------------
*******************************************************************************/