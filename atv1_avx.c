/*
Exemplo de código AVX utilizando Intel instrinsics e gcc built-in functions

Compile usando:
gcc atv1_avx.c -o 1 -mavx -O3


http://www.songho.ca/misc/sse/sse.html

https://gcc.gnu.org/onlinedocs/gcc-4.9.2/gcc/X86-Built-in-Functions.html#X86-Built-in-Functions
https://gcc.gnu.org/onlinedocs/gcc-4.9.2/gcc/Vector-Extensions.html#Vector-Extensions
https://software.intel.com/sites/landingpage/IntrinsicsGuide/
https://msdn.microsoft.com/en-us/library/26td21ds.aspx

AVX
https://software.intel.com/en-us/articles/introduction-to-intel-advanced-vector-extensions/

*/

#include <stdio.h>
#include <time.h>

#include <immintrin.h> // AVX

#define VECTOR_SIZE 64

void add_intel_intrinsics(float *a)
{
    int i;
    for (i = 0; i <= VECTOR_SIZE; i += 8)
    {
        __m256 va = _mm256_load_ps(&a[i]);
        __m256 vi = _mm256_set1_ps(255);
        va = vi - va;

        _mm256_store_ps(&a[i], va);
    }
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    float *a = (float *)_mm_malloc(sizeof(float) * VECTOR_SIZE, 64 * 32); //aloca um vetor de 32 bytes (256 bits) alinhado em endereços múltiplos de 16 bytes.

    int i = 0;

    for (i = 0; i < VECTOR_SIZE; ++i)
    {
        a[i] = rand() % 256;
    }

    for (i = 0; i <= 56; i += 8)
    {
        add_intel_intrinsics(&a[i]);
    }

    for (i = 0; i < VECTOR_SIZE; ++i)
    {
        printf("%f\n", a[i]);
    }

    _mm_free(a);

    return 0;
}