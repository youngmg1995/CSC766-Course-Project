/******************************************************************************* 
------------------------------------- INFO -------------------------------------
*******************************************************************************/
/**
 * @file binaryTreeGen.h
 * @author Mitchell Young (mgyoung@ncsu.edu)
 * @brief Includes the types and functionalites necessary to generate binary
 * 	trees. The generated trees can be random or balanced, and can also be
 * 	generic binary trees or binary search trees.
 * @version 0.1
 * @date 2022-03-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef	__BINARYTREE_GEN_H
#define	__BINARYTREE_GEN_H



/******************************************************************************* 
------------------------------- IMPORTS & PARAMS -------------------------------
*******************************************************************************/
#include "types.h"



/******************************************************************************* 
--------------------------------- DECLARATIONS ---------------------------------
*******************************************************************************/
/* basic tree generators */ 
extern Tree * genRandomTree(int N, bool isBST);
extern Tree * genContRandomTree(Tree *btNodeArray, int N, bool isBST);
extern Tree * genBalancedTree(int depth, bool isBST);
extern Tree * genContBalancedTree(Tree *btNodeArray, int depth, bool isBST);

/* optimized tree generators */ 
extern void genRandomTreeOptimized(int *invTable, ITNode *itNodeArray, int N, bool isBST, TreeInfo *treeInfo);
extern void genContRandomTreeOptimized(int *invTable, Tree *btNodeArray, ITNode *itNodeArray, int N, bool isBST, TreeInfo *treeInfo);
extern void genBalancedTreeOptimized(int *invTable, ITNode *itNodeArray, int depth, bool isBST, TreeInfo *treeInfo);
extern void genContBalancedTreeOptimized(int *invTable, Tree *btNodeArray, ITNode *itNodeArray, int depth, bool isBST, TreeInfo *treeInfo);

/* other useful functions */ 
extern Tree * invTab2BT(int *invTable, int N);
extern Tree * invTab2ContBT(int *invTable, Tree *btNodeArray, int N);
extern Tree * invTab2BTOptimized(int *invTable, ITNode *itNodeArray, int N);
extern Tree * invTab2ContBTOptimized(int *invTable, Tree *btNodeArray, ITNode *itNodeArray, int N);
extern void convert2BST(Tree *root);
extern void genTree2StdOut(int N);
extern void genInversionTable(int *invTable, int N);
extern void printInvTab(int *invTable, int N, bool vert);
extern void initITNode(ITNode *node);



#endif
/******************************************************************************* 
--------------------------------- END OF FILE ----------------------------------
*******************************************************************************/