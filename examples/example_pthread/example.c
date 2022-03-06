#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
  
// Let us create a global variable to change it in threads
int g = 0;
  
// The function to be executed by all threads
void *myThreadFun(void *vargp)
{
    // Store the value argument passed to this thread
    int *myid = (int *)vargp;
  
    // Let us create a static variable to observe its changes
    static int s = 0;
  
    // Change static and global variables
    ++s; ++g;
  
    // Print the argument, static and global variables
    printf("Thread ID: %d, Static: %d, Global: %d\n", *myid, ++s, ++g);
}

void *thread_callback(void *arg)
{
    sleep(1);
    printf("Inside the thread_callback: %d\n", *(int *)arg);
    pthread_exit(NULL);
    return NULL;
}

int main()
{
    int i;
    int arg= 42;
    pthread_t tid, thread_id;
    
    // Part 1: access global shared variable

    puts("Before the thread");   
    pthread_create(&thread_id, NULL, thread_callback, &arg);
    pthread_join(thread_id, NULL);
    puts("After the thread");
    
    // Part 2: create three threads

    for (i = 0; i < 3; i++)
        pthread_create(&tid, NULL, myThreadFun, (void *)&tid);
  
    pthread_exit(NULL);
    return 0;
}