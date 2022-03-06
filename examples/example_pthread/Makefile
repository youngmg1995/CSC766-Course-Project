CC = emcc
OPT = -std=c++11 
SIMD = -msimd128
MULTITHREADFLAG= -pthread -s PTHREAD_POOL_SIZE=4 EXIT_RUNTIME=1
CFLAGS = $(OPT) $(MULTITHREADFLAG)


comp:
	export EMCC_CORES=6
	$(CC) $(CFLAGS) example.c -o example.js 

comp2:
	$(CC) $(CFLAGS) example.cpp -o example.js

run: 
	node --experimental-wasm-threads example.js

server:
	echo "http://localhost:8000/"
	python3 -m http.server	

clean:
	rm -rf *.js *.wasm *.html


