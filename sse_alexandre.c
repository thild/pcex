/*
Exemplo de código SSE utilizando Intel instrinsics e gcc built-in functions

Compile usando:
gcc sse_alexandre.c -o sse_alexandre -msse -msse4.2 -O3


http://www.songho.ca/misc/sse/sse.html

https://gcc.gnu.org/onlinedocs/gcc-4.9.2/gcc/X86-Built-in-Functions.html#X86-Built-in-Functions
https://gcc.gnu.org/onlinedocs/gcc-4.9.2/gcc/Vector-Extensions.html#Vector-Extensions
https://software.intel.com/sites/landingpage/IntrinsicsGuide/
https://msdn.microsoft.com/en-us/library/26td21ds.aspx

AVX
https://software.intel.com/en-us/articles/introduction-to-intel-advanced-vector-extensions/

*/

#include <stdio.h>

#include <xmmintrin.h> // SSE (Required to use the __m128, and __m128d type)
#include <emmintrin.h> // SSE2 (Required to use the __m128i type)
#include <pmmintrin.h> // SSE3
#include <smmintrin.h> // SSE4.1


#define IMAGE_WIDTH         8
#define IMAGE_HEIGHT        8


void calculate_intel_intrinsics(float *b) {
  __m128 vc = _mm_set1_ps(10);
float *vector;
vector = b;
int i;
  for (i = 0; i < IMAGE_WIDTH * IMAGE_HEIGHT; i+=4) {
    __m128 img = _mm_load_ps(vector);
    __m128 vr = _mm_add_ps(img, vc);
    _mm_store_ps(vector, vr);
    vector += 4;
  }

}


int main (int argc, char *argv[]) {
  float *image __attribute__ ((aligned(16))) = (float*)malloc (sizeof(float) * IMAGE_WIDTH * IMAGE_HEIGHT);

  int i, x, y;
  i = 0;
  
  printf("\nOriginal image\n");

  for (y = 0; y < IMAGE_HEIGHT; ++y) {
    for (x = 0; x < IMAGE_WIDTH; ++x) {
      image[i] = 1;
      printf("%.2f ", image[i]);
      ++i;
     }
     printf("\n");
  }


  printf("\nIntel SSE image calculate\n");

  calculate_intel_intrinsics(image);

  i = 0;

  for (y = 0; y < IMAGE_HEIGHT; ++y) {
    for (x = 0; x < IMAGE_WIDTH; ++x) {
      printf("%.2f ", image[i]);
      ++i;
    }
    printf("\n");
  }

}
