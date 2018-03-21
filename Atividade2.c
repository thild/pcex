#include <stdio.h>

#include <immintrin.h> // AVX

void add_intel_intrinsics(float *imgIn, float *imgOut, __m256 bright)
{
  __m256 vimgIn = _mm256_load_ps (imgIn);
  __m256 vimgOut = _mm256_add_ps (vimgIn, bright);
  _mm256_store_ps(imgOut, vimgOut); 
}

int main (int argc, char *argv[])
{
  float *imgIn = (float*)_mm_malloc (sizeof(float) * 128, 32); //aloca um vetor de 32 bytes (256 bits) alinhado em endereços múltiplos de 16 bytes.
  float *imgOut = (float*)_mm_malloc (sizeof(float) * 128, 32);
  __m256 bright = _mm256_set1_ps(20);
  
  int i = 0;
  
   for (i = 0; i < 128; ++i) {
     imgIn[i] = i;
   }
  
  printf("\nExecutando\n");

    for(i = 0; i<=128-8; i+=8)
    {
      add_intel_intrinsics(&imgIn[i], &imgOut[i], bright);   
    }
   
  
  for (i = 0; i < 128; ++i) {
    printf("%f\n", imgOut[i]);
  }
  
  _mm_free(imgIn);
  _mm_free(imgOut);
}
  