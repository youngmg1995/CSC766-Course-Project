/******************************************************************************* 
------------------------------------- INFO -------------------------------------
*******************************************************************************/
/**
 * @file binaryTree.c
 * @author Mitchell Young (mgyoung@ncsu.edu)
 * @brief Defines basic methods for manipulating binary trees.
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

#include "types.h"



/******************************************************************************* 
-------------------------------- FUNCTION DEFS ---------------------------------
*******************************************************************************/
void initTQ(TreeQueue *tq, int capacity)
{
	tq->capacity	= capacity;
	tq->size 	= 0;
	tq->front 	= 0;
	tq->back 	= 0;
	tq->queue 	= (Tree **) malloc(capacity * sizeof(Tree *));
}

void freeTQ(TreeQueue *tq)
{
	free(tq->queue);
	tq->queue = NULL;
}

void resetTQ(TreeQueue *tq)
{
	tq->size 	= 0;
	tq->front 	= 0;
	tq->back 	= 0;
}

bool isEmptyTQ(TreeQueue *tq)
{
	return tq->size == 0;
}

bool isFullTQ(TreeQueue *tq)
{
	return tq->size == tq->capacity;
}

void enQueueTQ(TreeQueue *tq, Tree *t)
{
	tq->queue[tq->back] = t;
	tq->back++;
	if (tq->back == tq->capacity) { tq->back = 0;}
	tq->size++;
}

Tree * deQueueTQ(TreeQueue *tq)
{
	if (isEmptyTQ(tq))
	{
		return NULL;
	}
	else
	{
		Tree *tmp = tq->queue[tq->front];
		tq->front++;
		if (tq->front == tq->capacity) { tq->front = 0;}
		tq->size--;
		return tmp;
	}
}



/******************************************************************************* 
---------------------------------- UNIT TESTS ----------------------------------
*******************************************************************************/



/******************************************************************************* 
--------------------------------- END OF FILE ----------------------------------
*******************************************************************************/