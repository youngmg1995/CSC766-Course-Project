// C++ program for SIMD example
#include <iostream>
using namespace std;

#include <wasm_simd128.h>

//#define TEST_TRANSPOSE

// https://v8.dev/features/simd
// https://stackoverflow.com/questions/66908027/emscripten-how-can-i-compile-a-c-file-with-an-intrinsic-header-like-immintrin-h

/*void multiply_arrays(int* out, int* in_a, int* in_b, int size) {
  for (int i = 0; i < size; i++) {
    out[i] = in_a[i] * in_b[i];
  }
}*/

void multiply_arrays(int* out, int* in_a, int* in_b, int size) {
  for (int i = 0; i < size; i += 4) {
    v128_t a = wasm_v128_load(&in_a[i]);
    v128_t b = wasm_v128_load(&in_b[i]);
    v128_t prod = wasm_i32x4_mul(a, b);
    wasm_v128_store(&out[i], prod);
  }
}

#ifdef TEST_TRANSPOSE
void transpose4x4(int matrix[16]) {
	const v128_t row0 = wasm_v128_load(matrix);
	const v128_t row1 = wasm_v128_load(matrix + 4);
	const v128_t row2 = wasm_v128_load(matrix + 8);
	const v128_t row3 = wasm_v128_load(matrix + 12);

	const v128_t tmp0 = wasm_v32x4_shuffle(row0, row1, 0, 4, 1, 5);
	const v128_t tmp1 = wasm_v32x4_shuffle(row2, row3, 0, 4, 1, 5);
	const v128_t tmp2 = wasm_v32x4_shuffle(row0, row1, 2, 6, 3, 7);
	const v128_t tmp3 = wasm_v32x4_shuffle(row2, row3, 2, 6, 3, 7);

	const v128_t col0 = wasm_v32x4_shuffle(tmp0, tmp1, 0, 1, 4, 5);
	const v128_t col1 = wasm_v32x4_shuffle(tmp0, tmp1, 2, 3, 6, 7);
	const v128_t col2 = wasm_v32x4_shuffle(tmp2, tmp3, 0, 1, 4, 5);
	const v128_t col3 = wasm_v32x4_shuffle(tmp2, tmp3, 2, 3, 6, 7);

	wasm_v128_store(matrix, col0);
	wasm_v128_store(matrix + 4, col1);
	wasm_v128_store(matrix + 8, col2);
	wasm_v128_store(matrix + 12, col3);
}
#endif

void printArray( int* arr, int size ){
  for(int i=0;i<size;i++) cout<<arr[i]<<" ";
      cout<<endl;
}
/* Driver program to test above functions*/
int main()
{
    int out[16];
    int in_a[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    int in_b[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    int size=16;

    
    printArray(out,size);
    multiply_arrays( out, in_a, in_b, size);
    printArray(out,size);
    
#ifdef TEST_TRANSPOSE
    transpose4x4(out);
    printArray(out,size);
#endif

	cout << "\nEnd of task\n";
    return 0;
}