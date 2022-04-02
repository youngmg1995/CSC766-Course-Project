/******************************************************************************* 
------------------------------------- INFO -------------------------------------
*******************************************************************************/
/**
 * @file treeLoader.cpp
 * @author Mitchell Young (mgyoung@ncsu.edu)
 * @brief Defines functions for loading and saving splay trees.
 * @version 0.1
 * @date 2022-04-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */


/******************************************************************************* 
------------------------------- IMPORTS & PARAMS -------------------------------
*******************************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

#include "types.h"
#include "splayTree.h"
#include "util.h"

// using namespace std;
// using namespace nholmann;


#define small_tree_file "/Users/mitchell/Documents/classes/csc766/CSC766-Project/tree-transformation/.data/small_tree.json"
#define output_tree_file "/Users/mitchell/Documents/classes/csc766/CSC766-Project/tree-transformation/.data/output_tree.json"

/******************************************************************************* 
---------------------------- TREE LOADER & BUILDER -----------------------------
*******************************************************************************/

int getTreeKeys(nlohmann::json jsonObject, std::unordered_map<std::string, int> &keyMap)
{
    if (jsonObject.size() > 0)
    {
        int totalNodes = 1;

        std::string key = jsonObject["n"];
        nlohmann::json children = jsonObject["c"];

        if (!keyMap.contains(key))
        {
            keyMap[key] = (int) keyMap.size();
        }

        for (auto child : children)
        {
            totalNodes += getTreeKeys(child, keyMap);
        }

        return totalNodes;
    }
    else
    {
        return 0;
    }
}

node * convertJSON2Tree(nlohmann::json rootObject, std::unordered_map<std::string, int> &keyMap, node **splayArray, node *parent)
{
    if (rootObject.size() > 0)
    {
        node *root = *splayArray;
        (*splayArray)++;
        root->key = keyMap[rootObject["n"]];
        root->parent = parent;

        nlohmann::json childrenObject = rootObject["c"];
        if (childrenObject.size() > 0)
        {
            node *child;
            for (auto childObject : childrenObject)
            {
                child = convertJSON2Tree(childObject, keyMap, splayArray, root);
                root->children = insertNode(root->children, child);
            }
        }
        else
        {
            root->children = NULL;
        }

        return root;
    }
    else
    {
        return NULL;
    }
}

int loadJSON(const char fileName[], std::unordered_map<std::string, int> &keyMap, node **splayArray, node **root)
{
    std::ifstream inputStream(fileName);
    nlohmann::json jsonObject = nlohmann::json::parse(inputStream);

    int totalNodes = 0;
    totalNodes = getTreeKeys(jsonObject, keyMap);

    *splayArray = (node *) malloc(totalNodes * sizeof(node));
    int i;
    node *n;
    for (i=0, n=*splayArray; i<totalNodes; i++, n++)
    {
        initNode(n);
    }
    n = *splayArray;

    *root = convertJSON2Tree(jsonObject, keyMap, &n, NULL);

    return totalNodes;
}

/* could improve by sorting by keys in children */
void convertTree2JSON(std::unordered_map<int, std::string> &invKeyMap, node *root, nlohmann::json &parentObject)
{
    if (root != NULL)
    {
        nlohmann::json rootObject;
        rootObject["n"] = invKeyMap[root->key];
        rootObject["c"] = nlohmann::json::array();

        convertTree2JSON(invKeyMap, root->children, rootObject);
        parentObject["c"].push_back(rootObject);

        convertTree2JSON(invKeyMap, root->left, parentObject);
        convertTree2JSON(invKeyMap, root->right, parentObject);
    }
}

void outputJSON(const char fileName[], std::unordered_map<int, std::string> &invKeyMap, node *root)
{
    nlohmann::json outputJSON;
    outputJSON["n"] = invKeyMap[root->key];
    outputJSON["c"] = nlohmann::json::array();
    convertTree2JSON(invKeyMap, root->children, outputJSON);

    std::ofstream outputStream(fileName);
    outputStream << std::setw(4) << outputJSON << std::endl;
}



/******************************************************************************* 
---------------------------------- UNIT TESTS ----------------------------------
*******************************************************************************/
// /* Driver program to test above function*/
void treeLoaderUnitTest()
{
    node *splayArray = NULL;
    node *root = NULL;

    std::unordered_map<std::string, int> keyMap;
    int treeSize = loadJSON(small_tree_file, keyMap, &splayArray, &root);

    std::unordered_map<int, std::string> invKeyMap;
    for (std::pair<std::string, int> element : keyMap)
    {
        invKeyMap[element.second] = element.first;
    }


    printf("\n");
    printf("Info on Loaded Tree\n");
    printf("-------------------\n");
    printf("JSON File Path: %s\n", small_tree_file);
    printf("Tree Size: %d\n", treeSize);
    printf("Unique Keys: %d\n", (int) keyMap.size());
    std::cout << "Root Key: " << invKeyMap[root->key] << "\n";
    std::cout << "Root Parent: " << (root->parent == NULL ? "NULL" : invKeyMap[root->parent->key]) << "\n";
    std::cout << "Root Left: " << (root->left == NULL ? "NULL" : invKeyMap[root->left->key]) << "\n";
    std::cout << "Root Right: " << (root->right == NULL ? "NULL" : invKeyMap[root->right->key]) << "\n";
    std::cout << "Root Children Root: " << (root->children == NULL ? "NULL" : invKeyMap[root->children->key]) << "\n";
    printf("Root Children\n");
    print_ascii_tree(root->children);
    printf("\n");


    outputJSON(output_tree_file, invKeyMap, root);


    free(splayArray);
}



/******************************************************************************* 
--------------------------------- END OF FILE ----------------------------------
*******************************************************************************/