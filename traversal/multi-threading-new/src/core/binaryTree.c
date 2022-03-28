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
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include "types.h"
#include "util.h"

static int sampleKey = 849037849;
static double testArray[100];

/******************************************************************************* 
-------------------------------- FUNCTION DEFS ---------------------------------
*******************************************************************************/
void initTree(Tree *tree)
{
	tree->id	= 0;
	tree->data	= NULL;
	tree->left	= NULL;
	tree->right	= NULL;
}

Tree * make_empty(Tree *t)
{
	if (t != NULL)
	{
	make_empty(t->left);
	make_empty(t->right);
	free(t);
	}

	return NULL;
}

Tree * find_min(Tree *t)
{
	if (t == NULL)
	{
		return NULL;
	}
	else if (t->left == NULL)
	{
		return t;
	}
	else
	{
		return find_min(t->left);
	}
}

Tree * find_max(Tree *t)
{
	if (t == NULL)
	{
		return NULL;
	}
	else if (t->right == NULL)
	{
		return t;
	}
	else
	{
		return find_max(t->right);
	}
}

Tree * find(int id, Tree *t)
{
	if (t == NULL)
	{
	return NULL;
	}

	if (id < t->id)
	{
	return find(id, t->left);
	}
	else if (id > t->id)
	{
	return find(id, t->right);
	}
	else
	{
	return t;
	}
}

//Insert i into the tree t, duplicate will be discarded
//Return a pointer to the resulting tree.                 
Tree * insert(int id, void *data, Tree *t) 
{
	Tree * new_node;
	
	if (t == NULL) 
	{
		new_node = (Tree *) malloc (sizeof (Tree));
		if (new_node == NULL) 
		{
			return t;
		}

		new_node->id = id;
		new_node->data = data;
		new_node->left = new_node->right = NULL;
		return new_node;
	}
	
	if (id < t->id) 
	{
		t->left = insert(id, data, t->left);
	} 
	else if (id > t->id) 
	{
		t->right = insert(id, data, t->right);
	} 
	else 
	{ 
	//duplicate, ignore it
		return t;
	}
	return t;
}

Tree * delete(int id, Tree * t, void *data) 
{
	//Deletes node from the tree
	// Return a pointer to the resulting tree
	Tree *tmp_cell;
	
	if (t==NULL) return NULL;
	
	if (id < t->id) 
	{
		t->left = delete(id, t->left, data);
	} 
	else if (id > t->id) 
	{
		t->right = delete(id, t->right, data);
	} 
	else if (t->left && t->right)
	{
		tmp_cell = find_min(t->right);
		t->id = tmp_cell->id;
		t->data = tmp_cell->data;
		t->right = delete(t->id, t->right, data);
	}
	else
	{ 
		tmp_cell = t;
		if (t->left == NULL)
		{
			t = t->right;
		}
		else if (t->right == NULL)
		{
			t = t->left;
		}
		data = tmp_cell->data;
		free(tmp_cell);
	}

	return t;
}

void printNode(Tree *t)
{
	printf("%d ", t->id);
}

void printNodeStdErr(Tree *t)
{
	fprintf(stderr, "%d ", t->id);
}

void incrementID(Tree *t)
{
	(t->id)++;
}

void searchKey(Tree *t)
{
	bool isMatch = (t->id) == sampleKey;
	if (isMatch) sampleKey++;
}

void sleepNode(Tree *t)
{
	usleep(200);
}

void randArray(Tree *t)
{
	int i;
	for (i=0; i<100; i++)
	{
		t->id = (int) genrand64_real2();
	}
}


/******************************************************************************* 
---------------------------------- UNIT TESTS ----------------------------------
*******************************************************************************/



/******************************************************************************* 
--------------------------------- END OF FILE ----------------------------------
*******************************************************************************/