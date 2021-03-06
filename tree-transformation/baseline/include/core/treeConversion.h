/******************************************************************************* 
------------------------------------- INFO -------------------------------------
*******************************************************************************/
/**
 * @file treeConversion.h
 * @author Mitchell Young (mgyoung@ncsu.edu)
 * @brief Includes functions for converting top-down trees to bottom-up
 *  trees and vice versa.
 * @version 0.1
 * @date 2022-04-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef	__TREETRAV_TREECONV_H
#define	__TREETRAV_TREECONV_H



/******************************************************************************* 
------------------------------- IMPORTS & PARAMS -------------------------------
*******************************************************************************/
#include <types.h>

#define TINY_TREE_SIZE_TD   12
#define TINY_TREE_SIZE_BU   9
#define SMALL_TREE_SIZE_TD   2386
#define SMALL_TREE_SIZE_BU   4378
#define BIG_TREE_SIZE_TD   709780
#define BIG_TREE_SIZE_BU   5188410



/******************************************************************************* 
--------------------------------- DECLARATIONS ---------------------------------
*******************************************************************************/

/* tree conversion functions */
extern node * td2buTransform(node *tdRoot);
extern node * td2buTransformCont(node *tdRoot, node *nodeArray);
extern node * td2buTransformCont2(node *inputArray, int inputSize, node *outputArray);

/* unit tests */
extern void treeConvUnitTest(const char tree_input_file[]);

/* other useful functions */
extern int getTreeSize(node *root);



#endif
/******************************************************************************* 
--------------------------------- END OF FILE ----------------------------------
*******************************************************************************/