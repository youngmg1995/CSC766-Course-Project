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
    if (NUM_THREADS <= 2)
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

/* ================================================================================================================================================= */
/* ================================================================================================================================================= */
/* ================================================================================================================================================= */

/* ---------------- Efficient Versions (Nodes Pre-Allocated) ---------------- */
void insertPathCont(node *leaf, node *root, node **nodeArray)
{
    while (leaf->parent != NULL)
    {
        // printf("Inserting Node: %d\n", leaf->key);
        root->children = insertCont(root->children, leaf->key, nodeArray);
        root->children->parent = root;
        leaf = leaf->parent;
        root = root->children;
    }
}

void td2buRecursiveCont(node *tdRoot, node *buRoot, node **nodeArray)
{
    // printf("TD2BU on Node: %d\n", tdRoot->key);
    if (tdRoot->children == NULL) 
    {
        insertPathCont(tdRoot, buRoot, nodeArray);
    }
    else
    {
        td2buRecursiveCont(tdRoot->children, buRoot, nodeArray);
    }
    
    if (tdRoot->left != NULL) td2buRecursiveCont(tdRoot->left, buRoot, nodeArray);
    if (tdRoot->right != NULL) td2buRecursiveCont(tdRoot->right, buRoot, nodeArray);
}

void insertPathContMT(node *leaf, node *root, node **nodeArray, pthread_mutex_t *arrayMutex)
{
    while (leaf->parent != NULL)
    {
        // printf("Inserting Node: %d\n", leaf->key);
        root->children = insertContMT(root->children, leaf->key, nodeArray, arrayMutex);
        root->children->parent = root;
        leaf = leaf->parent;
        root = root->children;
    }
}

void td2buRecursiveContMT(node *tdRoot, node *buRoot, node **nodeArray, pthread_mutex_t *arrayMutex, int tid)
{
    // printf("MT TD2BU on Node: %d\n", tdRoot->key);
    if (tdRoot->children != NULL) 
    {
        td2buRecursiveContMT(tdRoot->children, buRoot, nodeArray, arrayMutex, tid);
    }
    else if ((tdRoot->key % (NUM_THREADS-1)) == tid)
    {
        insertPathContMT(tdRoot, buRoot, nodeArray, arrayMutex);
    }
    
    if (tdRoot->left != NULL) td2buRecursiveContMT(tdRoot->left, buRoot, nodeArray, arrayMutex, tid);
    if (tdRoot->right != NULL) td2buRecursiveContMT(tdRoot->right, buRoot, nodeArray, arrayMutex, tid);
}

struct td2buTransfContArgs 
{
    node *tdRoot;
    node **nodeArray;
    pthread_mutex_t *arrayMutex;
    int tid;
};

// node * td2buTransformContMT(node *tdRoot, node *nodeArray)
// {   
//     node *buRoot = nodeArray++;
//     buRoot->key = 0;
//     td2buRecursiveCont(tdRoot, buRoot, &nodeArray);
//     return buRoot;
// }

void * td2buTransformContMT(void *args)
{
    struct td2buTransfContArgs *transfArgs = (struct td2buTransfContArgs *) args;
    int tid                         = transfArgs->tid;
    node *tdRoot                    = transfArgs->tdRoot;
    node **nodeArray                = transfArgs->nodeArray;
    pthread_mutex_t *arrayMutex     = transfArgs->arrayMutex;

    // printf("Starting Transformation Thread: %d\n", tid);

    pthread_mutex_lock(arrayMutex);
    node *buRoot = (*nodeArray)++;
    pthread_mutex_unlock(arrayMutex);

    buRoot->key = 0;

    td2buRecursiveContMT(tdRoot, buRoot, nodeArray, arrayMutex, tid);
    return (void *) buRoot;
}

void getArrayOffsets(node *tdRoot, td2buTransfContArgs *threadArgs)
{
    int tid = tdRoot->key % (NUM_THREADS-1);
    (*(threadArgs[tid].nodeArray))++;

    if (tdRoot->children != NULL) getArrayOffsets(tdRoot->children, threadArgs);
    if (tdRoot->left != NULL) getArrayOffsets(tdRoot->left, threadArgs);
    if (tdRoot->right != NULL) getArrayOffsets(tdRoot->right, threadArgs);
}

node * td2buTransformContMain(node *tdRoot, node *nodeArray)
{
    if (NUM_THREADS <= 2)
    {
        node *mainRoot = nodeArray++;
        mainRoot->key = 0;
        td2buRecursiveCont(tdRoot, mainRoot, &nodeArray);
        return mainRoot;
    }
    else
    {
        pthread_t threads[NUM_THREADS-1];
        pthread_mutex_t arrayMutex;
        struct td2buTransfContArgs threadArgs[NUM_THREADS-1];
        int tid;

        pthread_mutex_init(&arrayMutex, NULL);

        node *mainRoot, *threadRoots[NUM_THREADS-1], *threadRoot;
        mainRoot = nodeArray++;
        mainRoot->key = 0;

        // printf("Creating Threads\n");

        for (tid=0; tid<NUM_THREADS-1; tid++)
        {
            threadArgs[tid].tid = tid;
            threadArgs[tid].tdRoot = tdRoot;
            threadArgs[tid].arrayMutex = &arrayMutex;
            threadArgs[tid].nodeArray = &nodeArray;
            if (pthread_create(&(threads[tid]), NULL, &td2buTransformContMT, (void *) &(threadArgs[tid])) != 0)
            {
                perror("Failed to create the thread");
            }
        }

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
                threadRoot->key = -1;
            }
            else if (mainRoot->children == NULL)
            {
                mainRoot->key = -1;
                mainRoot = threadRoot;
            }
            else
            {
                mainRoot->children = mergeTrees(mainRoot->children, threadRoot->children);
                threadRoot->children = NULL;
                threadRoot->key = -1;
            }
        }

        pthread_mutex_destroy(&arrayMutex);

        // printf("Returning Root\n");

        return mainRoot;
    }
}
/* -------------------------------------------------------------------------- */

/* ================================================================================================================================================= */
/* ================================================================================================================================================= */
/* ================================================================================================================================================= */

/* ----------- Efficient Versions (Nodes Pre-Allocated) Version 2 ----------- */

void td2buRecursiveContMT2(node *tdRoot, node *buRoot, node **nodeArray, int tid)
{
    // printf("MT TD2BU on Node: %d\n", tdRoot->key);
    if (tdRoot->children != NULL) 
    {
        td2buRecursiveContMT2(tdRoot->children, buRoot, nodeArray, tid);
    }
    else if ((tdRoot->key % (NUM_THREADS-1)) == tid)
    {
        insertPathCont(tdRoot, buRoot, nodeArray);
    }
    
    if (tdRoot->left != NULL) td2buRecursiveContMT2(tdRoot->left, buRoot, nodeArray, tid);
    if (tdRoot->right != NULL) td2buRecursiveContMT2(tdRoot->right, buRoot, nodeArray, tid);
}

struct td2buTransfContArgs2
{
    node *tdRoot;
    node *nodeArray;
    int tid;
};

void * td2buTransformContMT2(void *args)
{
    struct td2buTransfContArgs2 *transfArgs = (struct td2buTransfContArgs2 *) args;
    int tid                         = transfArgs->tid;
    node *tdRoot                    = transfArgs->tdRoot;
    node *nodeArray                 = transfArgs->nodeArray;

    // printf("Starting Transformation Thread: %d\n", tid);

    node *buRoot = nodeArray++;
    buRoot->key = 0;

    td2buRecursiveContMT2(tdRoot, buRoot, &nodeArray, tid);
    return (void *) buRoot;
}

void getThreadLoads(node *tdRoot, int *threadLoads)
{
    int tid = tdRoot->key % (NUM_THREADS-1);
    (threadLoads[tid])++;

    if (tdRoot->children != NULL) getThreadLoads(tdRoot->children, threadLoads);
    if (tdRoot->left != NULL) getThreadLoads(tdRoot->left, threadLoads);
    if (tdRoot->right != NULL) getThreadLoads(tdRoot->right, threadLoads);
}

node * td2buTransformContMain2(node *tdRoot, node *nodeArray)
{
    if (NUM_THREADS <= 2)
    {
        node *mainRoot = nodeArray++;
        mainRoot->key = 0;
        td2buRecursiveCont(tdRoot, mainRoot, &nodeArray);
        return mainRoot;
    }
    else
    {
        pthread_t threads[NUM_THREADS-1];
        struct td2buTransfContArgs2 threadArgs[NUM_THREADS-1];
        int tid;

        node *mainRoot, *threadRoots[NUM_THREADS-1], *threadRoot;
        mainRoot = nodeArray++;
        mainRoot->key = 0;

        int threadLoads[NUM_THREADS-1] = {0};
        getThreadLoads(tdRoot, &(threadLoads[0]));
        for (tid=1; tid<NUM_THREADS-1; tid++) { threadLoads[tid] += threadLoads[tid-1]; }
        for (tid=0; tid<NUM_THREADS-1; tid++) { threadLoads[tid] -= threadLoads[0]; printf("%d\n", threadLoads[tid]); }

        // printf("Creating Threads\n");

        for (tid=0; tid<NUM_THREADS-1; tid++)
        {
            threadArgs[tid].tid = tid;
            threadArgs[tid].tdRoot = tdRoot;
            threadArgs[tid].nodeArray = &(nodeArray[threadLoads[tid]]);
            if (pthread_create(&(threads[tid]), NULL, &td2buTransformContMT2, (void *) &(threadArgs[tid])) != 0)
            {
                perror("Failed to create the thread");
            }
        }

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
                threadRoot->key = -1;
            }
            else if (mainRoot->children == NULL)
            {
                mainRoot->key = -1;
                mainRoot = threadRoot;
            }
            else
            {
                mainRoot->children = mergeTrees(mainRoot->children, threadRoot->children);
                threadRoot->children = NULL;
                threadRoot->key = -1;
            }
        }

        // printf("Returning Root\n");

        return mainRoot;
    }
}
/* -------------------------------------------------------------------------- */

/* ================================================================================================================================================= */
/* ================================================================================================================================================= */
/* ================================================================================================================================================= */

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