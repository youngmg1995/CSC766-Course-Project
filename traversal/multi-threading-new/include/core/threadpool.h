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
#include "types.h"

#define NUM_THREADS 2



/******************************************************************************* 
---------------------------- FUNCTION DECLARATIONS -----------------------------
*******************************************************************************/

/* functions for thread pool and task queue */
extern void initThreadPool(ThreadPool *threadPool, StartThreadArgs *startArgs, int size);
extern void destroyThreadPool(ThreadPool *threadPool, StartThreadArgs *startArgs);

/* new multi-threaded traversal functions */
extern void preOrderMTWrapper(Tree *root, TreeCallback callback, ThreadPool *threadPool, StartThreadArgs *startArgs);
extern void postOrderMTWrapper(Tree *root, TreeCallback callback, ThreadPool *threadPool, StartThreadArgs *startArgs);



#endif
/******************************************************************************* 
--------------------------------- END OF FILE ----------------------------------
*******************************************************************************/