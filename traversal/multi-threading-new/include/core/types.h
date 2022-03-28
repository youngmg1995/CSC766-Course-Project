/******************************************************************************* 
------------------------------------- INFO -------------------------------------
*******************************************************************************/
/**
 * @file types.h
 * @author Mitchell Young (mgyoung@ncsu.edu)
 * @brief Defines binary tree types and other types used to create/draw them.
 * @version 0.1
 * @date 2022-03-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef	__BINARYTREE_TYPES_H
#define	__BINARYTREE_TYPES_H


/******************************************************************************* 
------------------------------- IMPORTS & PARAMS -------------------------------
*******************************************************************************/
#include <pthread.h>
#include <stdbool.h>


/******************************************************************************* 
--------------------------------- BINARY TREE ----------------------------------
*******************************************************************************/

/* basic binary tree (primary type used in module) */
typedef struct Tree Tree;
struct Tree
{
	int id;
	void *data;
	Tree *left;
	Tree *right;
};



/******************************************************************************* 
------------------------------- TREE GENERATION --------------------------------
*******************************************************************************/

/* type used while building binary tree from inversion table */
typedef struct ITNode ITNode;
struct ITNode
{
	int val;
	Tree *tree;
	ITNode *parent;
};

/* type used to get info about generated binary tree */
typedef struct TreeInfo
{
	int size;
	int leaves;
	int depth;
	float density;
	Tree *root;
} TreeInfo;



/******************************************************************************* 
-------------------------------- TREE TRAVERSAL --------------------------------
*******************************************************************************/

/* defines callback function type for performing actions during tree traversal */
typedef void (*TreeCallback)(Tree *);

/* binary tree queue, used for level-order traversal */
typedef struct TreeQueue
{
	int capacity;
	int size;
	int front;
	int back;
	Tree **queue;
} TreeQueue;

/* types for passing function pointer to traversal function */
typedef void (*TraversalFunc)(Tree *);
typedef void (*TraversalFuncCB)(Tree *, TreeCallback);
typedef void (*TraversalFuncLevel)(Tree *, TreeQueue *);
typedef void (*TraversalFuncLevelCB)(Tree *, TreeQueue *, TreeCallback);
typedef void (*TraversalFuncCont)(Tree *, int);
typedef void (*TraversalFuncContCB)(Tree *, int, TreeCallback);



/******************************************************************************* 
------------------------------- MULTI-THREADING --------------------------------
*******************************************************************************/

typedef struct TraversalThread TraversalThread;
typedef struct ThreadPool ThreadPool;
typedef struct StartThreadArgs StartThreadArgs;

/* types for passing function pointer to multi-threaded traversal functions */
typedef void (*TraversalFuncMT)(Tree *, TreeCallback, TraversalThread *, ThreadPool *);
typedef void (*TraversalFuncMTWrapper)(Tree *, TreeCallback, ThreadPool *, StartThreadArgs *);

/* stores task executed by each thread */
typedef struct TraversalTask {
	TraversalFuncMT traversalFunc;
	Tree * root;
	TreeCallback callback;
} TraversalTask;

/* stores threads and info related to each (such as current task) */
typedef struct TraversalThread
{
    int threadID;
    bool started;
    bool busy;
    TraversalTask task;
    pthread_t thread;
    pthread_mutex_t mutex;
    pthread_cond_t cond;

    int totalTasks;
    int totalCallbacks;
} TraversalThread;

/* pool that stores all threads and info used during mult-threaded traversal */
typedef struct ThreadPool
{
    int size;
    int taskCount;
    int availThreads;
    int nextThread;
    bool addingTasks;
	bool finished;
    pthread_mutex_t mutex;
    TraversalThread *threads;
} ThreadPool;

/* used for passing various arguments to thread entry point */
typedef struct StartThreadArgs
{
    ThreadPool * threadPool;
    TraversalThread * thread;
} StartThreadArgs;




#endif
/******************************************************************************* 
--------------------------------- END OF FILE ----------------------------------
*******************************************************************************/