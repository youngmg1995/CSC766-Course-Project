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


#define tiny_tree_file ".data/inputs/tiny_tree.json"
#define small_tree_file ".data/inputs/small_tree.json"
#define big_tree_file ".data/inputs/big_tree.json"
#define output_og_tree_file ".data/outputs/output_og_tree.json"
#define compressed_output_og_tree_file ".data/outputs/compressed_og_tree.json"
#define output_bu_tree_file ".data/outputs/output_bu_tree.json"
#define output_td_tree_file ".data/outputs/output_td_tree.json"


#define tiny_tree_file_compressed ".data/compressed_inputs/tiny_tree.json"
#define small_tree_file_compressed ".data/compressed_inputs/small_tree.json"
#define big_tree_file_compressed ".data/compressed_inputs/big_tree.json"


/******************************************************************************* 
--------------------------------- DECLARATIONS ---------------------------------
*******************************************************************************/

/* functions for loading and outputting tree */
extern int loadJSON(const char fileName[], std::unordered_map<std::string, int> &keyMap, node **splayArray, node **root);
extern int loadCompressedJSON(const char fileName[], node **splayArray, node **root);
extern void outputJSON(const char fileName[], std::unordered_map<int, std::string> &invKeyMap, node *root);
extern void outputCompressedJSON(const char fileName[], node *root);

/* unit test */
extern void treeLoaderUnitTest(const char tree_input_file[]);



#endif
/******************************************************************************* 
--------------------------------- END OF FILE ----------------------------------
*******************************************************************************/