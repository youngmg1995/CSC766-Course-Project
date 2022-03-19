/******************************************************************************* 
------------------------------------- INFO -------------------------------------
*******************************************************************************/
/**
 * @file binaryTreeGen.c
 * @author Mitchell Young (mgyoung@ncsu.edu)
 * @brief Defines functions for generating binary trees.
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
#include "binaryTree.h"


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
		preOrder(root->left);
		// do something here
		preOrder(root->right);
	}
}

void postOrder(Tree *root)
{
	if (root != NULL)
	{	
		preOrder(root->left);
		preOrder(root->right);
		// do something here
	}
}

// void levelOrder(Tree *root)
// {
// }

void orderedTraversal(Tree *treeArray, int N)
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
void preOrderCB(Tree *root, TreeCallBack callBack)
{
	if (root != NULL)
	{	
		callBack(root);
		preOrder(root->left);
		preOrder(root->right);
	}
}

void inOrderCB(Tree *root, TreeCallBack callBack)
{
	if (root != NULL)
	{	
		preOrder(root->left);
		callBack(root);
		preOrder(root->right);
	}
}

void postOrderCB(Tree *root, TreeCallBack callBack)
{
	if (root != NULL)
	{	
		preOrder(root->left);
		preOrder(root->right);
		callBack(root);
	}
}

// void levelOrder(Tree *root)
// {
// }

void orderedTraversalCB(Tree *treeArray, int N, TreeCallBack callBack)
{
	int i;
	for (i=0; i<N; i++, treeArray++)
	{
		callBack(treeArray);
	}
}


/******************************************************************************* 
--------------------------------- END OF FILE ----------------------------------
*******************************************************************************/