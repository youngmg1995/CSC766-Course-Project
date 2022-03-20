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
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "binaryTree.h"
#include "util.h"


/******************************************************************************* 
------------------------------- HELPER FUNCTIONS -------------------------------
*******************************************************************************/
void initITNode(ITNode *node)
{
	node->val		= 0;
	node->tree		= NULL;
	node->parent	= NULL;
}

double getP(int N, int i, int j)
{
	return ( (double) (i+3)*(N-j) ) / ( (i+2)*(2*(N-j)+i+1) );
}

double getQ(int N, int j, int k)
{
	return  ( (double) (k+1)*(N-j+k+1) ) / ( (k+2)*(2*(N-j)+k-1) );
}

int assign(int N, int i, int j)
{
	int k = i + 1;
	double P = getP(N, i, j);
	double sum = P;
	double x = genrand64_real2();
	while ((1-x) > sum)
	{
		P *= getQ(N, j, k);
		sum += P;
		k--;
	}
	return k;
}

void genInversionTable(int *invTable, int N)
{
	*invTable = 0;
	int i, j;
	for (j=1; j < N; j++)
	{
		i = *invTable;
		invTable++;
		*invTable = assign(N, i, j);
	}
}

void genInversionTableOptimized(int *invTable, int N, TreeInfo *treeInfo)
{
	treeInfo->size 		= 1;
	treeInfo->depth		= 0;
	treeInfo->leaves	= 1;

	*invTable = 0;
	int i, depth;
	for (depth=0; treeInfo->size < N; (treeInfo->size)++)
	{
		i = *invTable;
		invTable++;
		*invTable = assign(N, i, treeInfo->size);

		if (*invTable >= i)
		{
			depth++;
			if (depth > treeInfo->depth)
			{
				treeInfo->depth = depth;
			}
		}
		else
		{
			(treeInfo->leaves)++;
			depth -= (i - *invTable - 1);
		}
	}
}

void genBalancedIT(int *invTable, int depth)
{
	*invTable = 0;
	if (depth > 0)
	{
		int *left = invTable + 1;
		int *right = invTable + (1<<depth);
		genBalancedIT(right, depth-1);
		int i;
		for (i=0; i<((1<<depth)-1); i++, left++, right++)
		{
			*left = *right + 1;
		}
	}
}

void printInvTab(int *invTable, int N, bool vert)
{	
	int i;
	if (vert)
	{
		for (i=0; i<N; i++, invTable++)
		{	
			printf("%d\n", *invTable);
		}
	}
	else
	{
		for (i=0; i<N; i++, invTable++)
		{	
			printf("%d ", *invTable);
		}
		// printf("\n");
	}
	// printf("\n");
}

void genTree2StdOut(int N)
{
	printf("%d\n", N);

	int i, j;
	printf("%d\n", 0);
	for (j=1, i=0; j < N; j++)
	{
		i = assign(N, i, j);
		printf("%d\n", i);
	}
}

Tree * invTab2BT(int *invTable, int N)
{
	ITNode *itNodeArray = (ITNode *) malloc(N * sizeof(ITNode));
	Tree *root = (Tree *) malloc(sizeof(Tree));

	ITNode *currentIT, *prevIT;
	Tree *currentBT, *prevBT;

	currentBT 			= root;
	currentBT->id		= 0;
	currentBT->data		= NULL;
	currentBT->left		= NULL;
	currentBT->right	= NULL;
	
	currentIT 			= itNodeArray;
	currentIT->val		= *invTable;
	currentIT->tree		= currentBT;
	currentIT->parent	= NULL;
	
	int i;
	for (i=1; i<N; i++)
	{
		invTable++;
		prevIT = currentIT;
		prevBT = currentBT;

		currentBT 			= (Tree *) malloc(sizeof(Tree));
		currentBT->id		= i;
		currentBT->data		= NULL;
		currentBT->left		= NULL;
		currentBT->right	= NULL;

		currentIT++;
		currentIT->val		= *invTable;
		currentIT->tree		= currentBT;
		currentIT->parent	= NULL;

		if (currentIT->val > prevIT->val)
		{
			// printf("Moving Left\n");
			prevBT->left = currentBT;
			currentIT->parent = prevIT;
		}
		else 
		{
			while (currentIT->val < prevIT->val) 
			{
				// printf("Moving Up\n");
				prevIT = prevIT->parent;
			};
			// printf("Moving Right\n");
			prevIT->tree->right = currentBT;
			currentIT->parent = prevIT;
		}
	}

	free(itNodeArray);

	return root;
}

Tree * invTab2ContBT(int *invTable, Tree *btNodeArray, int N)
{
	ITNode *itNodeArray = (ITNode *) malloc(N * sizeof(ITNode));
	ITNode *currentIT, *prevIT;
	Tree *currentBT, *prevBT, *root;

	currentBT 			= btNodeArray;
	currentBT->id		= 0;
	currentBT->data		= NULL;
	currentBT->left		= NULL;
	currentBT->right	= NULL;
	root 				= currentBT;

	currentIT 			= itNodeArray;
	currentIT->val		= *invTable;
	currentIT->tree		= currentBT;
	currentIT->parent	= NULL;
	
	int i;
	for (i=1; i<N; i++)
	{
		invTable++;
		prevIT = currentIT;
		prevBT = currentBT;

		currentBT++;
		currentBT->id		= i;
		currentBT->data		= NULL;
		currentBT->left		= NULL;
		currentBT->right	= NULL;

		currentIT++;
		currentIT->val		= *invTable;
		currentIT->tree		= currentBT;
		currentIT->parent	= NULL;

		if (currentIT->val > prevIT->val)
		{
			// printf("Moving Left\n");
			prevBT->left = currentBT;
			currentIT->parent = prevIT;
		}
		else 
		{
			while (currentIT->val < prevIT->val) 
			{
				// printf("Moving Up\n");
				prevIT = prevIT->parent;
			};
			// printf("Moving Right\n");
			prevIT->tree->right = currentBT;
			currentIT->parent = prevIT;
		}
	}

	free(itNodeArray);

	return root;
}

Tree * invTab2BTOptimized(int *invTable, ITNode *itNodeArray, int N)
{
	Tree *root = (Tree *) malloc(sizeof(Tree));

	ITNode *currentIT, *prevIT;
	Tree *currentBT, *prevBT;

	currentBT 			= root;
	currentBT->id		= 0;
	currentBT->data		= NULL;
	currentBT->left		= NULL;
	currentBT->right	= NULL;
	
	currentIT 			= itNodeArray;
	currentIT->val		= *invTable;
	currentIT->tree		= currentBT;
	currentIT->parent	= NULL;
	
	int i;
	for (i=1; i<N; i++)
	{
		invTable++;
		prevIT = currentIT;
		prevBT = currentBT;

		currentBT 			= (Tree *) malloc(sizeof(Tree));
		currentBT->id		= i;
		currentBT->data		= NULL;
		currentBT->left		= NULL;
		currentBT->right	= NULL;

		currentIT++;
		currentIT->val		= *invTable;
		currentIT->tree		= currentBT;
		currentIT->parent	= NULL;

		if (currentIT->val > prevIT->val)
		{
			// printf("Moving Left\n");
			prevBT->left = currentBT;
			currentIT->parent = prevIT;
		}
		else 
		{
			while (currentIT->val < prevIT->val) 
			{
				// printf("Moving Up\n");
				prevIT = prevIT->parent;
			};
			// printf("Moving Right\n");
			prevIT->tree->right = currentBT;
			currentIT->parent = prevIT;
		}
	}

	return root;
}

Tree * invTab2ContBTOptimized(int *invTable, Tree *btNodeArray, ITNode *itNodeArray, int N)
{
	ITNode *currentIT, *prevIT;
	Tree *currentBT, *prevBT, *root;

	currentBT 			= btNodeArray;
	currentBT->id		= 0;
	currentBT->data		= NULL;
	currentBT->left		= NULL;
	currentBT->right	= NULL;
	root 				= currentBT;

	currentIT 			= itNodeArray;
	currentIT->val		= *invTable;
	currentIT->tree		= currentBT;
	currentIT->parent	= NULL;
	
	int i;
	for (i=1; i<N; i++)
	{
		invTable++;
		prevIT = currentIT;
		prevBT = currentBT;

		currentBT++;
		currentBT->id		= i;
		currentBT->data		= NULL;
		currentBT->left		= NULL;
		currentBT->right	= NULL;

		currentIT++;
		currentIT->val		= *invTable;
		currentIT->tree		= currentBT;
		currentIT->parent	= NULL;

		if (currentIT->val > prevIT->val)
		{
			// printf("Moving Left\n");
			prevBT->left = currentBT;
			currentIT->parent = prevIT;
		}
		else 
		{
			while (currentIT->val < prevIT->val) 
			{
				// printf("Moving Up\n");
				prevIT = prevIT->parent;
			};
			// printf("Moving Right\n");
			prevIT->tree->right = currentBT;
			currentIT->parent = prevIT;
		}
	}

	return root;
}

void bs2BST(Tree *root, int *id)
{
	if (root != NULL)
	{
		bs2BST(root->left, id);
		root->id = *id;
		(*id)++;
		bs2BST(root->right, id);
	}
}

void convert2BST(Tree *root)
{	
	int id = 0;
	bs2BST(root, &id);
}



/******************************************************************************* 
------------------------------- PRIMARY EXPORTS --------------------------------
*******************************************************************************/

/* -------------------------------------------------------------------------- */

/* exportable functions that don't require other types (i.e. ITNode) */
Tree * genRandomTree(int N, bool isBST)
{
	int *invTable = (int *) malloc(N * sizeof(int));
	genInversionTable(invTable, N);
	Tree *root = invTab2BT(invTable, N);
	free(invTable);
	if (isBST) convert2BST(root);
	return root;
}

Tree * genContRandomTree(Tree *btNodeArray, int N, bool isBST)
{
	int *invTable = (int *) malloc(N * sizeof(int));
	genInversionTable(invTable, N);	
	Tree *root = invTab2ContBT(invTable, btNodeArray, N);
	free(invTable);
	if (isBST) convert2BST(root);
	return root;
}

Tree * genBalancedTree(int depth, bool isBST)
{
	int N = (1<<(depth+1))-1;
	int *invTable = (int *) malloc(N * sizeof(int));
	genBalancedIT(invTable, depth);
	Tree *root = invTab2BT(invTable, N);
	free(invTable);
	if (isBST) convert2BST(root);
	return root;
}

Tree * genContBalancedTree(Tree *btNodeArray, int depth, bool isBST)
{
	int N = (1<<(depth+1))-1;
	int *invTable = (int *) malloc(N * sizeof(int));
	genBalancedIT(invTable, depth);
	Tree *root = invTab2ContBT(invTable, btNodeArray, N);
	free(invTable);
	if (isBST) convert2BST(root);
	return root;
}

/* -------------------------------------------------------------------------- */

/* optimized version that don't require memory allocation but require it be passed in (as itNodeArray) */
void genRandomTreeOptimized(int *invTable, ITNode *itNodeArray, int N, bool isBST, TreeInfo *treeInfo)
{
	treeInfo->size = N;
	genInversionTableOptimized(invTable, N, treeInfo);
	treeInfo->root = invTab2BTOptimized(invTable, itNodeArray, N);
	if (isBST) convert2BST(treeInfo->root);
}

void genContRandomTreeOptimized(int *invTable, Tree *btNodeArray, ITNode *itNodeArray, int N, bool isBST, TreeInfo *treeInfo)
{
	treeInfo->size = N;
	genInversionTableOptimized(invTable, N, treeInfo);	
	treeInfo->root = invTab2ContBTOptimized(invTable, btNodeArray, itNodeArray, N);
	if (isBST) convert2BST(treeInfo->root);
}

void genBalancedTreeOptimized(int *invTable, ITNode *itNodeArray, int depth, bool isBST, TreeInfo *treeInfo)
{
	treeInfo->size = (1<<(depth+1))-1;
	treeInfo->depth = depth;
	treeInfo->leaves = (1<<depth);
	genBalancedIT(invTable, depth);
	treeInfo->root = invTab2BTOptimized(invTable, itNodeArray, treeInfo->size);
	if (isBST) convert2BST(treeInfo->root);
}

void genContBalancedTreeOptimized(int *invTable, Tree *btNodeArray, ITNode *itNodeArray, int depth, bool isBST, TreeInfo *treeInfo)
{
	treeInfo->size = (1<<(depth+1))-1;
	treeInfo->depth = depth;
	treeInfo->leaves = (1<<depth);
	genBalancedIT(invTable, depth);
	treeInfo->root = invTab2ContBTOptimized(invTable, btNodeArray, itNodeArray, treeInfo->size);
	if (isBST) convert2BST(treeInfo->root);
}

/* -------------------------------------------------------------------------- */

/******************************************************************************* 
--------------------------------- END OF FILE ----------------------------------
*******************************************************************************/