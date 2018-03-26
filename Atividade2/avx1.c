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


#define VECTOR_SIZE 64

typedef float v8sf __attribute__ ((vector_size(sizeof(float)*VECTOR_SIZE))); 



void add_intel_intrinsics(float *y, float *w)
{
  __m256 vy = _mm256_load_ps (y);
  __m256 vw = _mm256_load_ps (w);
 
 
}



int main (int argc, char *argv[])
{
  float *y = (float*)_mm_malloc (sizeof(float) * VECTOR_SIZE, 32); //aloca um vetor de 32 bytes (256 bits) alinhado em endereços múltiplos de 16 bytes.
  float *w = (float*)_mm_malloc (sizeof(float) * VECTOR_SIZE, 32);
  
  
  
  int i = 0;
  
  for (i = 0; i < VECTOR_SIZE; ++i) {
    y[i] = i;
    w[i] = i;
  }
    
  
  __m256 d = {10, 10, 10, 10, 10, 10, 10, 10}; // mascara que vai modificar o vetor
  
    

  for (i = 0; i < VECTOR_SIZE - 7; i+=8) { //divide o vetor em pedaços de tamanho 8, para modificar cada pedaço separadamente
    __m256 vy = _mm256_load_ps(&y[i]); // y= imagem
    __m256 vw = vy * d; // resultado = imagem * mascara
    _mm256_store_ps(&w[i],vw);
  }

  for (i = 0; i < VECTOR_SIZE; i++) { //divide o vetor em pedaços de tamanho 8, para modificar cada pedaço separadamente
    printf("%f\n", w[i]);
  }
  
  return 0;
} 