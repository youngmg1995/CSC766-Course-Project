/******************************************************************************* 
------------------------------------- INFO -------------------------------------
*******************************************************************************/
/**
 * @file binaryTree.c
 * @author Mitchell Young (mgyoung@ncsu.edu)
 *  - code base pulled from: https://www.codesdope.com/course/data-structures-splay-trees/
 *  - modifications made by author to fit into project
 * @brief Defines basic methods for manipulating splay trees.
 * @version 0.1
 * @date 2022-04-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */



/******************************************************************************* 
------------------------------- IMPORTS & PARAMS -------------------------------
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>



/******************************************************************************* 
---------------------------------- TYPE DEFS -----------------------------------
*******************************************************************************/

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
	struct node *parent;
	struct node *children;
}node;

// typedef struct splay_tree {
// 	struct node *root;
// }splay_tree;



/******************************************************************************* 
-------------------------------- FUNCTION DEFS ---------------------------------
*******************************************************************************/

node* new_node(int key) {
	node *n = malloc(sizeof(node));
	n->key = key;
	n->parent = NULL;
	n->right = NULL;
	n->left = NULL;

	return n;
}

// splay_tree* new_splay_tree() {
// 	splay_tree *t = malloc(sizeof(splay_tree));
// 	t->root = NULL;

// 	return t;
// }

node * maximum(node *root, node *x) {
	while(x->right != NULL)
	x = x->right;
	return x;
}

node * left_rotate(node *root, node *x) {
	node *y = x->right;
	x->right = y->left;
	if(y->left != NULL) {
		y->left->parent = x;
	}
	y->parent = x->parent;
	if(x->parent == NULL) { //x is root
		root = y;
	}
	else if(x == x->parent->left) { //x is left child
		x->parent->left = y;
	}
	else { //x is right child
		x->parent->right = y;
	}
	y->left = x;
	x->parent = y;

	return root;
}

node * right_rotate(node *root, node *x) {
	node *y = x->left;
	x->left = y->right;
	if(y->right != NULL) {
		y->right->parent = x;
	}
	y->parent = x->parent;
	if(x->parent == NULL) { //x is root
		root = y;
	}
	else if(x == x->parent->right) { //x is left child
		x->parent->right = y;
	}
	else { //x is right child
		x->parent->left = y;
	}
	y->right = x;
	x->parent = y;

	return root;
}

node * splay(node *root, node *n) {
	while(n->parent != NULL) { //node is not root
		if(n->parent == root) { //node is child of root, one rotation
			if(n == n->parent->left) {
				root = right_rotate(root, n->parent);
			}
			else {
				root = left_rotate(root, n->parent);
			}
		}
		else {
			node *p = n->parent;
			node *g = p->parent; //grandparent

			if(n->parent->left == n && p->parent->left == p) { //both are left children
				root = right_rotate(root, g);
				root = right_rotate(root, p);
			}
			else if(n->parent->right == n && p->parent->right == p) { //both are right children
				root = left_rotate(root, g);
				root = left_rotate(root, p);
			}
			else if(n->parent->right == n && p->parent->left == p) {
				root = left_rotate(root, p);
				root = right_rotate(root, g);
			}
			else if(n->parent->left == n && p->parent->right == p) {
				root = right_rotate(root, p);
				root = left_rotate(root, g);
			}
		}
	}

	return root;
}

node * insert(node *root, node *n) {
	node *y = NULL;
	node *temp = root;
	while(temp != NULL) {
		y = temp;
		if(n->key < temp->key) {
			temp = temp->left;
		}
		else {
			temp = temp->right;
		}
	}
	n->parent = y;

	if(y == NULL) { //newly added node is root
		root = n;
	}
	else if(n->key < y->key) {
		y->left = n;
	}
	else {
		y->right = n;
	}
	root = splay(root, n);

	return root;
}

node * search(node *root, node **n, int x) {
	if(x == n->key) {
		splay(t, n);
		return n;
	}
	else if(x < n->key){
		return search(root, n->left, x);
	}
	else if(x > n->key) {
		return search(root, n->right, x);
	}
	else {
		return NULL;
	}
}

node * delete(node *root, node *n) {
	splay(root, n);

	node *left_subtree = root->left;
	if(left_subtree != NULL) {
		left_subtree->parent = NULL;
	}
	node *right_subtree = root->right;
	if(right_subtree != NULL) {
		right_subtree->parent = NULL;
	}

	free(n);

	if(left_subtree != NULL) {
		node *m = maximum(left_subtree, left_subtree);
		splay(left_subtree, m);
		left_subtree->right = right_subtree;
		root = left_subtree;
	}
	else {
		root = right_subtree;
	}

	return root;
}

void inorder(splay_tree *t, node *n) {
	if(n != NULL) {
		inorder(t, n->left);
		printf("%d\n", n->key);
		inorder(t, n->right);
	}
}

// int main() {
// 	splay_tree *t = new_splay_tree();

// 	node *a, *b, *c, *d, *e, *f, *g, *h, *i, *j, *k, *l, *m;
// 	a = new_node(10);
// 	b = new_node(20);
// 	c = new_node(30);
// 	d = new_node(100);
// 	e = new_node(90);
// 	f = new_node(40);
// 	g = new_node(50);
// 	h = new_node(60);
// 	i = new_node(70);
// 	j = new_node(80);
// 	k = new_node(150);
// 	l = new_node(110);
// 	m = new_node(120);

// 	insert(t, a);
// 	insert(t, b);
// 	insert(t, c);
// 	insert(t, d);
// 	insert(t, e);
// 	insert(t, f);
// 	insert(t, g);
// 	insert(t, h);
// 	insert(t, i);
// 	insert(t, j);
// 	insert(t, k);
// 	insert(t, l);
// 	insert(t, m);

// 	delete(t, a);
// 	delete(t, m);

// 	inorder(t, t->root);

// 	return 0;
// }