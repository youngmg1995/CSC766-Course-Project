/******************************************************************************* 
------------------------------------- INFO -------------------------------------
*******************************************************************************/
/**
 * @file batches.cpp
 * @author Mitchell Young (mgyoung@ncsu.edu)
 * @brief Runs experiments on binary trees.
 * @version 0.1
 * @date 2022-03-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */


/******************************************************************************* 
------------------------------- IMPORTS & PARAMS -------------------------------
*******************************************************************************/
#include <stdbool.h>
#include <stdlib.h>
#include <iostream>
#include <unordered_map>

#include "types.h"
#include "splayTree.h"
#include "treeLoader.h"

#include "exp.h"
#include "timer.h"


/******************************************************************************* 
------------------------------- PRIMARY EXPORTS --------------------------------
*******************************************************************************/

/* -------------------------------------------------------------------------- */

void traversalBatch(
	const char tree_input_file[], const char treeType[], 
	int buTreeSize, int tdTreeSize,
	bool printResults, bool verbose
)
{
	int i;

    node *splayArray = NULL;
    node *original = NULL;

    std::unordered_map<std::string, int> keyMap;
    int treeSize = loadJSON(tree_input_file, keyMap, &splayArray, &original);

    std::unordered_map<int, std::string> invKeyMap;
    for (std::pair<std::string, int> element : keyMap)
    {
        invKeyMap[element.second] = element.first;
    }

	node *tmp;
	node *buNodeArray = (node *) malloc(buTreeSize * sizeof(node));


/* ---------------------------- Plain Traversal ----------------------------- */
	timeTraversal(original, true, false, treeType);
/* -------------------------------------------------------------------------- */


/* ----------------------- Transform With Mem. Alloc. ----------------------- */
	timeTransformMalloc(original, true, false, treeType);
/* -------------------------------------------------------------------------- */


/* --------------------- Transform Without Mem. Alloc. ---------------------- */
	for (i=0, tmp=buNodeArray; i<buTreeSize; i++, tmp++)
	{
		initNode(tmp);
	}
	timeTransformNoMalloc(original, buNodeArray, true, false, treeType);
/* -------------------------------------------------------------------------- */


/* ------------------ Cont. Transform Without Mem. Alloc. ------------------- */
	for (i=0, tmp=buNodeArray; i<buTreeSize; i++, tmp++)
	{
		initNode(tmp);
	}
	timeTransformCont(splayArray, treeSize, buNodeArray, true, false, treeType);
/* -------------------------------------------------------------------------- */


	free(splayArray);
	free(buNodeArray);
	invKeyMap.clear();
	keyMap.clear();
}

/* -------------------------------------------------------------------------- */

/******************************************************************************* 
--------------------------------- END OF FILE ----------------------------------
*******************************************************************************/