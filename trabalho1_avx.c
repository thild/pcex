/*
Exemplo de código AVX utilizando Intel instrinsics e gcc built-in functions

Compile usando:
gcc trabalho1_avx.c -o 1 -mavx -O3


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

#define VECTOR_SIZE 3

void produtoEscalarEz(float *a, float *b, float *c)
{
    __m256 va = _mm256_load_ps(a);
    __m256 vb = _mm256_load_ps(b);
    __m256 vc = _mm256_dp_ps(va, vb, 241); // esse 241 quando taca em binario vira um numero que diz pra taca no final do vetor (1111 0001)

    _mm256_store_ps(c, vc);
}

void produtoEscalarNotEz(float *a, float *b, float *c)
{
    __m256 va = _mm256_load_ps(a);
    __m256 vb = _mm256_load_ps(b);
    __m256 vc = _mm256_mul_ps(va, vb);

    vc = _mm256_hadd_ps(vc, vc);
    vc = _mm256_hadd_ps(vc, vc);

    vc = _mm256_shuffle_ps(vc, vc, 3);

    _mm256_store_ps(c, vc);
    // pra soma fazer 2 hadd e depois shufa
}

int main(int argc, char *argv[])
{
    float *a = (float *)_mm_malloc(sizeof(float) * VECTOR_SIZE, 64 * 32); //aloca um vetor de 32 bytes (256 bits) alinhado em endereços múltiplos de 16 bytes.
    float *b = (float *)_mm_malloc(sizeof(float) * VECTOR_SIZE, 64 * 32);
    float *c = (float *)_mm_malloc(sizeof(float) * VECTOR_SIZE, 64 * 32);

    int i = 0;

    for (i = 0; i < VECTOR_SIZE; ++i)
    {
        a[i] = i;
        b[i] = i;
    }

    produtoEscalarNotEz(a, b, c);

    for (i = 0; i < VECTOR_SIZE; ++i)
    {
        printf("%f\n", c[i]);
    }

    _mm_free(a);
    _mm_free(b);
    _mm_free(c);

    return 0;
}