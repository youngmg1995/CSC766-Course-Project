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
#include <time.h>

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
	node->left		= NULL;
	node->right		= NULL;
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
		printf("\n");
	}
	printf("\n");
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

Tree * preOrderIT2BT(int *invTable, Tree *btNodeArray, ITNode *itNodeArray, int N)
{
	ITNode *currentIT, *prevIT;
	Tree *currentBT, *prevBT, *root;

	currentBT 			= btNodeArray;
	currentBT->id		= 0;
	currentBT->data		= NULL;
	root 				= currentBT;

	currentIT 			= itNodeArray;
	currentIT->val		= *invTable;
	currentIT->tree		= currentBT;
	currentIT->parent	= NULL;
	
	int i, j;
	for (i=1; i<N; i++)
	{
		invTable++;
		prevIT = currentIT;
		prevBT = currentBT;

		btNodeArray++;
		currentBT 			= btNodeArray;
		currentBT->id		= i;
		currentBT->data		= NULL;

		itNodeArray++;
		currentIT 			= itNodeArray;
		currentIT->val		= *invTable;
		currentIT->tree		= currentBT;
		currentIT->parent	= NULL;

		// printf("%d %d\n", i, *invTable);
		// printf("%d %d %d %d\n", i, prevIT->val, prevIT->tree->id, prevIT->tree->val);

		if (currentIT->val > prevIT->val)
		{
			// printf("Moving Left\n");
			// move left
			prevBT->left = currentBT;
			

			prevIT->left = currentIT;
			currentIT->parent = prevIT;
		}
		else 
		{
			// backtrack
			while (currentIT->val < prevIT->val) 
			{
				// printf("Moving Up\n");
				prevIT = prevIT->parent;
			};
			// printf("Moving Right\n");
			
			prevIT->tree->right = currentBT;
			
			prevIT->right = currentIT;
			currentIT->parent = prevIT;
		}
		// printf("%d Prev: %d %d , Curr: %d %d\n", i, prevBT->id, prevBT->val, currentBT->id, currentBT->val);
	}

	return root;
}


/******************************************************************************* 
------------------------------- PRIMARY EXPORTS --------------------------------
*******************************************************************************/

Tree * genRandomTree(int *invTable, Tree *btNodeArray, ITNode *itNodeArray, int N)
{
	genInversionTable(invTable, N);
	return preOrderIT2BT(invTable, btNodeArray, itNodeArray, N);
}

Tree * genBalancedTree(int *invTable, Tree *btNodeArray, ITNode *itNodeArray, int depth)
{
	genBalancedIT(invTable, depth);
	return preOrderIT2BT(invTable, btNodeArray, itNodeArray, (1<<(depth+1))-1);
}

// Tree * genTree(int *invTable, Tree *btNodeArray, ITNode *itNodeArray, int N, bool isBalanced)
// {
// 	if (isBalanced)
// 	{
		
// 	}
// 	else
// 	{
// 		genInversionTable(invTable, N);
// 		return preOrderIT2BT(invTable, btNodeArray, itNodeArray, N);
// 	}
// }

/******************************************************************************* 
--------------------------------- END OF FILE ----------------------------------
*******************************************************************************/