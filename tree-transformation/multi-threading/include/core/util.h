/******************************************************************************* 
------------------------------------- INFO -------------------------------------
*******************************************************************************/
/**
 * @file util.h
 * @author Mitchell Young (mgyoung@ncsu.edu)
 * @brief Random utilities for project.
 * @version 0.1
 * @date 2022-04-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef	__TREETRAV_UTIL_H
#define	__TREETRAV_UTIL_H



/******************************************************************************* 
------------------------------- IMPORTS & PARAMS -------------------------------
*******************************************************************************/



/******************************************************************************* 
--------------------------------- DECLARATIONS ---------------------------------
*******************************************************************************/

/* for printing a tree */
extern void print_ascii_tree(node * t);

/* random number generation */
extern double genrand64_real2(void);
extern void init_genrand64(unsigned long long seed);



#endif
/******************************************************************************* 
--------------------------------- END OF FILE ----------------------------------
*******************************************************************************/