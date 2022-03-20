/******************************************************************************* 
------------------------------------- INFO -------------------------------------
*******************************************************************************/
/**
 * @file traversal.c
 * @author Mitchell Young (mgyoung@ncsu.edu)
 * @brief Defines functions for traversing binary trees.
 * @version 0.1
 * @date 2022-03-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */


/******************************************************************************* 
------------------------------- IMPORTS & PARAMS -------------------------------
*******************************************************************************/
#include <stddef.h>

#include "types.h"


/******************************************************************************* 
------------------------------- HELPER FUNCTIONS -------------------------------
*******************************************************************************/



/******************************************************************************* 
------------------------------- BASIC TRAVERSALS -------------------------------
*******************************************************************************/
void preOrder(Tree *root)
{
	if (root != NULL)
	{	
		// do something here
		preOrder(root->left);
		preOrder(root->right);
	}
}

void inOrder(Tree *root)
{
	if (root != NULL)
	{	
		inOrder(root->left);
		// do something here
		inOrder(root->right);
	}
}

void postOrder(Tree *root)
{
	if (root != NULL)
	{	
		postOrder(root->left);
		postOrder(root->right);
		// do something here
	}
}

// void levelOrder(Tree *root)
// {
// }

void contiguousOrder(Tree *treeArray, int N)
{
	int i;
	for (i=0; i<N; i++, treeArray++)
	{
		// do something
	}
}



/******************************************************************************* 
----------------------------- CALLBACK TRAVERSALS ------------------------------
*******************************************************************************/
void preOrderCB(Tree *root, TreeCallback callback)
{
	if (root != NULL)
	{	
		callback(root);
		preOrderCB(root->left, callback);
		preOrderCB(root->right, callback);
	}
}

void inOrderCB(Tree *root, TreeCallback callback)
{
	if (root != NULL)
	{	
		inOrderCB(root->left, callback);
		callback(root);
		inOrderCB(root->right, callback);
	}
}

void postOrderCB(Tree *root, TreeCallback callback)
{
	if (root != NULL)
	{	
		postOrderCB(root->left, callback);
		postOrderCB(root->right, callback);
		callback(root);
	}
}

// void levelOrder(Tree *root)
// {
// }

void contiguousOrderCB(Tree *treeArray, int N, TreeCallback callback)
{
	int i;
	for (i=0; i<N; i++, treeArray++)
	{
		callback(treeArray);
	}
}


/******************************************************************************* 
--------------------------------- END OF FILE ----------------------------------
*******************************************************************************/