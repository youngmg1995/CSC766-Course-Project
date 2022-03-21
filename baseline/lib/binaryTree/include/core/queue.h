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

#ifndef	__BINARYTREE_QUEUE_H
#define	__BINARYTREE_QUEUE_H


/******************************************************************************* 
------------------------------- IMPORTS & PARAMS -------------------------------
*******************************************************************************/
#include <stdbool.h>

#include "types.h"



/******************************************************************************* 
---------------------------- FUNCTION DECLARATIONS -----------------------------
*******************************************************************************/
extern void initTQ(TreeQueue *tq, int capacity);
extern void freeTQ(TreeQueue *tq);
extern void resetTQ(TreeQueue *tq);
extern bool isEmptyTQ(TreeQueue *tq);
extern bool isFullTQ(TreeQueue *tq);
extern void enQueueTQ(TreeQueue *tq, Tree *t);
extern Tree * deQueueTQ(TreeQueue *tq);



#endif
/******************************************************************************* 
--------------------------------- END OF FILE ----------------------------------
*******************************************************************************/