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

node * td2buTransform(node *tdRoot)
{
    node *buRoot = newNode(0);
    td2buRecursive(tdRoot, buRoot);
    return buRoot;
}
/* -------------------------------------------------------------------------- */


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

node * td2buTransformCont(node *tdRoot, node *nodeArray)
{   
    node *buRoot = nodeArray++;
    buRoot->key = 0;
    td2buRecursiveCont(tdRoot, buRoot, &nodeArray);
    return buRoot;
}
/* -------------------------------------------------------------------------- */


/* -------- Super Efficient Versions (Just Traverse Down Node Array) -------- */
node * td2buTransformCont2(node *inputArray, int inputSize, node *outputArray)
{   
    node *root = outputArray++;
    root->key = 0;
    int i;
    node *n;
    for (i=0, n=inputArray; i<inputSize; i++, n++)
    {
        // printf("TD2BU on Node: %d\n", tdRoot->key);
        if (n->children == NULL) insertPathCont(n, root, &outputArray);
    }
    return root;
}
/* -------------------------------------------------------------------------- */



/******************************************************************************* 
---------------------------------- UNIT TESTS ----------------------------------
*******************************************************************************/
// /* Driver program to test above function*/
void treeConvUnitTest(const char tree_input_file[])
{
    int i;

    node *splayArray = NULL;
    node *original = NULL;

    std::unordered_map<std::string, int> keyMap;
    int treeSize = loadJSON(tree_input_file, keyMap, &splayArray, &original);

    std::unordered_map<int, std::string> invKeyMap;
    for (std::pair<std::string, int> element : keyMap)
    {
        invKeyMap[element.second] = element.first;
    }


    printf("\n");
    printf("Info on Originally Loaded Top-Down Tree\n");
    printf("---------------------------------------\n");
    printf("JSON File Path: %s\n", tree_input_file);
    printf("Tree Size: %d\n", treeSize);
    printf("Unique Keys: %d\n", (int) keyMap.size());
    std::cout << "Root Key: " << invKeyMap[original->key] << "\n";
    std::cout << "Root Parent: " << (original->parent == NULL ? "NULL" : invKeyMap[original->parent->key]) << "\n";
    std::cout << "Root Left: " << (original->left == NULL ? "NULL" : invKeyMap[original->left->key]) << "\n";
    std::cout << "Root Right: " << (original->right == NULL ? "NULL" : invKeyMap[original->right->key]) << "\n";
    std::cout << "Root Children Root: " << (original->children == NULL ? "NULL" : invKeyMap[original->children->key]) << "\n";
    printf("Root Children\n");
    // print_ascii_tree(original->children);
    printf("\n");
    outputJSON(output_og_tree_file, invKeyMap, original);


    printf("\n");
    printf("Converted Bottum-Up Tree Info \n");
    printf("------------------------------\n");
    node *buTree = td2buTransform(original);
    int buTreeSize = getTreeSize(buTree);
    printf("Tree Size: %d\n", buTreeSize);
    std::cout << "Root Key: " << invKeyMap[buTree->key] << "\n";
    std::cout << "Root Parent: " << (buTree->parent == NULL ? "NULL" : invKeyMap[buTree->parent->key]) << "\n";
    std::cout << "Root Left: " << (buTree->left == NULL ? "NULL" : invKeyMap[buTree->left->key]) << "\n";
    std::cout << "Root Right: " << (buTree->right == NULL ? "NULL" : invKeyMap[buTree->right->key]) << "\n";
    std::cout << "Root Children Root: " << (buTree->children == NULL ? "NULL" : invKeyMap[buTree->children->key]) << "\n";
    printf("Root Children\n");
    // print_ascii_tree(buTree->children);
    printf("\n");
    outputJSON(output_bu_tree_file, invKeyMap, buTree);


    printf("\n");
    printf("Re-Converted Top-Down Tree Info \n");
    printf("--------------------------------\n");
    node *tdTree = td2buTransform(buTree);
    int tdTreeSize = getTreeSize(tdTree);
    printf("Tree Size: %d\n", tdTreeSize);
    std::cout << "Root Key: " << invKeyMap[tdTree->key] << "\n";
    std::cout << "Root Parent: " << (tdTree->parent == NULL ? "NULL" : invKeyMap[tdTree->parent->key]) << "\n";
    std::cout << "Root Left: " << (tdTree->left == NULL ? "NULL" : invKeyMap[tdTree->left->key]) << "\n";
    std::cout << "Root Right: " << (tdTree->right == NULL ? "NULL" : invKeyMap[tdTree->right->key]) << "\n";
    std::cout << "Root Children Root: " << (tdTree->children == NULL ? "NULL" : invKeyMap[tdTree->children->key]) << "\n";
    printf("Root Children\n");
    // print_ascii_tree(tdTree->children);
    printf("\n");
    outputJSON(output_td_tree_file, invKeyMap, tdTree);


    freeTree(buTree);
    freeTree(tdTree);


    printf("\n");
    printf("Contiguous Converted Bottum-Up Tree Info \n");
    printf("-----------------------------------------\n");
    node *buNodeArray = (node *) malloc(buTreeSize * sizeof(node));
    for (i=0, buTree=buNodeArray; i<buTreeSize; i++, buTree++)
    {
        initNode(buTree);
    }
    buTree = td2buTransformCont(original, buNodeArray);
    buTreeSize = getTreeSize(buTree);
    printf("Tree Size: %d\n", buTreeSize);
    std::cout << "Root Key: " << invKeyMap[buTree->key] << "\n";
    std::cout << "Root Parent: " << (buTree->parent == NULL ? "NULL" : invKeyMap[buTree->parent->key]) << "\n";
    std::cout << "Root Left: " << (buTree->left == NULL ? "NULL" : invKeyMap[buTree->left->key]) << "\n";
    std::cout << "Root Right: " << (buTree->right == NULL ? "NULL" : invKeyMap[buTree->right->key]) << "\n";
    std::cout << "Root Children Root: " << (buTree->children == NULL ? "NULL" : invKeyMap[buTree->children->key]) << "\n";
    printf("Root Children\n");
    // print_ascii_tree(buTree->children);
    printf("\n");
    outputJSON(output_bu_tree_file, invKeyMap, buTree);


    printf("\n");
    printf("Contiguous Re-Converted Top-Down Tree Info \n");
    printf("-------------------------------------------\n");
    node *tdNodeArray = (node *) malloc(tdTreeSize * sizeof(node));
    for (i=0, tdTree=tdNodeArray; i<tdTreeSize; i++, tdTree++)
    {
        initNode(tdTree);
    }
    tdTree = td2buTransformCont(buTree, tdNodeArray);
    tdTreeSize = getTreeSize(tdTree);
    printf("Tree Size: %d\n", tdTreeSize);
    std::cout << "Root Key: " << invKeyMap[tdTree->key] << "\n";
    std::cout << "Root Parent: " << (tdTree->parent == NULL ? "NULL" : invKeyMap[tdTree->parent->key]) << "\n";
    std::cout << "Root Left: " << (tdTree->left == NULL ? "NULL" : invKeyMap[tdTree->left->key]) << "\n";
    std::cout << "Root Right: " << (tdTree->right == NULL ? "NULL" : invKeyMap[tdTree->right->key]) << "\n";
    std::cout << "Root Children Root: " << (tdTree->children == NULL ? "NULL" : invKeyMap[tdTree->children->key]) << "\n";
    printf("Root Children\n");
    // print_ascii_tree(tdTree->children);
    printf("\n");
    outputJSON(output_td_tree_file, invKeyMap, tdTree);


    free(buNodeArray);
    free(tdNodeArray);


    printf("\n");
    printf("Contiguous 2 Converted Bottum-Up Tree Info \n");
    printf("-------------------------------------------\n");
    buNodeArray = (node *) malloc(buTreeSize * sizeof(node));
    for (i=0, buTree=buNodeArray; i<buTreeSize; i++, buTree++)
    {
        initNode(buTree);
    }
    buTree = td2buTransformCont2(original, treeSize, buNodeArray);
    buTreeSize = getTreeSize(buTree);
    printf("Tree Size: %d\n", buTreeSize);
    std::cout << "Root Key: " << invKeyMap[buTree->key] << "\n";
    std::cout << "Root Parent: " << (buTree->parent == NULL ? "NULL" : invKeyMap[buTree->parent->key]) << "\n";
    std::cout << "Root Left: " << (buTree->left == NULL ? "NULL" : invKeyMap[buTree->left->key]) << "\n";
    std::cout << "Root Right: " << (buTree->right == NULL ? "NULL" : invKeyMap[buTree->right->key]) << "\n";
    std::cout << "Root Children Root: " << (buTree->children == NULL ? "NULL" : invKeyMap[buTree->children->key]) << "\n";
    printf("Root Children\n");
    // print_ascii_tree(buTree->children);
    printf("\n");
    outputJSON(output_bu_tree_file, invKeyMap, buTree);


    printf("\n");
    printf("Contiguous 2 Re-Converted Top-Down Tree Info \n");
    printf("---------------------------------------------\n");
    tdNodeArray = (node *) malloc(tdTreeSize * sizeof(node));
    for (i=0, tdTree=tdNodeArray; i<tdTreeSize; i++, tdTree++)
    {
        initNode(tdTree);
    }
    tdTree = td2buTransformCont2(buTree, buTreeSize, tdNodeArray);
    tdTreeSize = getTreeSize(tdTree);
    printf("Tree Size: %d\n", tdTreeSize);
    std::cout << "Root Key: " << invKeyMap[tdTree->key] << "\n";
    std::cout << "Root Parent: " << (tdTree->parent == NULL ? "NULL" : invKeyMap[tdTree->parent->key]) << "\n";
    std::cout << "Root Left: " << (tdTree->left == NULL ? "NULL" : invKeyMap[tdTree->left->key]) << "\n";
    std::cout << "Root Right: " << (tdTree->right == NULL ? "NULL" : invKeyMap[tdTree->right->key]) << "\n";
    std::cout << "Root Children Root: " << (tdTree->children == NULL ? "NULL" : invKeyMap[tdTree->children->key]) << "\n";
    printf("Root Children\n");
    // print_ascii_tree(tdTree->children);
    printf("\n");
    outputJSON(output_td_tree_file, invKeyMap, tdTree);


    free(buNodeArray);
    free(tdNodeArray);
    free(splayArray);
}




/******************************************************************************* 
--------------------------------- END OF FILE ----------------------------------
*******************************************************************************/