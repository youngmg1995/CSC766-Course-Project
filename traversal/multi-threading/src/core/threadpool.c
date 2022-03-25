/******************************************************************************* 
------------------------------------- INFO -------------------------------------
*******************************************************************************/
/**
 * @file binaryTree.c
 * @author Mitchell Young (mgyoung@ncsu.edu)
 * @brief Function definitions related to thread pool used in 
 *  multi-threaded implementation of tree traversals.
 * @version 0.1
 * @date 2022-03-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */


/******************************************************************************* 
------------------------------- IMPORTS & PARAMS -------------------------------
*******************************************************************************/
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "threadpool.h"



/******************************************************************************* 
------------------------------- GLOBAL VARIABLES -------------------------------
*******************************************************************************/

pthread_t threadPool[NUM_THREADS-1];
volatile int threadCount = 0;

TraversalTask taskQueue[255];
volatile int taskCount = 0;

pthread_mutex_t queueMutex;
pthread_cond_t queueCond;

bool addingTasks = false;

/******************************************************************************* 
------------------------------- THREAD FUNCTIONS -------------------------------
*******************************************************************************/

void execTraversalTask(TraversalTask *task)
{
    // task->traversalFunc(task->root, task->callback);
    task->callback(task->root);
}

void submitTraversalTask(TraversalTask task)
{
    pthread_mutex_lock(&queueMutex);
    taskQueue[taskCount] = task;
    taskCount++;
    pthread_mutex_unlock(&queueMutex);
    pthread_cond_signal(&queueCond);
}

void * startThread(void *args)
{
    printf("Starting Thread\n");

    while (addingTasks || taskCount > 0)
    {
        TraversalTask task;

        pthread_mutex_lock(&queueMutex);
        while (taskCount == 0)
        {
            pthread_cond_wait(&queueCond, &queueMutex);
        }

        if (!addingTasks && taskCount == 0) break;

        // this queue can be improved/optimized
        task = taskQueue[0];
        int i;
        for (i=0; i<taskCount-1; i++)
        {
            taskQueue[i] = taskQueue[i+1];
        }
        taskCount--;
        pthread_mutex_unlock(&queueMutex);
        printf("Executing Task: Node ID = %d\n", task.root->id);
        execTraversalTask(&task); 
    }

    printf("Finishing Thread\n");

    return NULL;
}

void initThreadPool()
{
    printf("Initializing Threads from Main Thread\n");

    pthread_mutex_init(&queueMutex, NULL);
    pthread_cond_init(&queueCond, NULL);

    addingTasks = true;

    int t;
    for (t=0; t<NUM_THREADS-1; t++)
    {
        if (pthread_create(&threadPool[t], NULL, &startThread, NULL) != 0)
        {
            perror("Failed to create the thread");
        }
        else
        {
            threadCount++;
        }
    }

    printf("Finished Initializing Threads from Main Thread\n");
}

void joinThreadPool()
{
    printf("Joining Threads from Main Thread\n");

    pthread_mutex_lock(&queueMutex);
    addingTasks = false;
    pthread_mutex_unlock(&queueMutex);
    pthread_cond_broadcast(&queueCond);

    int t;
    for (t=0; t<NUM_THREADS-1; t++)
    {
        if (pthread_join(threadPool[t], NULL) != 0)
        {
            perror("Failed to join the thread");
        }
        else
        {
            printf("Joined Thread: ID = %d\n", t);
            threadCount--;
        }
    }

    pthread_mutex_destroy(&queueMutex);
    pthread_cond_destroy(&queueCond);

    printf("Finished Joining Threads from Main Thread\n");
}




/******************************************************************************* 
-------------------------- MULTI-THREADED TRAVERSALS ---------------------------
*******************************************************************************/
void preOrderMT(Tree * root, TreeCallback callback)
{
	if (root != NULL)
	{	
        printf("Creating Task for Root: id = %d\n", root->id);
        TraversalTask task = {
            .root = root,
            .callback = callback,
        };
		submitTraversalTask(task);

		preOrderMT(root->left, callback);
		preOrderMT(root->right, callback);
	}
}
void preOrderMTWrapper(Tree * root, TreeCallback callback)
{
    initThreadPool();

	if (root != NULL)
	{	
        printf("Creating Task for Root: id = %d\n", root->id);
        TraversalTask task = {
            .root = root,
            .callback = callback,
        };
		submitTraversalTask(task);

		preOrderMT(root->left, callback);
		preOrderMT(root->right, callback);
	}

    joinThreadPool();
}

void postOrderMT(Tree *root, TreeCallback callback)
{
	if (root != NULL)
	{	
		postOrderMT(root->left, callback);
		postOrderMT(root->right, callback);

        printf("Creating Task for Root: id = %d\n", root->id);
        TraversalTask task = {
            .root = root,
            .callback = callback,
        };
		submitTraversalTask(task);
	}
}
void postOrderMTWrapper(Tree *root, TreeCallback callback)
{
    initThreadPool();

	if (root != NULL)
	{	
		postOrderMT(root->left, callback);
		postOrderMT(root->right, callback);

        printf("Creating Task for Root: id = %d\n", root->id);
        TraversalTask task = {
            .root = root,
            .callback = callback,
        };
		submitTraversalTask(task);
	}

    joinThreadPool();
}



/******************************************************************************* 
---------------------------------- UNIT TESTS ----------------------------------
*******************************************************************************/



/******************************************************************************* 
--------------------------------- END OF FILE ----------------------------------
*******************************************************************************/