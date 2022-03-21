// =====================================================================================
// accelerate searching of k-ary Heap tree using wasm SIMD instructions
// author: Zong-Ru Li
// date:  3/21/2022
// edition: v1.0
// description: 
//              data storage structure:   static array
//              tree type:                Max 4-ary heap
//              compare 4 child nodes from the same parent node using wasm_i32x4_eq instruction,
//              and then use wasm_i32x4_bitmask filter output into 4 bit
// =====================================================================================

#include <iostream>
using namespace std;

#include <chrono>
using namespace std::chrono;

#include <wasm_simd128.h>

// https://v8.dev/features/simd
// https://stackoverflow.com/questions/66908027/emscripten-how-can-i-compile-a-c-file-with-an-intrinsic-header-like-immintrin-h

/*void multiply_arrays(int* out, int* in_a, int* in_b, int size) {
  for (int i = 0; i < size; i++) {
    out[i] = in_a[i] * in_b[i];
  }
}*/

void multiply_arrays(int* out, int* in_a, int* in_b, int size) {
  for (int i = 0; i < size; i += 4) {
    v128_t a = wasm_v128_load(&in_a[i]);
    v128_t b = wasm_v128_load(&in_b[i]);
    v128_t prod = wasm_i32x4_mul(a, b);
    wasm_v128_store(&out[i], prod);
  }
}

//_mm_cmpeq_epi8
#define TYPE int

void cmp_arrays(TYPE* out,TYPE* in_a, TYPE* key, int size){
  for (int i = 0; i < size; i += 4) {
    v128_t a = wasm_v128_load(&in_a[i]);
    v128_t b = wasm_v128_load(&key[0]);
    //v128_t cmp = wasm_i8x16_eq(a, b);
    v128_t cmp = wasm_i32x4_eq(a, b);
    //uint16_t mask = wasm_i8x16_bitmask(cmp);
    uint16_t mask = wasm_i32x4_bitmask(cmp);
    wasm_v128_store(&out[i], cmp);    
    cout<<mask<<endl;
  }
}
/*
void cmp_arrays_4(TYPE* out,TYPE* in_a, TYPE* key){
  //for (int i = 0; i < size; i += 4) {
    v128_t a = wasm_v128_load(&in_a[0]);
    v128_t b = wasm_v128_load(&key[0]);
    //v128_t cmp = wasm_i8x16_eq(a, b);
    v128_t cmp = wasm_i32x4_eq(a, b);
    //uint16_t mask = wasm_i8x16_bitmask(cmp);
    uint16_t mask = wasm_i32x4_bitmask(cmp);
    wasm_v128_store(&out[0], cmp);    
    cout<<mask<<endl;
  //}
}
*/
int cmp_arrays_4(TYPE* in_a, TYPE* key){

    v128_t a = wasm_v128_load(&in_a[0]);
    v128_t b = wasm_v128_load(&key[0]);
    //v128_t cmp = wasm_i8x16_eq(a, b);
    v128_t cmp = wasm_i32x4_eq(a, b);
    //uint16_t mask = wasm_i8x16_bitmask(cmp);
    uint16_t mask = wasm_i32x4_bitmask(cmp);
    //wasm_v128_store(&out[0], cmp);    
    //cout<<mask<<endl;
    if(mask & 1) return 0;
    if(mask & 2) return 1;
    if(mask & 4) return 2;
    if(mask & 8) return 3;
    return -1;

}

void printArray( TYPE* arr, int size ){
  for(int i=0;i<size;i++) cout<<(int)arr[i]<<" ";
      cout<<endl;
}
/* Driver program to test above functions*/
/*int main()
{
    TYPE out[16];
    TYPE in_a[16] = {5,0,0,3,1,1,3,0,1,0,0,1,3,1,1,0};
    TYPE key[4] = {3,3,3,3};
    int size=16;

    printArray(in_a,size);
    printArray(key,4);
    printArray(out,size);
    //cmp_arrays( out, in_a, key, size);
    int idx = cmp_arrays_4( out, in_a, key);
    cout<<"\n\nFind at index: "<<idx<<endl;
    printArray(out,size);

	cout << "\nEnd of task\n";
    return 0;
}*/


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
// att[] -- Array that stores heap
// len   -- Size of array
// index -- index of element to be restored
//          (or heapified)
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
void printTree(TYPE arr[], int len, int k, int index=0 ){

    if(index >= len) return;
    // Children of the node at index i are at indices (k*i)+1 , (k*i)+2 …. (k*i)+k
    for( int j = k*index +1 ; j<= k*index + k ; j++ ){
      if( j>= len) return;
      cout<<"("<<j<<","<<arr[j]<<")";
    }
    for( int j = k*index +1 ; j<= k*index + k ; j++ ){
      printTree(arr,len,k,j);
    }
}
// share the same logic from print, did not search root. need a wrapper in the future
int searchTree(TYPE arr[], int len, int k, TYPE key, int index=0 ){
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
      find = searchTree(arr,len,k,key,j);
      if( find != -1 ) return find;
    }
    return -1;
}

int searchTree_4(TYPE arr[], int len, TYPE key[], int index=0 ){
    int find = -1;
    int k =4;
    if(index >= len) return -1;
    // Children of the node at index i are at indices (k*i)+1 , (k*i)+2 …. (k*i)+k
    // format of SIMD search function: int cmp_arrays_4(TYPE* out,TYPE* in_a, TYPE* key)
    // if remain child node less than 4, use original search algorithm
    if( k*index + k >= len) {
      for( int j = k*index +1 ; j<= k*index + k ; j++ ){
        if( j>= len) return -1;
        if( key[0] == arr[j]) return j;
      }
    } else { // if remain child nodes more or equal to 4, use SIMD search function
          find = cmp_arrays_4( &arr[ k*index +1 ], key );
          if( find != -1 ) return k*index +1+ find;
    }
    for( int j = k*index +1 ; j<= k*index + k ; j++ ){
      find = searchTree_4(arr,len,key,j);
      if( find != -1 ) return find;
    }
    return -1;
}

// Driver program
int main()
{
    const int capacity = 1000000;
    TYPE arr[capacity] = {4, 5, 6, 7, 8, 9, 10};
    int n = 7;
    int k = 4;
    TYPE key[4] = {3,3,3,3};

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
    printTree(arr, n, k);

    auto start = high_resolution_clock::now();
    cout<<"\n\nFind element "<<element<<" at index "<<searchTree(arr,n,k,element)<<endl;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Duration of original search: "<<duration.count() << endl;

     start = high_resolution_clock::now();
    cout<<"\n\nFind element "<<element<<" at index "<<searchTree_4(arr,n,key)<<endl;
     stop = high_resolution_clock::now();
     duration = duration_cast<microseconds>(stop - start);
    cout << "Duration of SIMD search: "<<duration.count() << endl;

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

    element = 3;
    start = high_resolution_clock::now();
    cout<<"\n\nFind element "<<element<<" at index "<<searchTree(arr,n,k,element)<<endl;
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Duration of original search: "<<duration.count() << endl;

    start = high_resolution_clock::now();
    cout<<"\n\nFind element "<<element<<" at index "<<searchTree_4(arr,n,key)<<endl;
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Duration of SIMD search: "<<duration.count() << endl;

    return 0;
}
