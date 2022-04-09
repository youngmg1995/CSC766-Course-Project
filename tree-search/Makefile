CC = g++
EMCC = em++
OPT = -std=c++2a -O3
OPT2 = -s WASM=1 -s NO_DISABLE_EXCEPTION_CATCHING -sASSERTIONS=1   -s LLD_REPORT_UNDEFINED
MULTITHREAD= #-pthread -sPROXY_TO_PTHREAD=1 -sPTHREAD_POOL_SIZE=2 -sEXIT_RUNTIME=1 -sALLOW_MEMORY_GROWTH=1 -sTOTAL_MEMORY=2047MB
SIMDFLAGS = -DSIMD -msimd128 -fPIC -Wno-implicit-function-declaration -msse2  # -s MALLOC=emmalloc
MEM_FLG = -sEXIT_RUNTIME=1 -sALLOW_MEMORY_GROWTH -sTOTAL_MEMORY=2047MB

CFLAGS = $(OPT) $(OPT2) $(MTITHREAD) $(SIMDFLAGS) $(MEM_FLG)

EMCC_CFLAGS		:=  -Wall -std=c++20 -O3
EMCC_LFLAGS 	:= -lm -std=c++20 -s ASSERTIONS=1 -s INITIAL_MEMORY=4294901760 -s NO_DISABLE_EXCEPTION_CATCHING

comp_emcc_simd:
#	export EMCC_CORES=6
	$(EMCC) $(CFLAGS) foo.cpp -o foo.html  --preload-file .data/

comp_emcc:
	$(EMCC) $(OPT) $(OPT2) foo.cpp -o foo.html  --preload-file .data/

# comile for large data, but can not run on node.js or browser ...
comp_emcc_large:
	$(EMCC)  $(EMCC_CFLAGS) $(EMCC_LFLAGS) $(SIMDFLAGS) foo.cpp -o foo.html  --preload-file .data/

comp_cc:
	$(CC) $(OPT) foo.cpp -o foo.out

run_emcc: 
	node --experimental-wasm-simd --experimental-wasm-threads --experimental-wasm-modules --experimental-wasm-bulk-memory --wasm-simd-post-mvp foo.js

run_cc:
	./foo.out

server:
	echo "http://localhost:8000/"
	python3 -m http.server	

clean:
	rm -rf *.js *.wasm *.html
