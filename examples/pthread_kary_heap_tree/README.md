 
# accelerate searching of k-ary Heap tree using wasm multithread

 author: Zong-Ru Li
 
 date:  3/21/2022
 
 edition: v1.0
 
 description: 
assume using k threads for searching. the program will build a k-ary Max heap tree.
tree root has k child nodes. The search function will assign each child node to a single thread.
Each thread is independent and access different part of tree storage array.

|||
|---|---|
|  data storage structure|   static array|
| tree type|     Max k-ary heap|

 
## 1. check wasm comiler work correctly
```
emcc -v
```
## 2. compile and run example
```
make comp
make run
```

## 3. result
this is the output for 1 time execution, timing differ in each run. this experiment is running on Windows Subsystem Linux with ubuntu 20.04.

<br>
Search element 3.<br> 
Find element 3 at index  147037.

||microseconds|
|---|---|
|Duration of original search| 2614|
|Duration of pthread search| 1492|

## 4. TBD
1. Currently I can not compile code in larger order of static array. <br>
emcc compiler will throw error cause it run out of initial memory location.
2. repeat experiment, calculating average speed up using multithread.