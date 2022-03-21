 
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