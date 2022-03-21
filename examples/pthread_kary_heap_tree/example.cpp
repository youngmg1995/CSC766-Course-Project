#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <iostream>
#include <chrono>
using namespace std;
using namespace chrono;
#define TYPE int

// https://www.geeksforgeeks.org/k-ary-heap/
// C++ program to demonstrate all operations of
// k-ary Heap

// The height of a complete k-ary tree with n-nodes is given by log k(n)
// Implementation:
// 1. Parent of the node at index i (except root node) is located at index (i-1)/k
// 2. Children of the node at index i are at indices (k*i)+1 , (k*i)+2 …. (k*i)+k
// 3. The last non-leaf node of a heap of size n is located at index (n-2)/k

//#include<bits/stdc++.h>
//using namespace std;
 
// function to heapify (or restore the max- heap
// property). This is used to build a k-ary heap
// and in extractMin()
// arr[] -- Array that stores heap
// len   -- Size of array
// index -- index of element to be restored
//          (or heapified)
#define pthreadsNum 12

const int capacity = 1000000;
TYPE arr[capacity] = {4, 5, 6, 7, 8, 9, 10};
int n = 7;
int k = pthreadsNum;
int key;

pthread_t tid[pthreadsNum];
int ids[pthreadsNum];
int tfind[pthreadsNum] = {0};

void restoreDown(TYPE arr[], int len, int index,
                                        int k)
{
    // child array to store indexes of all
    // the children of given node
    int child[k+1];
 
    while (1)
    {
        // child[i]=-1 if the node is a leaf
        // children (no children)
        for (int i=1; i<=k; i++)
            child[i] = ((k*index + i) < len) ?
                    (k*index + i) : -1;
 
        // max_child stores the maximum child and
        // max_child_index holds its index
        int max_child = -1, max_child_index ;
 
        // loop to find the maximum of all
        // the children of a given node
        for (int i=1; i<=k; i++)
        {
            if (child[i] != -1 &&
                arr[child[i]] > max_child)
            {
                max_child_index = child[i];
                max_child = arr[child[i]];
            }
        }
 
        // leaf node
        if (max_child == -1)
            break;
 
        // swap only if the key of max_child_index
        // is greater than the key of node
        if (arr[index] < arr[max_child_index])
            swap(arr[index], arr[max_child_index]);
 
        index = max_child_index;
    }
}
 
// Restores a given node up in the heap. This is used
// in decreaseKey() and insert()
void restoreUp(TYPE arr[], int index, int k)
{
    // parent stores the index of the parent variable
    // of the node
    int parent = (index-1)/k;
 
    // Loop should only run till root node in case the
    // element inserted is the maximum restore up will
    // send it to the root node
    while (parent>=0)
    {
        if (arr[index] > arr[parent])
        {
            swap(arr[index], arr[parent]);
            index = parent;
            parent = (index -1)/k;
        }
 
        // node has been restored at the correct position
        else
            break;
    }
}
 
// Function to build a heap of arr[0..n-1] and value of k.
void buildHeap(TYPE arr[], int n, int k)
{
    // Heapify all internal nodes starting from last
    // non-leaf node all the way upto the root node
    // and calling restore down on each
    for (int i= (n-1)/k; i>=0; i--)
        restoreDown(arr, n, i, k);
}
 
// Function to insert a value in a heap. Parameters are
// the array, size of heap, value k and the element to
// be inserted
void insert(TYPE arr[], int* n, int k, TYPE elem)
{
    // Put the new element in the last position
    arr[*n] = elem;
 
    // Increase heap size by 1
    *n = *n+1;
 
    // Call restoreUp on the last index
    restoreUp(arr, *n-1, k);
}
 
// Function that returns the key of root node of
// the heap and then restores the heap property
// of the remaining nodes
int8_t extractMax(TYPE arr[], int* n, int k)
{
    // Stores the key of root node to be returned
    int max = arr[0];
 
    // Copy the last node's key to the root node
    arr[0] = arr[*n-1];
 
    // Decrease heap size by 1
    *n = *n-1;
 
    // Call restoreDown on the root node to restore
    // it to the correct position in the heap
    restoreDown(arr, *n, 0, k);
 
    return max;
}
// currently dont print out root node, need a wrapper in the future
// first step: print out k child node from 1 parent node
// second step: pick the child with smallest index, use it as next parent node, then call printTree to print next level child nodes
void printTree( int index=0 ){
    int len = n;
    if(index >= len) return;
    // Children of the node at index i are at indices (k*i)+1 , (k*i)+2 …. (k*i)+k
    for( int j = k*index +1 ; j<= k*index + k ; j++ ){
      if( j>= len) return;
      cout<<"("<<j<<","<<arr[j]<<")";
    }
    for( int j = k*index +1 ; j<= k*index + k ; j++ ){
      printTree(j);
    }
}

void* callPrintTree(void *arg ){
    int* ptr = (int*)arg;
    int index = *ptr;  
    printf("tid: %d\n", *(int *)arg);
    printTree(index);
    pthread_exit(NULL);
}

// root of thread, create 4 child thread
void printTree_pthread(int index=0){
    int len = n;
    if(index >= len) return;
    // Children of the node at index i are at indices (k*i)+1 , (k*i)+2 …. (k*i)+k
    for( int j = k*index +1 ; j<= k*index + k ; j++ ){
      if( j>= len) return;
      cout<<"("<<j<<","<<arr[j]<<")";
    }
    int ii=0;
    for( int j = k*index +1 ; j<= k*index + k ; j++ ){
      //printTree((void *)&j);
      ids[ii] = j;
      pthread_create(&tid[ii], NULL, callPrintTree, (void *)&ids[ii]);
      ii++;      
    }
    for(ii=0;ii<k;ii++){
        pthread_join(tid[ii],NULL);
    }
    //pthread_exit();    
}

// share the same logic from print, did not search root. need a wrapper in the future
int searchTree(int index=0 ){
    int len = n;
    int find = -1;                                      // initialized as not found
    if(index >= len) return -1;                         // out of boundary check
    // Children of the node at index i are at indices (k*i)+1 , (k*i)+2 …. (k*i)+k
    for( int j = k*index +1 ; j<= k*index + k ; j++ ){  // compare k child nodes
      if( j>= len) return -1;                           // out of boundary check
      //cout<<"("<<j<<","<<arr[j]<<")";
      if( key == arr[j]) return j;                      // return if find
    }
    // if doesnt find key from k childs, search child in next level
    for( int j = k*index +1 ; j<= k*index + k ; j++ ){
      find = searchTree(j);
      if( find != -1 ) return find;
    }
    return -1;
}

void* callSearchTree(void *arg ){
    int* ptr = (int*)arg;
    int index = *ptr;  
    //printf("tid: %d\n", *(int *)arg);
    tfind[index-1] = searchTree(index);
    pthread_exit(NULL);
}

int searchTree_pthread(int index=0 ){
    int len = n;
    int find = -1;                                      // initialized as not found
    if(index >= len) return -1;                         // out of boundary check
    // Children of the node at index i are at indices (k*i)+1 , (k*i)+2 …. (k*i)+k
    for( int j = k*index +1 ; j<= k*index + k ; j++ ){  // compare k child nodes
      if( j>= len) return -1;                           // out of boundary check
      //cout<<"("<<j<<","<<arr[j]<<")";
      if( key == arr[j]) return j;                      // return if find
    }
    // if doesnt find key from k childs, search child in next level
    int ii=0;
    for( int j = k*index +1 ; j<= k*index + k ; j++ ){
      //find = searchTree(arr,len,k,key,j);
      ids[ii] = j;
      pthread_create(&tid[ii], NULL, callSearchTree, (void *)&ids[ii]);
      ii++;
      //if( find != -1 ) return find;
    }
    for(ii=0;ii<pthreadsNum;ii++){
        pthread_join(tid[ii],NULL);
        if( tfind[ii] != -1 ) return tfind[ii];
    }
    return -1;
}


// Driver program
int main()
{
    
    buildHeap(arr, n, k);
 
    printf("Built Heap : \n");
    for (int i=0; i<n; i++)
        printf("%d ", arr[i]);
 
    TYPE element = 3;
    insert(arr, &n, k, element);
 
    printf("\n\nHeap after insertion of %d: \n",
            element);
    for (int i=0; i<n; i++)
        printf("%d ", arr[i]);
    cout<<"\n\nHeap Tree:\n"<<endl;

    for(int i=11; i<20;i++){
      element = i;
      insert(arr, &n, k, element);
    }

    printTree();
    cout<<endl<<endl;
    printTree_pthread();

    key = 3;
    auto start = high_resolution_clock::now();
    cout<<"\n\nFind element "<<key<<" at index "<<searchTree()<<endl;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Duration of original search: "<<duration.count() << endl;

     start = high_resolution_clock::now();
    cout<<"\n\nFind element "<<key<<" at index "<<searchTree_pthread()<<endl;
     stop = high_resolution_clock::now();
     duration = duration_cast<microseconds>(stop - start);
    cout << "Duration of pthread search: "<<duration.count() << endl;

    /*printf("\n\nExtracted max is %d",
                   extractMax(arr, &n, k));
 
    printf("\n\nHeap after extract max: \n");
    for (int i=0; i<n; i++)
        printf("%d ", arr[i]);
    */
    for(int i=11; i<capacity-100;i++){
      element = i;
      insert(arr, &n, k, element);
    }
    
    //printf("\n\nHeap after insertion of %d: \n", element);
    //for (int i=0; i<n; i++)
    //    printf("%d ", arr[i]);
    //cout<<"\n\nHeap Tree:\n"<<endl;

    key = 3;
    start = high_resolution_clock::now();
    cout<<"\n\nFind element "<<key<<" at index "<<searchTree()<<endl;
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Duration of original search: "<<duration.count() << endl;

    start = high_resolution_clock::now();
    cout<<"\n\nFind element "<<key<<" at index "<<searchTree_pthread()<<endl;
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Duration of pthread search: "<<duration.count() << endl;

    return 0;
}