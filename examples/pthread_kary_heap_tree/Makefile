CC = emcc
OPT = -std=c++11 
SIMD = -msimd128
MULTITHREAD= -pthread -s PROXY_TO_PTHREAD EXIT_RUNTIME=1 #-s ALLOW_MEMORY_GROWTH=1
CFLAGS = $(OPT) $(MULTITHREAD)


comp:
	export EMCC_CORES=6
	emcc -pthread -s ALLOW_MEMORY_GROWTH=1 -s PTHREAD_POOL_SIZE=12 -s EXIT_RUNTIME=1 -O3 example.cpp -o example.js 

comp2:
	export EMCC_CORES=6
	emcc -pthread -s ALLOW_MEMORY_GROWTH=1 -s PROXY_TO_PTHREAD=1 -s PTHREAD_POOL_SIZE=12 -s EXIT_RUNTIME=1 -O3 example2.cpp -o example.js

run: 
	node --experimental-wasm-threads example.js

server:
	echo "http://localhost:8000/"
	python3 -m http.server	

clean:
	rm -rf *.js *.wasm *.html
