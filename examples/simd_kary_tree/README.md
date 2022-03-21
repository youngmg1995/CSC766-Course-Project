 
# accelerate searching of k-ary Heap tree using wasm SIMD instructions

 author: Zong-Ru Li
 
 date:  3/21/2022
 
 edition: v1.0
 
 description: 
compare 4 child nodes from the same parent node using wasm_i32x4_eq instruction, and then use wasm_i32x4_bitmask filter output into 4 bit

|||
|---|---|
|  data storage structure|   static array|
| tree type|     Max 4-ary heap|

 
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
Search element 3.<br> 
Find element 3 at index 415061.
||microseconds|
|---|---|
|Duration of original search| 540|
|Duration of SIMD search| 312|

## 4. TBD
Currently I can not compile code in larger order of static array. <br>
emcc compiler will throw error cause it run out of initial memory location.