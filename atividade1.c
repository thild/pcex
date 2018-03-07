/*
Arquiteturas SIMD - Atividade 2 - Implementação

Implemente um algoritmo de processamento de imagens utilizando as extensões de vetor SSE ou AVX.

    Modele sua imagem como um vetor unidimensional de floats em escala de cinza.
        Utilize a função y * w + x para acessar os pixels.
    A imagem deve conter largura em bytes (stride) múltiplos de 16 bytes para manter o alinhamento.
        Nota: A largura visível da imagem não precisa necessariamente ter largura múltipla de 16 bytes.
    O trabalho deve ser enviado como pull request no github.

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



void pdiNegativo(float *a)
{
  for(int i=0;i<=64-8;i+=8)
  {
    __m256 va = _mm256_load_ps (&a[i]);
    __m256 vi = _mm256_set1_ps (255);
    //operações com os vetores utilizando o vi
    va = vi - va;
    _mm256_store_ps(&a[i], va);
  }
}




int main (int argc, char *argv[])
{
  float *a = (float*)_mm_malloc (sizeof(float) * 64, 32); //aloca um vetor de 32 bytes (256 bits) alinhado em endereços múltiplos de 16 bytes.
  float *b = (float*)_mm_malloc (sizeof(float) * 64, 32);
  float *c = (float*)_mm_malloc (sizeof(float) * 64, 32);
  
  int i = 0;
  
  for (i = 0; i < 64; ++i) {
    a[i] = i;
  }
  
  pdiNegativo(a);

   for (i = 0; i < 64; ++i) {
    printf("%f\n", a[i]);
   }
 
  return 0;
}
