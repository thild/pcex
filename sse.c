/*
Exemplo de código SSE utilizando Intel instrinsics e gcc built-in functions

Compile usando:
gcc sse.c -o sse -msse -msse4.2


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

#define VECTOR_SIZE         4
typedef float v4sf __attribute__ ((vector_size(sizeof(float)*VECTOR_SIZE))); 

typedef union f4vector
{
    v4sf    v;
    float   f[VECTOR_SIZE];
} f4vector;

void add_intel_intrinsics(float *a, float *b, float *c)
{
  __m128 va = _mm_load_ps (a);
  __m128 vb = _mm_load_ps (b);
  __m128 vc = _mm_add_ps (va, vb);
  _mm_store_ps(c, vc);

  /* Equivalente Assembly 
  ** mov eax, a
  ** mov edx, b 
  ** mov ecx, c
  ** movaps xmm0, XMMWORD PTR [eax]
  ** addps xmm0, XMMWORD PTR [edx]
  ** movaps XMMWORD PTR [ecx], xmm0
  */
}


v4sf add_gcc_builtin(v4sf a, v4sf b)
{
  return __builtin_ia32_addps (a, b);
}



int main (int argc, char *argv[])
{
  float *a __attribute__ ((aligned(16))) = (float*)malloc (sizeof(float) * 4); //aloca um vetor de 16bytes (128bits) alinhado em endereços múltiplos de 16bytes.
  float *b __attribute__ ((aligned(16))) = (float*)malloc (sizeof(float) * 4);
  float *c __attribute__ ((aligned(16))) = (float*)malloc (sizeof(float) * 4);
  
  int i = 0;
  
  for (i = 0; i < 4; ++i) {
    a[i] = i;
    b[i] = i;
  }
  
  printf("Intel Intrinsics\n");
  
  add_intel_intrinsics(a, b, c);

  for (i = 0; i < 4; ++i) {
    printf("%f\n", c[i]);
  }
  
  free(a);
  free(b);
  free(c);
  

  printf("\nGCC Built-in Functions\n");
  
  v4sf d, e, f;

  d = (v4sf){2, 2, 3, 4};
  e = (v4sf){2, 2, 3, 4};
  f = d + e;  

  for (i = 0; i < 4; ++i) {
    printf("%f\n", f[i]);
  }

  return 0;
}
