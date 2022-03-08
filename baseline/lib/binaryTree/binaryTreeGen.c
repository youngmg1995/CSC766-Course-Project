/******************************************************************************* 
------------------------------------- INFO -------------------------------------
*******************************************************************************/
/**
 * @file binaryTreeGen.c
 * @author Mitchell Young (mgyoung@ncsu.edu)
 * @brief 
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


#define	TEST_1_N		5
#define	TEST_1_SAMPLES	1000000

#define	TEST_2_N		25

#define	TEST_3_N1		100
#define	TEST_3_SAMPLES1	10
#define	TEST_3_N2		1000
#define	TEST_3_SAMPLES2	10
#define	TEST_3_N3		10000
#define	TEST_3_SAMPLES3	10


extern double genrand64_real2(void);
extern void init_genrand64(unsigned long long seed);



/******************************************************************************* 
-------------------------------- FUNCTION DEFS ---------------------------------
*******************************************************************************/
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

BTNode * preOrderIT2BT(int *invTable, BTNode *btNodeArray, ITNode *itNodeArray, int N)
{
	ITNode *currentIT, *prevIT;
	BTNode *currentBT, *prevBT;

	currentBT 			= itNodeArray;
	currentBT->id		= 0;
	currentBT->val		= 0;

	currentIT 			= itNodeArray;
	currentIT->val		= *invTable;
	currentIT->node		= currentBT;
	currentIT->parent	= NULL;
	
	int i, j;
	for (i=1; i<=N; i++)
	{
		invTable++;
		prevIT = currentIT;
		prevBT = currentBT;
		itNodeArray++;
		btNodeArray++;

		if (*invTable < *(invTable-1))
		{
			// move left
		}
		else if (*invTable < *(invTable-1))
		{
			// backtrack
		}
		else
		{
			// move right
		}
	}
}


/******************************************************************************* 
---------------------------------- UNIT TESTS ----------------------------------
*******************************************************************************/

int factorial(int x)
{
	int f = 1;
	while (x > 1)
	{
		f *= x;
		x--;
	}
	return f;
}

int catalan(int x)
{
	int xFact = factorial(x);
	return factorial(2*x) / ((x+1)*xFact*xFact);
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

void printInvTab(int *invTable, int N)
{
	int i;
	for (i=0; i<N; i++, invTable++)
	{
		printf("%d ", *invTable);
	}
}

void invTabUnitTest()
{
	/* ---------------------------------------------------------------------- */
	printf("\n");
	printf("###############################################################################\n");
	printf("###################### Binary Tree Generation Unit Tests ######################\n");
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

		printf("N = %d , C = %d , Samples = %d \n", N, N, C, TEST_1_SAMPLES);
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
			printInvTab(curr, N);
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
	printf("          Test 2: Example Inversion TableOutput          \n");
	printf("=========================================================\n");
	printf("\n");
	
	genTree2StdOut(TEST_2_N);
	printf("\n");


	/* ---------------------------------------------------------------------- */
	printf("\n");
	printf("=========================================================\n");
	printf("          Test 3: Tree Generation Measurements           \n");
	printf("=========================================================\n");
	printf("\n");

	
	/* ---------------------------------------------------------------------- */
}


/******************************************************************************* 
------------------------------------- MAIN -------------------------------------
*******************************************************************************/
int main(int argc, char *argv[])
{
	invTabUnitTest();
}


/******************************************************************************* 
--------------------------------- END OF FILE ----------------------------------
*******************************************************************************/