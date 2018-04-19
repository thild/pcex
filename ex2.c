#include <stdio.h>

#include <immintrin.h>

void crepusculo(float *imgin, float *imgout, __m256 intens)
{
  __m256 vimgin = _mm256_load_ps (imgin);
  __m256 vimgout = _mm256_add_ps (vimgin, intens);
  _mm256_store_ps(imgout, vimgout);

  /* Equivalente Assembly 
  ** mov eax, a
  ** mov edx, b 
  ** mov ecx, c
  ** movaps xmm0, XMMWORD PTR [eax]
  ** addps xmm0, XMMWORD PTR [edx]
  ** movaps XMMWORD PTR [ecx], xmm0
  */
}

int main (int argc, char *argv[])
{

    __m256 intens = _mm256_set1_ps(50);

  float *imgin = (float*)_mm_malloc (sizeof(float) *96, 32); //aloca um vetor de 32 bytes (256 bits) alinhado em endereços múltiplos de 16 bytes.
  float *imgout = (float*)_mm_malloc (sizeof(float) *96, 32);
  
  int i = 0;
  
    for (i = 0; i < 96; ++i) {
      imgin[i] = i;
    }

  for (i = 0; i <= 96 - 8; i+=8) {
      crepusculo(&imgin[i], &imgout[i], intens);
  }

  printf("Vai da certo");

      for (i = 0; i < 96; ++i) {
        printf("%f\n",imgout[i]);
      }

  }