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
#include <string.h>
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
void printUnitTestMsg(int *testNum, const char message[])
{
	const char delimiter[] = "================================================================================";
	int n = strlen(delimiter);
	int m = strlen(message);

	int p = (n-m-8)/2;
	p = p <= 0 ? 0 : p;
	int q = p <= 0 ? 0 : n - m - p - 8;

	char *spacer1 = (char *) malloc((p+1) *sizeof(char));
	int i;
	for (i=0; i<p; i++)
	{
		spacer1[i] = ' ';
	}
	spacer1[p] = '\0';

	char *spacer2 = (char *) malloc((q+1) *sizeof(char));
	for (i=0; i<q; i++)
	{
		spacer2[i] = ' ';
	}
	spacer2[q] = '\0';


	printf("\n");
	printf("%s\n", delimiter);
	printf("%s\n", delimiter);
	printf("%sTest %d: %s%s\n", spacer1, *testNum, message, spacer2);
	printf("%s\n", delimiter);
	printf("%s\n", delimiter);
	printf("\n");

	free(spacer1);
	free(spacer2);

	(*testNum)++;
}

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
---------------------------------- UNIT TESTS ----------------------------------
*******************************************************************************/
void validateBST()
{
	Tree *bstRoot = NULL;
	Tree *tmp;


	printf("Inserting into BST: id = %d\n", 4);
	printf("************************************\n");
	bstRoot = insert(4, NULL, bstRoot);
	print_ascii_tree(bstRoot);
	printf("\n");

	printf("Inserting into BST: id = %d\n", 23);
	printf("************************************\n");
	bstRoot = insert(23, NULL, bstRoot);
	print_ascii_tree(bstRoot);
	printf("\n");

	printf("Inserting into BST: id = %d\n", 53);
	printf("************************************\n");
	bstRoot = insert(53, NULL, bstRoot);
	print_ascii_tree(bstRoot);
	printf("\n");

	printf("Inserting into BST: id = %d\n", 10);
	printf("************************************\n");
	bstRoot = insert(10, NULL, bstRoot);
	print_ascii_tree(bstRoot);
	printf("\n");

	printf("Inserting into BST: id = %d\n", 8);
	printf("************************************\n");
	bstRoot = insert(8, NULL, bstRoot);
	print_ascii_tree(bstRoot);
	printf("\n");

	printf("Inserting into BST: id = %d\n", 1);
	printf("************************************\n");
	bstRoot = insert(1, NULL, bstRoot);
	print_ascii_tree(bstRoot);
	printf("\n");

	printf("Inserting into BST: id = %d\n", 30);
	printf("************************************\n");
	bstRoot = insert(30, NULL, bstRoot);
	print_ascii_tree(bstRoot);
	printf("\n");

	printf("Find MIN in BST\n");
	printf("************************************\n");
	tmp = find_min(bstRoot);
	printf("Min ID = %d\n", tmp->id);
	printf("\n");

	printf("Find MAX in BST\n");
	printf("************************************\n");
	tmp = find_max(bstRoot);
	printf("Max ID = %d\n", tmp->id);
	printf("\n");

	printf("Find Specific ID in BST: id = %d\n", 10);
	printf("************************************\n");
	tmp = find(10, bstRoot);
	printf("Located ID = %d\n", tmp->id);
	printf("\n");

	printf("Deleting from BST: id = %d\n", 4);
	printf("************************************\n");
	bstRoot = delete(4, bstRoot, NULL);
	print_ascii_tree(bstRoot);
	printf("\n");

	printf("Deleting from BST: id = %d\n", 53);
	printf("************************************\n");
	bstRoot = delete(53, bstRoot, NULL);
	print_ascii_tree(bstRoot);
	printf("\n");

	printf("Deleting/Freeing BST\n");
	printf("************************************\n");
	bstRoot = make_empty(bstRoot);
	print_ascii_tree(bstRoot);
	printf("\n");

}


void validateInvTabGen()
{
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
			printf("%8d = %4.2f %% \n", tabSums[i], perc);
			curr += N;
		}
		perc = ((double) total/TEST_1_SAMPLES * 100);
		printf("Total %8d = %4.2f %% \n", total, ((double) total/TEST_1_SAMPLES * 100));
		printf("\n");
	}

	free(invTable);
	free(invTabSet);
	free(tabSums);
}

void validateInvTabTanslation()
{
	int *invTable;
	Tree *binaryTree, *btNodeArray;

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
	printf("\n\n");

	printf("Correct Binary Tree: N = %d\n", TEST_2_N);
	printf("************************************\n");
	Tree valTree[TEST_2_N];
	valTree[0].id = 0;  
	valTree[0].left = &(valTree[1]); 
	valTree[0].right = &(valTree[5]); 
	valTree[1].id = 1;  
	valTree[1].left = &(valTree[2]); 
	valTree[1].right = &(valTree[4]); 
	valTree[2].id = 2;  
	valTree[2].left = NULL; 
	valTree[2].right = &(valTree[3]);; 
	valTree[3].id = 3;  
	valTree[3].left = NULL; 
	valTree[3].right = NULL; 
	valTree[4].id = 4;  
	valTree[4].left = NULL; 
	valTree[4].right = NULL;
	valTree[5].id = 5;  
	valTree[5].left = &(valTree[6]); 
	valTree[5].right = NULL; 
	valTree[6].id = 6;  
	valTree[6].left = NULL; 
	valTree[6].right = &(valTree[7]); 
	valTree[7].id = 7;  
	valTree[7].left = NULL; 
	valTree[7].right = NULL; 
	print_ascii_tree(&(valTree[0]));
	printf("\n");

	printf("Translated Binary Tree: N = %d\n", TEST_2_N);
	printf("************************************\n");
	binaryTree = invTab2BT(invTable, TEST_2_N);
	print_ascii_tree(binaryTree);
	printf("\n");

	printf("Translated Contiguous Binary Tree: N = %d\n", TEST_2_N);
	printf("************************************\n");
	btNodeArray = (Tree *) malloc(TEST_2_N * sizeof(Tree));
	binaryTree = make_empty(binaryTree);
	binaryTree = invTab2ContBT(invTable, btNodeArray, TEST_2_N);
	print_ascii_tree(binaryTree);
	printf("\n");

	printf("Translated Binary Search Tree: N = %d\n", TEST_2_N);
	printf("************************************\n");
	convert2BST(binaryTree);
	print_ascii_tree(binaryTree);
	printf("\n");

	free(invTable);
	free(btNodeArray);	
}

void exampleInvTabTreeGen()
{
	int *invTable;
	Tree *binaryTree, *btNodeArray;

	printf("Generated Binary Tree: N = %d\n", TEST_3_N);
	printf("************************************\n");
	invTable = (int *) malloc(TEST_3_N * sizeof(int));
	binaryTree = genRandomTree(invTable, TEST_3_N, false);
	printInvTab(invTable, TEST_3_N, false);
	printf("\n\n");
	print_ascii_tree(binaryTree);
	printf("\n");

	printf("Generated Contiguos Binary Tree: N = %d\n", TEST_3_N);
	printf("***************************************\n");
	btNodeArray = (Tree *) malloc(TEST_3_N * sizeof(Tree));
	binaryTree = make_empty(binaryTree);
	binaryTree = genContRandomTree(invTable, btNodeArray, TEST_3_N, false);
	printInvTab(invTable, TEST_3_N, false);
	printf("\n\n");
	print_ascii_tree(binaryTree);
	printf("\n");

	printf("Generated Binary Search Tree: N = %d\n", TEST_3_N);
	printf("************************************\n");
	binaryTree = genRandomTree(invTable, TEST_3_N, true);
	printInvTab(invTable, TEST_3_N, false);
	printf("\n\n");
	print_ascii_tree(binaryTree);
	printf("\n");

	printf("Generated Contiguos Binary Search Tree: N = %d\n", TEST_3_N);
	printf("**********************************************\n");
	binaryTree = make_empty(binaryTree);
	binaryTree = genContRandomTree(invTable, btNodeArray, TEST_3_N, true);
	printInvTab(invTable, TEST_3_N, false);
	printf("\n\n");
	print_ascii_tree(binaryTree);
	printf("\n");

	free(invTable);
	free(btNodeArray);	
}

void exampleInvTab2Output()
{
	genTree2StdOut(TEST_3_N);
	printf("\n");	
}

void validateBalancedTreeGen()
{
	int *invTable, N, depth;
	Tree *binaryTree, *btNodeArray;

	N = (1<<(TEST_5_DEPTH+1))-1;
	invTable = (int *) malloc(N * sizeof(int));
	btNodeArray = (Tree *) malloc(N * sizeof(Tree));

	for (depth=0; depth<=TEST_5_DEPTH; depth++)
	{
		N = (1<<(depth+1))-1;

		printf("Balanced Binary Tree: depth = %d , N = %d\n", depth, N);
		printf("*********************************************\n");
		binaryTree = genContBalancedTree(invTable, btNodeArray, depth, false);
		printInvTab(invTable, N, false);
		printf("\n\n");
		print_ascii_tree(binaryTree);
		printf("\n");

		printf("Balanced Binary Search Tree: depth = %d , N = %d\n", depth, N);
		printf("************************************************\n");
		binaryTree = genContBalancedTree(invTable, btNodeArray, depth, true);
		printInvTab(invTable, N, false);
		printf("\n\n");
		print_ascii_tree(binaryTree);
		printf("\n");
	}

	free(invTable);
	free(btNodeArray);	
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

	int testNum = 1;


	/* ---------------------------------------------------------------------- */
	
	printUnitTestMsg(&testNum, "Validate Binary Search Tree Structure");
	validateBST();

	/* ---------------------------------------------------------------------- */
	
	printUnitTestMsg(&testNum, "Validate Inversion Table Gen. Correctness");
	validateInvTabGen();

	/* ---------------------------------------------------------------------- */
	
	printUnitTestMsg(&testNum, "Example Inversion Table Direct to Output");
	exampleInvTab2Output();

	/* ---------------------------------------------------------------------- */
	
	printUnitTestMsg(&testNum, "Validate Inversion Table Translation Correctness");
	validateInvTabTanslation();

	/* ---------------------------------------------------------------------- */
	
	printUnitTestMsg(&testNum, "Example Random Binary Tree Generation");
	exampleInvTabTreeGen();

	/* ---------------------------------------------------------------------- */
	
	printUnitTestMsg(&testNum, "Example Balanced Binary Tree Generation ");
	validateBalancedTreeGen();

	/* ---------------------------------------------------------------------- */

	return (0);
}


/******************************************************************************* 
--------------------------------- END OF FILE ----------------------------------
*******************************************************************************/