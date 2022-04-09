 
# accelerate searching of k-ary tree using wasm SIMD instructions

 author: Zong-Ru Li
 
 date:  3/21/2022
 
 edition: v1.0
 
 description: 
compare 8 child nodes from the same parent node using wasm_i16x8_eq instruction, and then use wasm_i16x8_bitmask filter output into 8 bit

|||
|---|---|
|  data storage structure|   dynamic array|
| tree type|     k-ary tree|

## 0. environment setup
1. create a folder in current directory
2. put dataset under .data folder
 
## 1. check wasm comiler work correctly
```
emcc -v
```
## 2. compile and run example
```
make comp_emcc_simd
make run_emcc
```
or execute python local server and open html in browser.

```
make comp_cc
make run_cc
```

## 3. result
to be done.<br> 
||microseconds|
|---|---|
|Duration of original search| |
|Duration of SIMD search| |

## 4. TBD
1. Currently I can not run code with big data base. <br>
    I can successfully compiled but it failed while executing using node command or using browser. they all throw exceptions due to memory allocation limit.<br>
```
foo.js:1 Cannot enlarge memory, asked to go up to 2147487744 bytes, but the limit is 2147483648 bytes!
```
2. simd only speed up a little bit, sometime even getting worse.