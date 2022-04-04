/******************************************************************************* 
------------------------------------- INFO -------------------------------------
*******************************************************************************/
/**
 * @file treLoader.h
 * @author Mitchell Young (mgyoung@ncsu.edu)
 * @brief Includes the functionalites necessary to load in and output the
 *  tree structures we will be working with.
 * @version 0.1
 * @date 2022-03-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef	__TREETRAV_TREELOADER_H
#define	__TREETRAV_TREELOADER_H



/******************************************************************************* 
------------------------------- IMPORTS & PARAMS -------------------------------
*******************************************************************************/
#include <types.h>
#include <unordered_map>


#define tiny_tree_file "/Users/mitchell/Documents/classes/csc766/CSC766-Project/tree-transformation/.data/tiny_tree.json"
#define small_tree_file "/Users/mitchell/Documents/classes/csc766/CSC766-Project/tree-transformation/.data/small_tree.json"
#define big_tree_file "/Users/mitchell/Documents/classes/csc766/CSC766-Project/tree-transformation/.data/big_tree.json"
#define output_tree_file "/Users/mitchell/Documents/classes/csc766/CSC766-Project/tree-transformation/.data/output_tree.json"
#define output_bu_tree_file "/Users/mitchell/Documents/classes/csc766/CSC766-Project/tree-transformation/.data/output_bu_tree.json"
#define output_td_tree_file "/Users/mitchell/Documents/classes/csc766/CSC766-Project/tree-transformation/.data/output_td_tree.json"



/******************************************************************************* 
--------------------------------- DECLARATIONS ---------------------------------
*******************************************************************************/

/* functions for loading and outputting tree */
extern int loadJSON(const char fileName[], std::unordered_map<std::string, int> &keyMap, node **splayArray, node **root);
extern void outputJSON(const char fileName[], std::unordered_map<int, std::string> &invKeyMap, node *root);

/* unit test */
extern void treeLoaderUnitTest(const char tree_input_file[]);



#endif
/******************************************************************************* 
--------------------------------- END OF FILE ----------------------------------
*******************************************************************************/