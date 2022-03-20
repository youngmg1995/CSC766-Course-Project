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
---------------------------------- TYPE DEFS -----------------------------------
*******************************************************************************/

/* type used to store info for timing tree traversal experiments */
typedef struct TimeInfo
{
  clock_t cycles;
  double seconds;
  int samples;
} TimeInfo;

/* types for passing function pointer to traversal function */
typedef void (*TraversalFunc)(Tree *);
typedef void (*TraversalFuncCB)(Tree *, TreeCallback);

#endif
/******************************************************************************* 
--------------------------------- END OF FILE ----------------------------------
*******************************************************************************/