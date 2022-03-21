CC = emcc
OPT = -std=c++11 
SIMDFLAGS = -fPIC -Wno-implicit-function-declaration -msse2 -msimd128 -s EXIT_RUNTIME=1
CFLAGS = $(OPT) $(SIMDFLAGS)

comp:
	$(CC) $(CFLAGS) -O3 foo.cpp -o foo.js

run:
	node --experimental-wasm-simd --wasm-simd-post-mvp foo.js 

clean:
	rm -rf *.js *.wasm *.html

server:
	echo "http://localhost:8000/"
	python3 -m http.server	

