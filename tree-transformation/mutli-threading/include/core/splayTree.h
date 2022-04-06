/******************************************************************************* 
------------------------------------- INFO -------------------------------------
*******************************************************************************/
/**
 * @file splayTree.h
 * @author Mitchell Young (mgyoung@ncsu.edu)
 * @brief Includes the types and functionalites necessary to create and
 * 	manipulate splay trees.
 * @version 0.1
 * @date 2022-03-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef	__TREETRAV_SPLAY_H
#define	__TREETRAV_SPLAY_H



/******************************************************************************* 
------------------------------- IMPORTS & PARAMS -------------------------------
*******************************************************************************/
#include <types.h>



/******************************************************************************* 
--------------------------------- DECLARATIONS ---------------------------------
*******************************************************************************/

/* splay tree methods */
extern node * newNode(int key);
extern void initNode(node *n);
extern node * freeTree(node *root);
extern node * search(node *root, int key);
extern node * insert(node *root, int key);
extern node * insertNode(node *root, node *n);
extern node * insertCont(node *root, int k, node **nodeArray);
extern void preOrder(node *root);


/* unit test */
extern void splayTreeUnitTest();



#endif
/******************************************************************************* 
--------------------------------- END OF FILE ----------------------------------
*******************************************************************************/