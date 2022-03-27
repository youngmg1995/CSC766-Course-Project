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
#include <unistd.h>

#include "types.h"
#include "threadpool.h"



/******************************************************************************* 
------------------------------- GLOBAL VARIABLES -------------------------------
*******************************************************************************/

pthread_t threadPool[NUM_THREADS-1];
volatile int threadCount = 0;

TraversalTask taskQueue[NUM_THREADS-1];
volatile int taskCount = 0;

pthread_mutex_t queueMutex;
pthread_cond_t queueCond;

bool addingTasks = false;

ThreadInfo threadInfoArray[NUM_THREADS];  



/******************************************************************************* 
---------------------------------- TASK QUEUE ----------------------------------
*******************************************************************************/
typedef struct TaskQueue
{
    int size;
    int capacity;
    int front;
    int back;
    TraversalTask **queue;
} TaskQueue;

void initTaskQueue(TaskQueue *tq, int capacity)
{
	tq->capacity    = capacity;
	tq->size 	    = 0;
	tq->front 	    = 0;
	tq->back 	    = 0;
	tq->queue 	    = (TraversalTask **) malloc(capacity * sizeof(TraversalTask *));
}

void freeTQ(TaskQueue *tq)
{
	free(tq->queue);
	tq->queue = NULL;
}

void resetTQ(TaskQueue *tq)
{
	tq->size 	= 0;
	tq->front 	= 0;
	tq->back 	= 0;
}

bool isEmptyTQ(TaskQueue *tq)
{
	return tq->size == 0;
}

bool isFullTQ(TaskQueue *tq)
{
	return tq->size == tq->capacity;
}

void enQueueTQ(TaskQueue *tq, TraversalTask *t)
{
	tq->queue[tq->back] = t;
	tq->back++;
	if (tq->back == tq->capacity) { tq->back = 0;}
	tq->size++;
}

Tree * deQueueTQ(TaskQueue *tq)
{
	if (isEmptyTQ(tq))
	{
		return NULL;
	}
	else
	{
		TraversalTask *tmp = tq->queue[tq->front];
		tq->front++;
		if (tq->front == tq->capacity) { tq->front = 0;}
		tq->size--;
		return tmp;
	}
}


/******************************************************************************* 
------------------------------- THREAD FUNCTIONS -------------------------------
*******************************************************************************/

void execTraversalTask(TraversalTask *task, ThreadInfo *threadInfo)
{
    threadInfo->tasks++;
    // printf("Executing Task: Thread = %d\n", threadInfo->threadID);
    // printf("Executing Task: Thread = %d , Root = %d\n", threadInfo->threadID, task->root->id);
    task->traversalFunc(task->root, task->callback, threadInfo);
    // task->callback(task->root);
}

void submitTraversalTask(TraversalTask task)
{   
    pthread_mutex_lock(&queueMutex);
    taskQueue[taskCount] = task;
    taskCount++;
    threadCount--;
    pthread_mutex_unlock(&queueMutex);
    pthread_cond_signal(&queueCond);
}

void * startThread(void *args)
{
    // printf("Starting Thread\n");
    ThreadInfo *threadInfo = (ThreadInfo *) args;
    // printf("Starting Thread: %d\n", threadInfo->threadID);

    for (;;)
    {
        if (!addingTasks && taskCount == 0) break;

        TraversalTask task;

        pthread_mutex_lock(&queueMutex);
        while (addingTasks && taskCount == 0)
        {
            pthread_cond_wait(&queueCond, &queueMutex);
        }

        if (!addingTasks && taskCount == 0) {
            pthread_mutex_unlock(&queueMutex);
            break;
        };

        // this queue can be improved/optimized
        task = taskQueue[0];
        int i;
        for (i=0; i<taskCount-1; i++)
        {
            taskQueue[i] = taskQueue[i+1];
        }
        taskCount--;
        // threadCount--;
        pthread_mutex_unlock(&queueMutex);
        // printf("Executing Task: Node ID = %d\n", task.root->id);
        execTraversalTask(&task, threadInfo); 

        pthread_mutex_lock(&queueMutex);
        threadCount++;
        pthread_mutex_unlock(&queueMutex);
    }

    // printf("Finishing Thread\n");

    return NULL;
}

void initThreadPool()
{
    // printf("Initializing Threads from Main Thread\n");

    pthread_mutex_init(&queueMutex, NULL);
    pthread_cond_init(&queueCond, NULL);

    threadCount = NUM_THREADS-1;
    taskCount = 0;

    addingTasks = true;

    threadInfoArray[0].threadID = 0;
    threadInfoArray[0].tasks = 1;
    threadInfoArray[0].callbacks = 0;

    int t;
    for (t=0; t<NUM_THREADS-1; t++)
    {
        threadInfoArray[t+1].threadID = t+1;
        threadInfoArray[t+1].tasks = 0;
        threadInfoArray[t+1].callbacks = 0;

        if (pthread_create(&threadPool[t], NULL, &startThread, (void *) &(threadInfoArray[t+1])) != 0)
        {
            perror("Failed to create the thread");
        }
    }

    // sleep(10);
    // printf("Finished Initializing Threads from Main Thread\n");
}

void joinThreadPool()
{
    // printf("Joining Threads from Main Thread\n");

    pthread_mutex_lock(&queueMutex);
    addingTasks = false;
    pthread_cond_broadcast(&queueCond);
    pthread_mutex_unlock(&queueMutex);

    // printf("Set Adding Tasks to False\n");

    int t;
    for (t=0; t<NUM_THREADS-1; t++)
    {
        if (pthread_join(threadPool[t], NULL) != 0)
        {
            perror("Failed to join the thread");
        }
    }

    int i;
    for (i=0; i<NUM_THREADS; i++)
    {
        printf(
            "Thread: %d , Tasks: %d , Callbacks: %d\n", 
            threadInfoArray[i].threadID, threadInfoArray[i].tasks, threadInfoArray[i].callbacks
        );
    }

    threadCount = 0;
    taskCount = 0;

    pthread_mutex_destroy(&queueMutex);
    pthread_cond_destroy(&queueCond);

    // printf("Finished Joining Threads from Main Thread\n");
}




/******************************************************************************* 
-------------------------- MULTI-THREADED TRAVERSALS ---------------------------
*******************************************************************************/
void preOrderMT(Tree * root, TreeCallback callback, ThreadInfo *threadInfo)
{
	if (root != NULL)
	{
        callback(root);
        threadInfo->callbacks++;

        if (threadCount > 0)
        {
            // printf("Creating Task for Root: id = %d\n", root->id);
            TraversalTask task = {
                .traversalFunc = preOrderMT,
                .root = root->left,
                .callback = callback,
            };
            submitTraversalTask(task);
        }
        else
        {
            preOrderMT(root->left, callback, threadInfo);
        }

		preOrderMT(root->right, callback, threadInfo);
	}
}
void preOrderMTWrapper(Tree * root, TreeCallback callback)
{
    initThreadPool();
    ThreadInfo *threadInfo = &(threadInfoArray[0]);
    
	if (root != NULL)
	{	
        callback(root);
        threadInfo->callbacks++;

        if (threadCount > 0)
        {
            // printf("Creating Task for Root: id = %d\n", root->id);
            TraversalTask task = {
                .traversalFunc = preOrderMT,
                .root = root->left,
                .callback = callback,
            };
            submitTraversalTask(task);
        }
        else
        {
            preOrderMT(root->left, callback, threadInfo);
        }

		preOrderMT(root->right, callback, threadInfo);
	}

    joinThreadPool();
}

void postOrderMT(Tree *root, TreeCallback callback, ThreadInfo *threadInfo)
{
	if (root != NULL)
	{	
        if (threadCount > 0)
        {
            // printf("Creating Task for Root: id = %d\n", root->id);
            TraversalTask task = {
                .traversalFunc = postOrderMT,
                .root = root->left,
                .callback = callback,
            };
            submitTraversalTask(task);
        }
        else
        {
            postOrderMT(root->left, callback, threadInfo);
        }

		postOrderMT(root->right, callback, threadInfo);


        callback(root);
        threadInfo->callbacks++;
	}
}
void postOrderMTWrapper(Tree *root, TreeCallback callback)
{
    initThreadPool();
    ThreadInfo *threadInfo = &(threadInfoArray[0]);

	if (root != NULL)
	{	
        if (threadCount > 0)
        {
            // printf("Creating Task for Root: id = %d\n", root->id);
            TraversalTask task = {
                .traversalFunc = postOrderMT,
                .root = root->left,
                .callback = callback,
            };
            submitTraversalTask(task);
        }
        else
        {
            postOrderMT(root->left, callback, threadInfo);
        }

		postOrderMT(root->right, callback, threadInfo);


        callback(root);
        threadInfo->callbacks++;
	}

    joinThreadPool();
}








// int getThreadCount()
// {
//     pthread_mutex_lock(&queueMutex);
//     int count = threadCount;
//     pthread_mutex_unlock(&queueMutex);
//     return count;
// }

// void preOrderMT(Tree * root, TreeCallback callback, ThreadInfo *threadInfo)
// {
//     callback(root);
//     threadInfo->callbacks++;

// 	if (root->left != NULL)
// 	{
//         if (root->right != NULL)
//         {
//             if (getThreadCount() > 0)
//             {
//                 TraversalTask task = {
//                     .traversalFunc = preOrderMT,
//                     .root = root->left,
//                     .callback = callback,
//                 };
//                 submitTraversalTask(task);
//             }
//             else
//             {
//                 preOrderMT(root->left, callback, threadInfo);
//             }
// 		    preOrderMT(root->right, callback, threadInfo);
//         }
//         else
//         {
//             preOrderMT(root->left, callback, threadInfo);
//         }
// 	}
//     else 
//     {
//         if (root->right != NULL)
//         {
//             preOrderMT(root->right, callback, threadInfo);
//         }
//     }
// }
// void preOrderMTWrapper(Tree * root, TreeCallback callback)
// {
//     initThreadPool();
//     ThreadInfo *threadInfo = &(threadInfoArray[0]);
    
//     callback(root);
//     threadInfo->callbacks++;

// 	if (root->left != NULL)
// 	{
//         if (root->right != NULL)
//         {
//             if (getThreadCount() > 0)
//             {
//                 TraversalTask task = {
//                     .traversalFunc = preOrderMT,
//                     .root = root->left,
//                     .callback = callback,
//                 };
//                 submitTraversalTask(task);
//             }
//             else
//             {
//                 preOrderMT(root->left, callback, threadInfo);
//             }
// 		    preOrderMT(root->right, callback, threadInfo);
//         }
//         else
//         {
//             preOrderMT(root->left, callback, threadInfo);
//         }
// 	}
//     else 
//     {
//         if (root->right != NULL)
//         {
//             preOrderMT(root->right, callback, threadInfo);
//         }
//     }

//     joinThreadPool();
// }

// void postOrderMT(Tree *root, TreeCallback callback, ThreadInfo *threadInfo)
// {
// 	if (root->left != NULL)
// 	{
//         if (root->right != NULL)
//         {
//             if (getThreadCount() > 0)
//             {
//                 TraversalTask task = {
//                     .traversalFunc = postOrderMT,
//                     .root = root->left,
//                     .callback = callback,
//                 };
//                 submitTraversalTask(task);
//             }
//             else
//             {
//                 postOrderMT(root->left, callback, threadInfo);
//             }
// 		    postOrderMT(root->right, callback, threadInfo);
//         }
//         else
//         {
//             postOrderMT(root->left, callback, threadInfo);
//         }
// 	}
//     else 
//     {
//         if (root->right != NULL)
//         {
//             postOrderMT(root->right, callback, threadInfo);
//         }
//     }

//     callback(root);
//     threadInfo->callbacks++;
// }
// void postOrderMTWrapper(Tree *root, TreeCallback callback)
// {
//     initThreadPool();
//     ThreadInfo *threadInfo = &(threadInfoArray[0]);

// 	if (root->left != NULL)
// 	{
//         if (root->right != NULL)
//         {
//             if (getThreadCount() > 0)
//             {
//                 TraversalTask task = {
//                     .traversalFunc = postOrderMT,
//                     .root = root->left,
//                     .callback = callback,
//                 };
//                 submitTraversalTask(task);
//             }
//             else
//             {
//                 postOrderMT(root->left, callback, threadInfo);
//             }
// 		    postOrderMT(root->right, callback, threadInfo);
//         }
//         else
//         {
//             postOrderMT(root->left, callback, threadInfo);
//         }
// 	}
//     else 
//     {
//         if (root->right != NULL)
//         {
//             postOrderMT(root->right, callback, threadInfo);
//         }
//     }

//     callback(root);
//     threadInfo->callbacks++;

//     joinThreadPool();
// }



/******************************************************************************* 
---------------------------------- UNIT TESTS ----------------------------------
*******************************************************************************/



/******************************************************************************* 
--------------------------------- END OF FILE ----------------------------------
*******************************************************************************/