/*
Exemplo de código AVX utilizando Intel instrinsics e gcc built-in functions

Compile usando:
gcc avx.c -o avx -mavx -O3


http://www.songho.ca/misc/sse/sse.html

https://gcc.gnu.org/onlinedocs/gcc-4.9.2/gcc/X86-Built-in-Functions.html#X86-Built-in-Functions
https://gcc.gnu.org/onlinedocs/gcc-4.9.2/gcc/Vector-Extensions.html#Vector-Extensions
https://software.intel.com/sites/landingpage/IntrinsicsGuide/
https://msdn.microsoft.com/en-us/library/26td21ds.aspx

AVX
https://software.intel.com/en-us/articles/introduction-to-intel-advanced-vector-extensions/

*/

#include <stdio.h>

#include <immintrin.h> // AVX


#define VECTOR_SIZE         8
typedef float v8sf __attribute__ ((vector_size(sizeof(float)*VECTOR_SIZE))); 

typedef union f4vector
{
    v8sf    v;
    float   f[VECTOR_SIZE];
} f4vector;


void add_intel_intrinsics(float *a, float *b, float *c)
{
  __m256 va = _mm256_load_ps (a);
  __m256 vb = _mm256_load_ps (b);
  __m256 vc = _mm256_add_ps (va, vb);
  _mm256_store_ps(c, vc);

  /* Equivalente Assembly 
  ** mov eax, a
  ** mov edx, b 
  ** mov ecx, c
  ** movaps xmm0, XMMWORD PTR [eax]
  ** addps xmm0, XMMWORD PTR [edx]
  ** movaps XMMWORD PTR [ecx], xmm0
  */
}


v8sf add_gcc_builtin(v8sf a, v8sf b)
{
  return __builtin_ia32_addps256 (a, b);
}



int main (int argc, char *argv[])
{
  float *a = (float*)_mm_malloc (sizeof(float) * VECTOR_SIZE, 32); //aloca um vetor de 32 bytes (256 bits) alinhado em endereços múltiplos de 16 bytes.
  float *b = (float*)_mm_malloc (sizeof(float) * VECTOR_SIZE, 32);
  float *c = (float*)_mm_malloc (sizeof(float) * VECTOR_SIZE, 32);
  
  int i = 0;
  
  for (i = 0; i < VECTOR_SIZE; ++i) {
    a[i] = i;
    b[i] = i;
  }
  
  printf("\nIntel AVX\n");
  
  add_intel_intrinsics(a, b, c);
  
  for (i = 0; i < VECTOR_SIZE; ++i) {
    printf("%f\n", c[i]);
  }
  
  _mm_free(a);
  _mm_free(b);
  _mm_free(c);
  
  
  
  printf("\nGCC Built-in Functions\n");
  
  v8sf d, e, f;

  d = (v8sf){0, 1, 2, 3, 4, 5, 6, 7};
  e = (v8sf){0, 1, 2, 3, 4, 5, 6, 7};
  f = add_gcc_builtin(d, e);  

  for (i = 0; i < VECTOR_SIZE; ++i) {
    printf("%f\n", f[i]);
  }
  
  
  printf("\nGCC implicity vectorization\n");
  
  f = d + e;  

  for (i = 0; i < VECTOR_SIZE; ++i) {
    printf("%f\n", f[i]);
  }

  return 0;
}
