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

#define	TEST_N			4
#define	TEST_SAMPLES	100

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

void genInversionTable(int* invTable, int N)
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

bool invTabIsEqual(int* tab1, int N1, int* tab2, int N2)
{
	if (N1 != N2) return false;

	int i;
	for (i=0; i<N1; i++, tab1++, tab2++)
	{
		if (*tab1 != *tab2) return false;
	}
	return true;
}

// void assignTab(int* invTabSet, int N, int* tabID, int depth, int prev)
// {
// 	int curr, index;
// 	for (curr=0; curr<=prev+1; curr++)
// 	{
// 		index = (*tabID)*N + depth;
// 		invTabSet[index] = curr;
// 		if (depth < N-1)
// 		{
// 			assignTab(invTabSet, N, tabID, depth+1, curr);
// 		}
// 		(*tabID)++;
// 	}
// }

void assignTab(int* invTabSet, int N, int* tabID, int depth, int prev)
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

void genInvTabSet(int* invTabSet, int N)
{
	int tabID = 0;
	assignTab(invTabSet, N, &tabID, 1, 0);
}

void updateSums(int* invTable, int* invTabSet, int* tabSums, int N, int C)
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

void printInvTab(int* invTable, int N)
{
	int i;
	for (i=0; i<N; i++, invTable++)
	{
		printf("%d ", *invTable);
	}
}

void invTabUnitTest()
{
	printf("\n");
	printf("=========================================================\n");
	printf("            Random Inversion Table Unit Tests            \n");
	printf("=========================================================\n");
	printf("\n");

	int* invTable = (int*) malloc(TEST_N * sizeof(int));
	int* invTabSet = (int*) malloc(catalan(TEST_N) * TEST_N * sizeof(int));
	int* tabSums = (int*) malloc(TEST_N * sizeof(int));

	int i, j, *curr;
	// for (i=0; i<catalan(TEST_N); i++) { *(invTabSet + TEST_N*i) = 0; }
	for (i=0, curr=invTabSet; i<catalan(TEST_N); i++)
	{
		for (j=0; j<TEST_N; j++, curr++)
		{
			*curr = 0;
		}
	}

	init_genrand64(0);

	int N, C, total;
	for (N=1; N<=TEST_N; N++)
	{
		C = catalan(N);
		genInvTabSet(invTabSet, N);
		for (i=0; i<N; i++)	{ tabSums[i] = 0; }

		printf("Test %d: N = %d , C = %d , Samples = %d \n", N, N, C, TEST_SAMPLES);
		printf("*******************************************\n");

		for (i=0; i<TEST_SAMPLES; i++)
		{
			genInversionTable(invTable, N);
			updateSums(invTable, invTabSet, tabSums, N, C);
		}

		total = 0;
		for (i=0; i<C; i++)
		{	
			total += tabSums[i];
			printInvTab((invTable + N*i), N);
			printf("- %6d = %4.2f %% \n", tabSums[i], ((double) tabSums[i]/TEST_SAMPLES * 100));
		}
		printf("Total - %6d = %4.2f %% \n", total, ((double) total/TEST_SAMPLES * 100));
		printf("\n");
	}

	free(invTable);
	free(invTabSet);
	free(tabSums);
}


/******************************************************************************* 
------------------------------------- MAIN -------------------------------------
*******************************************************************************/
int main(int argc, char* argv[])
{
	invTabUnitTest();
}


/******************************************************************************* 
--------------------------------- END OF FILE ----------------------------------
*******************************************************************************/