#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <immintrin.h>
// gcc escalarParalelo.c -o escalarParalelo -mavx -O3
#define size  200000

void produtoEscalar();

int main(){
    clock_t tic = clock();

    produtoEscalar();

    clock_t toc = clock();
    
    printf("Elapsed: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);
    
    return 0;
}

void produtoEscalar()
{
    float *In = (float*)_mm_malloc (sizeof(float) * size, 32); //aloca um vetor de 32 bytes (256 bits) alinhado em endereços múltiplos de 16 bytes.
    float *Out = (float*)_mm_malloc (sizeof(float) * size, 32);
    float *mult = (float*)_mm_malloc (sizeof(float) * 8, 32);
    mult[0] = 1;
    mult[1] = 2;
    mult[2] = 3;

    int i=0, j=0, k=0;

    for(i=0; i<size;i++)
    {
        Out[i] = 0;
    }

    __m256 vetIn = _mm256_load_ps(In);
    __m256 vetOut = _mm256_load_ps(Out);
    __m256 Vmult = _mm256_load_ps(mult);

    for(i=0; i<size-8; i+=8){
        for(j=0; j<3;j++){
            vetOut += _mm256_mul_ps(vetIn, Vmult);
            // _mm256_store_ps(imgOut, vimgOut); 
        }
    }
}