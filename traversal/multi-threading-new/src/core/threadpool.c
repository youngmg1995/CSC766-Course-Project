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



/******************************************************************************* 
------------------------------- GLOBAL VARIABLES -------------------------------
*******************************************************************************/



/******************************************************************************* 
---------------------------------- TASK QUEUE ----------------------------------
*******************************************************************************/


void initThread(TraversalThread *thread, int threadID)
{
    thread->threadID = threadID;
    pthread_mutex_init(&(thread->mutex), NULL);
    pthread_cond_init(&(thread->cond), NULL);
    thread->started = false;
    thread->busy = false;

    thread->totalTasks = 0;
    thread->totalCallbacks = 0;
}

void destroyThread(TraversalThread *thread)
{
    pthread_mutex_destroy(&(thread->mutex));
    pthread_cond_destroy(&(thread->cond));
}

void initThreadPool(ThreadPool *threadPool, StartThreadArgs *startArgs, int size)
{
    threadPool->size            = size;
    threadPool->availThreads    = 0;
    threadPool->nextThread      = 0;
    threadPool->taskCount       = 0;
    threadPool->addingTasks     = true;
    threadPool->finished        = false;
    pthread_mutex_init(&(threadPool->mutex), NULL);
    // edit this if you remove main thread from threadPool
    threadPool->threads = (TraversalThread *) malloc((size+1) * sizeof(TraversalThread));

    TraversalThread *t;
    int i;
    for (i=0, t=threadPool->threads; i<threadPool->size; i++, t++)
    {
        initThread(t, i);
    }

    // maybe remove later (treats main thread as last in thread poo)
    threadPool->threads[size].threadID = size;
    threadPool->threads[size].totalTasks = 0;
    threadPool->threads[size].totalCallbacks = 0;

    StartThreadArgs *s;
    for (i=0, t=threadPool->threads, s=startArgs; i<threadPool->size; i++, t++, s++)
    {
        s->thread = t;
        s->threadPool = threadPool;
    }
}

void destroyThreadPool(ThreadPool *threadPool, StartThreadArgs *startArgs)
{
    int i;
    TraversalThread *t;
    for (i=0, t=threadPool->threads; i<threadPool->size; i++, t++)
    {
        destroyThread(t);
    }
    free(threadPool->threads);

    pthread_mutex_destroy(&(threadPool->mutex));
}





void execTraversalTask(TraversalThread *thread, ThreadPool *threadPool)
{  
    // printf("Executing Traversal Task: Root = %d , Thread = %d\n", thread->task.root->id, thread->threadID);

    TraversalTask task = thread->task;
    task.traversalFunc(task.root, task.callback, thread, threadPool);

    // locks may not be necessary for altering thread (would anyone else try to acquire it while busy = true?)
    pthread_mutex_lock(&(thread->mutex));
    thread->busy = false;
    pthread_mutex_unlock(&(thread->mutex));

    pthread_mutex_lock(&(threadPool->mutex));
    threadPool->availThreads++;
    threadPool->taskCount--;
    if (threadPool->availThreads == 1)
    {
        threadPool->nextThread = thread->threadID;
    }
    pthread_mutex_unlock(&(threadPool->mutex));
}

bool shouldExit(ThreadPool *threadPool)
{
    if (threadPool->finished)
    {
        return true;
    }
    else
    {
        pthread_mutex_lock(&(threadPool->mutex));

        // printf("Should Exit?: AddingTasks = %s, TaskCount = %d\n",
        //     threadPool->addingTasks ? "True" : "False", threadPool->taskCount
        // );
        bool result = !(threadPool->addingTasks || threadPool->taskCount > 0);

        if (result)
        {
            // printf("Signaling All Threads to Finish\n");
            threadPool->finished = true;
            int i;
            TraversalThread *t;
            for (i=0, t=threadPool->threads; i<threadPool->size; i++, t++)
            {
                pthread_cond_signal(&(t->cond));
            }
        }

        pthread_mutex_unlock(&(threadPool->mutex));
        return result;
    }
}

void * startThread(void *args)
{
    StartThreadArgs *threadArgs = (StartThreadArgs *) args;
    ThreadPool *threadPool = threadArgs->threadPool;
    TraversalThread *thread = threadArgs->thread;

    // printf("Starting Thread: %d\n", thread->threadID);

    for (;;)
    {
        if (shouldExit(threadPool)) break;

        pthread_mutex_lock(&(thread->mutex));
        while (!(thread->busy || threadPool->finished))
        {
            // printf("Thread Waiting: Thread = %d , Busy? = %s\n", thread->threadID, thread->busy ? "True" : "False");
            pthread_cond_wait(&(thread->cond), &(thread->mutex));
            // printf("Thread Awoken: Thread = %d , Busy? = %s\n", thread->threadID, thread->busy ? "True" : "False");
            // printf("Task: Root = %d\n", thread->task.root->id);
        }

        // may cause deadlock here
        if (shouldExit(threadPool)) {
            // handle thread and threadPool changes on completion
            pthread_mutex_unlock(&(thread->mutex));
            break;
        };

        pthread_mutex_unlock(&(thread->mutex));

        execTraversalTask(thread, threadPool);
    }

    // printf("Finishing Thread: %d\n", thread->threadID);

    return NULL;
}




void startThreadPool(ThreadPool *threadPool, StartThreadArgs *startArgs)
{    
    threadPool->taskCount       = 0;
    threadPool->availThreads    = threadPool->size;
    threadPool->nextThread      = 0;
    threadPool->addingTasks     = true;
    threadPool->finished        = false;

    int i;
    TraversalThread *t;
    for (i=0, t=threadPool->threads; i<threadPool->size; i++, t++)
    {
        t->started          = true;
        t->busy             = false;
        t->totalTasks       = 0;
        t->totalCallbacks   = 0;
        if (pthread_create(&(t->thread), NULL, &startThread, (void *) &(startArgs[i])) != 0)
        {
            perror("Failed to create the thread");
        }
    }

    // maybe remove later (treats main thread as last in thread poo)
    t->totalTasks = 0;
    t->totalCallbacks = 0;  
}

void joinThreadPool(ThreadPool *threadPool)
{
    // printf("Joining Threads from Main Thread\n");

    pthread_mutex_lock(&(threadPool->mutex));
    threadPool->addingTasks = false;
    pthread_mutex_unlock(&(threadPool->mutex));

    // printf("Set Adding Tasks to False\n");

    int i;
    TraversalThread *t;
    for (i=0, t=threadPool->threads; i<threadPool->size; i++, t++)
    {
        // pthread_mutex_lock(&(t->mutex));
        // pthread_cond_signal(&(t->cond));
        // pthread_mutex_unlock(&(t->mutex));

        if (pthread_join(t->thread, NULL) != 0)
        {
            perror("Failed to join the thread");
        }
    }

    // printf("Printing Work Done By Each Thread\n");

    // edit this if you remove main thread from threadPool
    for (i=0, t=threadPool->threads; i<threadPool->size+1; i++, t++)
    {
        printf(
            "Thread: %d , Tasks: %d , Callbacks: %d\n", 
            t->threadID, t->totalTasks, t->totalCallbacks
        );
    }
}


bool submitTraversalTask(ThreadPool *threadPool, 
    Tree *root, TraversalFuncMT traversalFunc, TreeCallback callback
)
{   
    if (threadPool->availThreads > 0)
    {
        pthread_mutex_lock(&(threadPool->mutex));
        if (threadPool->availThreads == 0)
        {
            pthread_mutex_unlock(&(threadPool->mutex));
            return false;
        }
        else
        {
            // this code may cause deadlock (what due to trying to grab all the locks)
            TraversalThread *thread = (threadPool->threads + threadPool->nextThread);
            threadPool->availThreads--;
            threadPool->taskCount++;
            if (threadPool->availThreads > 0)
            {
                int i = threadPool->nextThread;
                do {
                    i++;
                    if (i==threadPool->size) i=0;
                } while (threadPool->threads[i].busy);
                threadPool->nextThread = i;
            }

            pthread_mutex_lock(&(thread->mutex));
            thread->busy = true;
            thread->task.root = root;
            thread->task.traversalFunc = traversalFunc;
            thread->task.callback = callback;
            thread->totalTasks++;
            // printf("Submitting Task: Root = %d , Thread = %d\n", root->id, thread->threadID);
            pthread_mutex_unlock(&(thread->mutex));
            pthread_mutex_unlock(&(threadPool->mutex));
            pthread_cond_signal(&(thread->cond));
            return true;
        }
    }
    else
    {
        return false;
    }
}




/******************************************************************************* 
-------------------------- MULTI-THREADED TRAVERSALS ---------------------------
*******************************************************************************/
void preOrderMT(
    Tree *root, TreeCallback callback, 
    TraversalThread *thread, ThreadPool *threadPool
)
{
    callback(root);
    thread->totalCallbacks++;

	if (root->left != NULL)
	{
        if (root->right != NULL)
        {
            if (!submitTraversalTask(threadPool, root->left, preOrderMT, callback))
            {
                preOrderMT(root->left, callback, thread, threadPool);
            }
		    preOrderMT(root->right, callback, thread, threadPool);
        }
        else
        {
            preOrderMT(root->left, callback, thread, threadPool);
        }
	}
    else 
    {
        if (root->right != NULL)
        {
            preOrderMT(root->right, callback, thread, threadPool);
        }
    }
}
void preOrderMTWrapper(Tree *root, TreeCallback callback, ThreadPool *threadPool, StartThreadArgs *startArgs)
{
    startThreadPool(threadPool, startArgs);
    // printf("Thread Pool Started\n");

	preOrderMT(root, callback, &(threadPool->threads[threadPool->size]), threadPool);
    // printf("Tree Traversed\n");

    joinThreadPool(threadPool);
    // printf("Thread Pool Joined\n");
}



void postOrderMT(
    Tree *root, TreeCallback callback, 
    TraversalThread *thread, ThreadPool *threadPool
)
{
	if (root->left != NULL)
	{
        if (root->right != NULL)
        {
            if (!submitTraversalTask(threadPool, root->left, postOrderMT, callback))
            {
                postOrderMT(root->left, callback, thread, threadPool);
            }
		    postOrderMT(root->right, callback, thread, threadPool);
        }
        else
        {
            postOrderMT(root->left, callback, thread, threadPool);
        }
	}
    else 
    {
        if (root->right != NULL)
        {
            postOrderMT(root->right, callback, thread, threadPool);
        }
    }

    callback(root);
    thread->totalCallbacks++;
}
void postOrderMTWrapper(Tree *root, TreeCallback callback, ThreadPool *threadPool, StartThreadArgs *startArgs)
{
    startThreadPool(threadPool, startArgs);
    // printf("Thread Pool Started\n");

	postOrderMT(root, callback, &(threadPool->threads[threadPool->size]), threadPool);
    // printf("Tree Traversed\n");

    joinThreadPool(threadPool);
    // printf("Thread Pool Joined\n");
}



/******************************************************************************* 
---------------------------------- UNIT TESTS ----------------------------------
*******************************************************************************/



/******************************************************************************* 
--------------------------------- END OF FILE ----------------------------------
*******************************************************************************/