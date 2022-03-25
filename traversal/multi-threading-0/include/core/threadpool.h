/******************************************************************************* 
------------------------------------- INFO -------------------------------------
*******************************************************************************/
/**
 * @file types.h
 * @author Mitchell Young (mgyoung@ncsu.edu)
 * @brief Header file for function declarations related to thread pool used
 *  in multi-threaded implementation of tree traversals.
 * @version 0.1
 * @date 2022-03-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef	__BINARYTREE_THREADPOOL_H
#define	__BINARYTREE_THREADPOOL_H


/******************************************************************************* 
------------------------------- IMPORTS & PARAMS -------------------------------
*******************************************************************************/
#include <stdbool.h>

#include "types.h"

#define NUM_THREADS 5
#define TASK_QUEUE_SIZE 1<<16



/******************************************************************************* 
---------------------------- FUNCTION DECLARATIONS -----------------------------
*******************************************************************************/

/* functions for thread pool and task queue */
extern void execTraversalTask(TraversalTask *task);
extern void submitTraversalTask(TraversalTask task);
extern void * startThread(void *args);
extern void initThreadPool();
extern void joinThreadPool();

/* new multi-threaded traversal functions */
extern void preOrderMTWrapper(Tree * root, TreeCallback callback);
extern void postOrderMTWrapper(Tree *root, TreeCallback callback);



#endif
/******************************************************************************* 
--------------------------------- END OF FILE ----------------------------------
*******************************************************************************/