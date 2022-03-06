# CSC766-Project

# step 1: 

install emsdk

```
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk
./emsdk install latest
./emsdk activate latest
source ./emsdk_env.sh
```

verify your installation is correct
```
emcc -v
cd upstream/emscripten
tests/runner test_loop
```

# step 2: download this repo and run example

```
git clone https://github.ncsu.edu/mgyoung/CSC766-Project
cd examples/example_simd
make comp
make run
cd ../example_pthread
make comp
make run
make comp2
make run
```

