/******************************************************************************* 
------------------------------------- INFO -------------------------------------
*******************************************************************************/
/**
 * @file traversal.cpp
 * @author Mitchell Young (mgyoung@ncsu.edu)
 * @brief Defines functions for traversing splay trees.
 * @version 0.1
 * @date 2022-04-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */


/******************************************************************************* 
------------------------------- IMPORTS & PARAMS -------------------------------
*******************************************************************************/
#include <stddef.h>

#include "types.h"
#include "util.h"


/******************************************************************************* 
------------------------------- HELPER FUNCTIONS -------------------------------
*******************************************************************************/



/******************************************************************************* 
------------------------------- BASIC TRAVERSALS -------------------------------
*******************************************************************************/
void splayTraversal(node *root)
{
	if (root != NULL)
	{	
		int tmp = root->key;
		root->key = (int) genrand64_real2()*8;
		root->key = tmp;
		splayTraversal(root->children);
		splayTraversal(root->left);
		splayTraversal(root->right);
	}
}

void splayTraversalCB(node *root, TraversalCallback callback)
{
	if (root != NULL)
	{	
		callback(root);
		splayTraversalCB(root->children, callback);
		splayTraversalCB(root->left, callback);
		splayTraversalCB(root->right, callback);
	}
}



/******************************************************************************* 
--------------------------------- END OF FILE ----------------------------------
*******************************************************************************/