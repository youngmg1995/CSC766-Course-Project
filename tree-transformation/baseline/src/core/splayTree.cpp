/******************************************************************************* 
------------------------------------- INFO -------------------------------------
*******************************************************************************/
/**
 * @file binaryTree.cpp
 * @author Mitchell Young (mgyoung@ncsu.edu)
 *  - code base pulled from: https://www.geeksforgeeks.org/splay-tree-set-2-insert-delete/
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

#include <types.h>
#include "util.h"
 


/******************************************************************************* 
--------------------------------- TREE METHODS ---------------------------------
*******************************************************************************/

/* Helper function that allocates a new node with the given key and
    NULL left and right pointers. */
node * newNode(int key)
{
    node* n = (node *) malloc(sizeof(node));
    n->key   = key;
    n->left  = n->right  = NULL;
    return (n);
}

void initNode(node *n)
{
    n->key = -1;
    n->left = n->right = n->parent = n->children = NULL;
}

node * freeTree(node *root)
{
    if (root != NULL)
    {
        freeTree(root->children);
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }

    return NULL;
}
 
// A utility function to right rotate subtree rooted with y
// See the diagram given above.
node * rightRotate(node *x)
{
    node *y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}
 
// A utility function to left rotate subtree rooted with x
// See the diagram given above.
node * leftRotate(node *x)
{
    node *y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}
 
// This function brings the key at root if key is present in tree.
// If key is not present, then it brings the last accessed item at
// root.  This function modifies the tree and returns the new root
node * splay(node *root, int key)
{
    // Base cases: root is NULL or key is present at root
    if (root == NULL || root->key == key)
        return root;
 
    // Key lies in left subtree
    if (root->key > key)
    {
        // Key is not in tree, we are done
        if (root->left == NULL) return root;
 
        // Zig-Zig (Left Left)
        if (root->left->key > key)
        {
            // First recursively bring the key as root of left-left
            root->left->left = splay(root->left->left, key);
 
            // Do first rotation for root, second rotation is done after else
            root = rightRotate(root);
        }
        else if (root->left->key < key) // Zig-Zag (Left Right)
        {
            // First recursively bring the key as root of left-right
            root->left->right = splay(root->left->right, key);
 
            // Do first rotation for root->left
            if (root->left->right != NULL)
                root->left = leftRotate(root->left);
        }
 
        // Do second rotation for root
        return (root->left == NULL)? root: rightRotate(root);
    }
    else // Key lies in right subtree
    {
        // Key is not in tree, we are done
        if (root->right == NULL) return root;
 
        // Zag-Zig (Right Left)
        if (root->right->key > key)
        {
            // Bring the key as root of right-left
            root->right->left = splay(root->right->left, key);
 
            // Do first rotation for root->right
            if (root->right->left != NULL)
                root->right = rightRotate(root->right);
        }
        else if (root->right->key < key)// Zag-Zag (Right Right)
        {
            // Bring the key as root of right-right and do first rotation
            root->right->right = splay(root->right->right, key);
            root = leftRotate(root);
        }
 
        // Do second rotation for root
        return (root->right == NULL)? root: leftRotate(root);
    }
}
 
// The search function for Splay tree.  Note that this function
// returns the new root of Splay Tree.  If key is present in tree
// then, it is moved to root.
node * search(node *root, int key)
{
    return splay(root, key);
}

// Function to insert a new key k in splay tree with given root
node * insert(node *root, int k)
{
    // Simple Case: If tree is empty
    if (root == NULL) return newNode(k);
 
    // Bring the closest leaf node to root
    root = splay(root, k);
 
    // If key is already present, then return
    if (root->key == k) return root;
 
    // Otherwise allocate memory for new node
    node *newnode  = newNode(k);
 
    // If root's key is greater, make root as right child
    // of newnode and copy the left child of root to newnode
    if (root->key > k)
    {
        newnode->right = root;
        newnode->left = root->left;
        root->left = NULL;
    }
 
    // If root's key is smaller, make root as left child
    // of newnode and copy the right child of root to newnode
    else
    {
        newnode->left = root;
        newnode->right = root->right;
        root->right = NULL;
    }
 
    return newnode; // newnode becomes new root
}

// Function to insert a new key k in splay tree with given root
node * insertNode(node *root, node *n)
{
    // Simple Case: If tree is empty
    if (root == NULL) return n;
 
    // Bring the closest leaf node to root
    root = splay(root, n->key);
 
    // If key is already present, then return
    if (root->key == n->key) return root;
 
    // If root's key is greater, make root as right child
    // of newnode and copy the left child of root to newnode
    if (root->key > n->key)
    {
        n->right = root;
        n->left = root->left;
        root->left = NULL;
    }
 
    // If root's key is smaller, make root as left child
    // of newnode and copy the right child of root to newnode
    else
    {
        n->left = root;
        n->right = root->right;
        root->right = NULL;
    }
 
    return n; // newnode becomes new root
}
 
// A utility function to print preorder traversal of the tree.
// The function also prints height of every node
void preOrder(node *root)
{
    if (root != NULL)
    {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}



/******************************************************************************* 
---------------------------------- UNIT TESTS ----------------------------------
*******************************************************************************/
// /* Driver program to test above function*/
void splayTreeUnitTest()
{
    node *tmp;
    node *root = newNode(100);

    root->left = newNode(50);
    root->right = newNode(200);
    root->left->left = newNode(40);
    root->left->left->left = newNode(30);
    root->left->left->left->left = newNode(20);
 
    printf("\n");
    printf("Original Tree:\n");
    printf("--------------\n");
    print_ascii_tree(root);
    printf("\n");

    printf("Search: 20\n");
    printf("--------------\n");
    root = search(root, 20);
    print_ascii_tree(root);
    printf("\n");

    printf("Search: 100\n");
    printf("--------------\n");
    root = search(root, 100);
    print_ascii_tree(root);
    printf("\n");

    printf("Search: 100\n");
    printf("--------------\n");
    root = search(root, 100);
    print_ascii_tree(root);
    printf("\n");

    printf("Insert: 80\n");
    printf("--------------\n");
    tmp = newNode(80);
    root = insertNode(root, tmp);
    print_ascii_tree(root);
    printf("\n");

    printf("Insert: 150\n");
    printf("--------------\n");
    tmp = newNode(150);
    root = insertNode(root, tmp);
    print_ascii_tree(root);
    printf("\n");

    printf("Search: 100\n");
    printf("--------------\n");
    root = search(root, 100);
    print_ascii_tree(root);
    printf("\n");

    printf("Search: 80\n");
    printf("--------------\n");
    root = search(root, 80);
    print_ascii_tree(root);
    printf("\n");

    printf("Search: 50\n");
    printf("--------------\n");
    root = search(root, 50);
    print_ascii_tree(root);
    printf("\n");

    printf("Search: 150\n");
    printf("--------------\n");
    root = search(root, 150);
    print_ascii_tree(root);
    printf("\n");

    printf("Insert: 17\n");
    printf("--------------\n");
    tmp = newNode(17);
    root = insertNode(root, tmp);
    print_ascii_tree(root);
    printf("\n");
}



/******************************************************************************* 
--------------------------------- END OF FILE ----------------------------------
*******************************************************************************/