CC = emcc
OPT = -std=c++11 
SIMD = -msimd128
MULTITHREAD= -pthread -s PROXY_TO_PTHREAD EXIT_RUNTIME=1 #-s ALLOW_MEMORY_GROWTH=1
CFLAGS = $(OPT) $(MULTITHREAD)


comp:
	export EMCC_CORES=6
	emcc -pthread -s PTHREAD_POOL_SIZE=4 -s EXIT_RUNTIME=1 example.c -o example.js 

comp2:
	emcc -pthread -s PTHREAD_POOL_SIZE=4 -s EXIT_RUNTIME=1 example.cpp -o example.js

run: 
	node --experimental-wasm-threads example.js

server:
	echo "http://localhost:8000/"
	python3 -m http.server	

clean:
	rm -rf *.js *.wasm *.html


# comp3 & run3 works correct!

comp3:
	emcc -fPIC -Wno-implicit-function-declaration -msse2 -msimd128 -experimental-wasm-simd  foo.cpp -o foo.js

run3:
	node --experimental-wasm-simd foo.js