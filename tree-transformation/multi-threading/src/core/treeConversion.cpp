/******************************************************************************* 
------------------------------------- INFO -------------------------------------
*******************************************************************************/
/**
 * @file treeConversion.cpp
 * @author Mitchell Young (mgyoung@ncsu.edu)
 * @brief Defines functions for converting top-down trees to bottom-up
 *  trees and vice versa.
 * @version 0.1
 * @date 2022-04-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */


/******************************************************************************* 
------------------------------- IMPORTS & PARAMS -------------------------------
*******************************************************************************/
#include <stdlib.h>
#include <iostream>
#include <unordered_map>

#include "types.h"
#include "splayTree.h"
#include "treeLoader.h"
#include "threadpool.h"
#include "util.h"



/******************************************************************************* 
------------------------------- HELPER FUNCTIONS -------------------------------
*******************************************************************************/
int getTreeSize(node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    else
    {
        int size = 1;
        size += getTreeSize(root->children);
        size += getTreeSize(root->left);
        size += getTreeSize(root->right);
        return size;
    }
}



/******************************************************************************* 
------------------------------- TREE CONVERSION -------------------------------
*******************************************************************************/

/* --------------- Inefficient Versions (Allocate Each Node) ---------------- */
void insertPath(node *leaf, node *root)
{
    while (leaf->parent != NULL)
    {
        // printf("Inserting Node: %d\n", leaf->key);
        root->children = insert(root->children, leaf->key);
        root->children->parent = root;
        leaf = leaf->parent;
        root = root->children;
    }
}

void td2buRecursive(node *tdRoot, node *buRoot)
{
    // printf("TD2BU on Node: %d\n", tdRoot->key);
    if (tdRoot->children == NULL) 
    {
        insertPath(tdRoot, buRoot);
    }
    else
    {
        td2buRecursive(tdRoot->children, buRoot);
    }
    
    if (tdRoot->left != NULL) td2buRecursive(tdRoot->left, buRoot);
    if (tdRoot->right != NULL) td2buRecursive(tdRoot->right, buRoot);
}

void td2buRecursiveMT(node *tdRoot, node *buRoot, int tid)
{
    // printf("MT TD2BU on Node: %d\n", tdRoot->key);
    if (tdRoot->children != NULL) 
    {
        td2buRecursiveMT(tdRoot->children, buRoot, tid);
    }
    else if ((tdRoot->key % (NUM_THREADS-1)) == tid)
    {
        insertPath(tdRoot, buRoot);
    }
    
    if (tdRoot->left != NULL) td2buRecursiveMT(tdRoot->left, buRoot, tid);
    if (tdRoot->right != NULL) td2buRecursiveMT(tdRoot->right, buRoot, tid);
}

struct td2buTransfArgs 
{
    node *tdRoot;
    int tid;
};

void * td2buTransformMT(void *args)
{
    struct td2buTransfArgs *transfArgs = (struct td2buTransfArgs *) args;
    int tid         = transfArgs->tid;
    node *tdRoot    = transfArgs->tdRoot;

    // printf("Starting Transformation Thread: %d\n", tid);

    node *buRoot = newNode(0);
    td2buRecursiveMT(tdRoot, buRoot, tid);
    return (void *) buRoot;
}

node * td2buTransformMain(node *tdRoot)
{
    if (NUM_THREADS <= 1)
    {
        node *mainRoot = newNode(0);
        td2buRecursive(tdRoot, mainRoot);
        return mainRoot;
    }
    else
    {
        pthread_t threads[NUM_THREADS-1];
        struct td2buTransfArgs threadArgs[NUM_THREADS-1];
        int tid;

        // printf("Creating Threads\n");

        for (tid=0; tid<NUM_THREADS-1; tid++)
        {
            threadArgs[tid].tid = tid;
            threadArgs[tid].tdRoot = tdRoot;
            if (pthread_create(&(threads[tid]), NULL, &td2buTransformMT, (void *) &(threadArgs[tid])) != 0)
            {
                perror("Failed to create the thread");
            }
        }

        node *mainRoot, *threadRoots[NUM_THREADS-1], *threadRoot;
        mainRoot = newNode(0);

        // printf("Joining Threads\n");
        
        for (tid=0; tid<NUM_THREADS-1; tid++)
        {
            if (pthread_join(threads[tid], (void **) &(threadRoots[tid])) != 0)
            {
                perror("Failed to join the thread");
            }
        }

        // printf("Merging Trees\n");

        for (tid=0; tid<NUM_THREADS-1; tid++)
        {
            threadRoot = threadRoots[tid];

            if (threadRoot->children == NULL)
            {
                free(threadRoot);
            }
            else if (mainRoot->children == NULL)
            {
                free(mainRoot);
                mainRoot = threadRoot;
            }
            else
            {
                mainRoot->children = mergeTrees(mainRoot->children, threadRoot->children);
                threadRoot->children = NULL;
                freeTree(threadRoot);
            }
        }

        // printf("Returning Root\n");

        return mainRoot;
    }
}
/* -------------------------------------------------------------------------- */


// /* ---------------- Efficient Versions (Nodes Pre-Allocated) ---------------- */
// void insertPathCont(node *leaf, node *root, node **nodeArray)
// {
//     while (leaf->parent != NULL)
//     {
//         // printf("Inserting Node: %d\n", leaf->key);
//         root->children = insertCont(root->children, leaf->key, nodeArray);
//         root->children->parent = root;
//         leaf = leaf->parent;
//         root = root->children;
//     }
// }

// void td2buRecursiveCont(node *tdRoot, node *buRoot, node **nodeArray)
// {
//     // printf("TD2BU on Node: %d\n", tdRoot->key);
//     if (tdRoot->children == NULL) 
//     {
//         insertPathCont(tdRoot, buRoot, nodeArray);
//     }
//     else
//     {
//         td2buRecursiveCont(tdRoot->children, buRoot, nodeArray);
//     }
    
//     if (tdRoot->left != NULL) td2buRecursiveCont(tdRoot->left, buRoot, nodeArray);
//     if (tdRoot->right != NULL) td2buRecursiveCont(tdRoot->right, buRoot, nodeArray);
// }

// node * td2buTransformCont(node *tdRoot, node *nodeArray)
// {   
//     node *buRoot = nodeArray++;
//     buRoot->key = 0;
//     td2buRecursiveCont(tdRoot, buRoot, &nodeArray);
//     return buRoot;
// }
// /* -------------------------------------------------------------------------- */


// /* -------- Super Efficient Versions (Just Traverse Down Node Array) -------- */
// node * td2buTransformCont2(node *inputArray, int inputSize, node *outputArray)
// {   
//     node *root = outputArray++;
//     root->key = 0;
//     int i;
//     node *n;
//     for (i=0, n=inputArray; i<inputSize; i++, n++)
//     {
//         // printf("TD2BU on Node: %d\n", tdRoot->key);
//         if (n->children == NULL) insertPathCont(n, root, &outputArray);
//     }
//     return root;
// }
// /* -------------------------------------------------------------------------- */



/******************************************************************************* 
---------------------------------- UNIT TESTS ----------------------------------
*******************************************************************************/
// /* Driver program to test above function*/
void treeConvUnitTest(const char compressed_tree_input_file[])
{
    // int i;

    node *splayArray = NULL;
    node *original = NULL;

    int treeSize = loadCompressedJSON(compressed_tree_input_file, &splayArray, &original);


    printf("\n");
    printf("Info on Originally Loaded Top-Down Tree\n");
    printf("---------------------------------------\n");
    printf("JSON File Path: %s\n", compressed_tree_input_file);
    printf("Tree Size: %d\n", treeSize);
    // printf("Root Children\n");
    // print_ascii_tree(original->children);
    // printf("\n");
    outputCompressedJSON(output_og_tree_file, original);


    printf("\n");
    printf("Converted Bottum-Up Tree Info \n");
    printf("------------------------------\n");
    node *buTree = td2buTransformMain(original);
    int buTreeSize = getTreeSize(buTree);
    printf("Tree Size: %d\n", buTreeSize);
    // printf("Root Children\n");
    // print_ascii_tree(buTree->children);
    // printf("\n");
    outputCompressedJSON(output_bu_tree_file, buTree);


    printf("\n");
    printf("Re-Converted Top-Down Tree Info \n");
    printf("--------------------------------\n");
    node *tdTree = td2buTransformMain(buTree);
    int tdTreeSize = getTreeSize(tdTree);
    printf("Tree Size: %d\n", tdTreeSize);
    // printf("Root Children\n");
    // print_ascii_tree(tdTree->children);
    // printf("\n");
    outputCompressedJSON(output_td_tree_file, tdTree);


    freeTree(buTree);
    freeTree(tdTree);
    free(splayArray);
}




/******************************************************************************* 
--------------------------------- END OF FILE ----------------------------------
*******************************************************************************/