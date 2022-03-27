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

#ifndef	__BINARYTREE_EXP_H
#define	__BINARYTREE_EXP_H


/******************************************************************************* 
------------------------------- IMPORTS & PARAMS -------------------------------
*******************************************************************************/
#include <time.h>

#include "types.h"


/******************************************************************************* 
---------------------------------- FUNC DECL -----------------------------------
*******************************************************************************/

/* type used to store info for timing tree traversal experiments */
typedef struct TimeInfo
{
  clock_t cycles;
  double seconds;
  int samples;
  double wallTime;
  double avgCycles;
  double avgSeconds;
  double avgWallTime;
} TimeInfo;

/* types for passing function pointer to traversal function */
typedef void (*TraversalFunc)(Tree *);
typedef void (*TraversalFuncCB)(Tree *, TreeCallback);
typedef void (*TraversalFuncLevel)(Tree *, TreeQueue *);
typedef void (*TraversalFuncLevelCB)(Tree *, TreeQueue *, TreeCallback);
typedef void (*TraversalFuncCont)(Tree *, int);
typedef void (*TraversalFuncContCB)(Tree *, int, TreeCallback);

#endif
/******************************************************************************* 
--------------------------------- END OF FILE ----------------------------------
*******************************************************************************/