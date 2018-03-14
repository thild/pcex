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

__m256 negPixel(float *pixel)
{
  __m256 p = _mm256_load_ps(pixel);
  __m256 max = _mm256_set1_ps(255);
  return _mm256_sub_ps(max, p);
}

int main (int argc, char *argv[])
{
  float *im = (float*)_mm_malloc (sizeof(float) * 64, 32); //aloca um vetor de 32 bytes (256 bits) alinhado em endereços múltiplos de 16 bytes.
  float *im2 = (float*)_mm_malloc (sizeof(float) * 64, 32);

  int i = 0;
  for (i = 0; i < 64; ++i) {
    im[i] = i;
  }

  for(i = 0; i <= 56; i+=8) 
  {
    __m256 pixel = negPixel(&im[i]);
    _mm256_store_ps(&im2[i], pixel);
  }
  
  for (i = 0; i < 64; ++i) {
    printf("%f\t~~~~~~> %f\n", im[i], im2[i]);
  }
  
  _mm_free(im);
  _mm_free(im2);
  
  return 0;
}
