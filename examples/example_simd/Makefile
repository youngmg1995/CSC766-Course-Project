CC = emcc
OPT = -std=c++11 
SIMDFLAGS = -fPIC -Wno-implicit-function-declaration -msse2 -msimd128 -experimental-wasm-simd
CFLAGS = $(OPT) $(SIMDFLAGS)

comp:
	$(CC) $(CFLAGS) foo.cpp -o foo.js

run:
	node --experimental-wasm-simd foo.js

clean:
	rm -rf *.js *.wasm *.html

server:
	echo "http://localhost:8000/"
	python3 -m http.server	

