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

#ifndef	__BINARYTREE_UTIL_H
#define	__BINARYTREE_UTIL_H



/******************************************************************************* 
------------------------------- IMPORTS & PARAMS -------------------------------
*******************************************************************************/
#include "types.h"



/******************************************************************************* 
--------------------------------- DECLARATIONS ---------------------------------
*******************************************************************************/
/* math stuff */
extern int factorial(int x);
extern int catalan(int x);

/* random number generation */
extern double genrand64_real2(void);
extern void init_genrand64(unsigned long long seed);

/* tree printing */
extern void print_ascii_tree(Tree * t);



#endif
/******************************************************************************* 
--------------------------------- END OF FILE ----------------------------------
*******************************************************************************/