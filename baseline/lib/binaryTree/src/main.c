/******************************************************************************* 
------------------------------------- INFO -------------------------------------
*******************************************************************************/
/**
 * @file main.c
 * @author Mitchell Young (mgyoung@ncsu.edu)
 * @brief Runs unit tests for generating binary trees.
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

#include "types.h"
#include "binaryTree.h"
#include "binaryTreeGen.h"
#include "util.h"


#define	TEST_1_N		5
#define	TEST_1_SAMPLES	1000000

#define	TEST_2_N		8

#define	TEST_3_N		25

#define	TEST_4_N		25

#define TEST_5_DEPTH	4


/******************************************************************************* 
------------------------------- HELPER FUNCTIONS -------------------------------
*******************************************************************************/
bool invTabIsEqual(int *tab1, int N1, int *tab2, int N2)
{
	if (N1 != N2) return false;

	int i;
	for (i=0; i<N1; i++, tab1++, tab2++)
	{
		if (*tab1 != *tab2) return false;
	}
	return true;
}

void assignTab(int *invTabSet, int N, int *tabID, int depth, int prev)
{
	if (depth >= N)
	{
		(*tabID)++;
	}
	else
	{
		int curr, index, start;
		for (curr=0; curr<=prev+1; curr++)
		{	
			start = *tabID;
			assignTab(invTabSet, N, tabID, depth+1, curr);
			for (index=(start*N + depth); start<*tabID; start++, index+=N)
			{
				invTabSet[index] = curr;
			}
		}
	}

}

void genInvTabSet(int *invTabSet, int N)
{
	int tabID = 0;
	assignTab(invTabSet, N, &tabID, 0, -1);
}

void updateSums(int *invTable, int *invTabSet, int *tabSums, int N, int C)
{
	int i;
	for (i=0; i<C; i++)
	{
		if (invTabIsEqual(invTable, N, invTabSet, N))
		{
			tabSums[i]++;
			return;
		}
		else
		{
			invTabSet += N;
		}
	}
}


/******************************************************************************* 
------------------------------------- MAIN -------------------------------------
*******************************************************************************/
int main(int argc, char *argv[])
{
	/* ---------------------------------------------------------------------- */
	printf("\n");
	printf("###############################################################################\n");
	printf("########################### Binary Tree Unit Tests ############################\n");
	printf("###############################################################################\n");
	printf("\n");


	/* ---------------------------------------------------------------------- */
	printf("\n");
	printf("=========================================================\n");
	printf("        Test 1: Random Inversion Table Correctness       \n");
	printf("=========================================================\n");
	printf("\n");

	int C = catalan(TEST_1_N);

	int *invTable = (int *) malloc(TEST_1_N * sizeof(int));
	int *invTabSet = (int *) malloc(C * TEST_1_N * sizeof(int));
	int *tabSums = (int *) malloc(C * sizeof(int));

	init_genrand64(time(0));

	int N, i, total, *curr;
	double perc;
	for (N=1; N<=TEST_1_N; N++)
	{
		C = catalan(N);
		genInvTabSet(invTabSet, N);
		for (i=0; i<C; i++)	{ tabSums[i] = 0; }

		printf("N = %d , C = %d , Samples = %d \n", N, C, TEST_1_SAMPLES);
		printf("************************************\n");

		for (i=0; i<TEST_1_SAMPLES; i++)
		{
			genInversionTable(invTable, N);
			updateSums(invTable, invTabSet, tabSums, N, C);
		}

		total = 0;
		curr = invTabSet;
		for (i=0; i<C; i++)
		{
			total += tabSums[i];
			perc = ((double) tabSums[i]/TEST_1_SAMPLES * 100);
			printInvTab(curr, N, false);
			printf(" %8d = %4.2f %% \n", tabSums[i], perc);
			curr += N;
		}
		perc = ((double) total/TEST_1_SAMPLES * 100);
		printf("Total %8d = %4.2f %% \n", total, ((double) total/TEST_1_SAMPLES * 100));
		printf("\n");
	}

	free(invTable);
	free(invTabSet);
	free(tabSums);


	/* ---------------------------------------------------------------------- */
	printf("\n");
	printf("=========================================================\n");
	printf("     Test 2: Inversion Table Translation Validation      \n");
	printf("=========================================================\n");
	printf("\n");

	printf("Validation Inversion Table: N = %d\n", TEST_2_N);
	printf("************************************\n");
	invTable = (int *) malloc(TEST_2_N * sizeof(int));
	invTable[0] = 0;
	invTable[1] = 1;
	invTable[2] = 2;
	invTable[3] = 2;
	invTable[4] = 1;
	invTable[5] = 0;
	invTable[6] = 1;
	invTable[7] = 1;
	printInvTab(invTable, TEST_2_N, false);

	printf("Correct Binary Tree: N = %d\n", TEST_2_N);
	printf("************************************\n");
	Tree valTree[TEST_2_N];
	valTree[0].id = 0;  
	// valTree[0].val = 0;  
	valTree[0].left = &(valTree[1]); 
	valTree[0].right = &(valTree[5]); 
	valTree[1].id = 1;  
	// valTree[1].val = 1;  
	valTree[1].left = &(valTree[2]); 
	valTree[1].right = &(valTree[4]); 
	valTree[2].id = 2;  
	// valTree[2].val = 2;  
	valTree[2].left = NULL; 
	valTree[2].right = &(valTree[3]);; 
	valTree[3].id = 3;  
	// valTree[3].val = 3;  
	valTree[3].left = NULL; 
	valTree[3].right = NULL; 
	valTree[4].id = 4;  
	// valTree[4].val = 4;
	valTree[4].left = NULL; 
	valTree[4].right = NULL;
	valTree[5].id = 5;  
	// valTree[5].val = 5;  
	valTree[5].left = &(valTree[6]); 
	valTree[5].right = NULL; 
	valTree[6].id = 6;  
	// valTree[6].val = 6;  
	valTree[6].left = NULL; 
	valTree[6].right = &(valTree[7]); 
	valTree[7].id = 7;  
	// valTree[7].val = 7;  
	valTree[7].left = NULL; 
	valTree[7].right = NULL; 
	print_ascii_tree(&(valTree[0]));
	printf("\n");

	printf("Generated Binary Tree: N = %d\n", TEST_2_N);
	printf("************************************\n");
	Tree *btNodeArray = (Tree *) malloc(TEST_2_N * sizeof(Tree));
	ITNode *itNodeArray = (ITNode *) malloc(TEST_2_N * sizeof(ITNode));
	Tree *currentBT = btNodeArray;
	ITNode *currentIT = itNodeArray;
	for (i=0; i<TEST_2_N; i++, currentBT++, currentIT++)
	{
		initTree(currentBT);
		initITNode(currentIT);
	}

	Tree *binaryTree = preOrderIT2BT(invTable, btNodeArray, itNodeArray, TEST_2_N);

	print_ascii_tree(binaryTree);
	printf("\n");

	free(invTable);
	free(itNodeArray);
	free(btNodeArray);	


	/* ---------------------------------------------------------------------- */
	printf("\n");
	printf("=========================================================\n");
	printf("    Test 3: Inversion Table & Binary Tree Generation     \n");
	printf("=========================================================\n");
	printf("\n");

	printf("Generated Inversion Table: N = %d\n", TEST_3_N);
	printf("************************************\n");
	invTable = (int *) malloc(TEST_3_N * sizeof(int));
	btNodeArray = (Tree *) malloc(TEST_3_N * sizeof(Tree));
	itNodeArray = (ITNode *) malloc(TEST_3_N * sizeof(ITNode));
	currentBT = btNodeArray;
	currentIT = itNodeArray;
	for (i=0; i<TEST_3_N; i++, currentBT++, currentIT++)
	{
		initTree(currentBT);
		initITNode(currentIT);
	}
	binaryTree = genRandomTree(invTable, btNodeArray, itNodeArray, TEST_3_N);
	printInvTab(invTable, TEST_3_N, false);

	printf("Generated Binary Tree: N = %d\n", TEST_3_N);
	printf("************************************\n");
	print_ascii_tree(binaryTree);
	printf("\n");

	free(invTable);
	free(itNodeArray);
	free(btNodeArray);	


	/* ---------------------------------------------------------------------- */
	printf("\n");
	printf("=========================================================\n");
	printf("      Test 4: Inversion Table Direct to Output       \n");
	printf("=========================================================\n");
	printf("\n");
	
	genTree2StdOut(TEST_3_N);
	printf("\n");	


	/* ---------------------------------------------------------------------- */
	printf("\n");
	printf("=========================================================\n");
	printf("         Test 5: Balanced Binary Tree Generation         \n");
	printf("=========================================================\n");
	printf("\n");

	N = (1<<(TEST_5_DEPTH+1))-1;
	invTable = (int *) malloc(N * sizeof(int));
	btNodeArray = (Tree *) malloc(N * sizeof(Tree));
	itNodeArray = (ITNode *) malloc(N * sizeof(ITNode));

	int depth;
	for (depth=0; depth<=TEST_5_DEPTH; depth++)
	{
		N = (1<<(depth+1))-1;
		currentBT = btNodeArray;
		currentIT = itNodeArray;
		for (i=0; i<N; i++, currentBT++, currentIT++)
		{
			initTree(currentBT);
			initITNode(currentIT);
		}

		printf("Balanced Binary Tree: depth = %d , N = %d\n", depth, N);
		printf("*********************************************\n");
		binaryTree = genBalancedTree(invTable, btNodeArray, itNodeArray, depth);
		printInvTab(invTable, N, false);
		print_ascii_tree(binaryTree);
		printf("\n");
	}

	free(invTable);
	free(itNodeArray);
	free(btNodeArray);	



	/* ---------------------------------------------------------------------- */
	printf("\n");
	printf("=========================================================\n");
	printf("          Test 6: Tree Generation Measurements           \n");
	printf("=========================================================\n");
	printf("\n");

	
	/* ---------------------------------------------------------------------- */
}


/******************************************************************************* 
--------------------------------- END OF FILE ----------------------------------
*******************************************************************************/