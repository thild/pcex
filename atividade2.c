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
#include <time.h>
#include <immintrin.h> // AVX

void produtoEscalar1(float *a, float *b, float *c){

   __m256 va = _mm256_load_ps (a);
   __m256 vb = _mm256_load_ps (b); 
   __m256 vc = _mm256_dp_ps(va,vb,241);
   _mm256_store_ps(c, vc);

}

void produtoEscalar2(float *a, float *b, float *c){
    
   __m256 va = _mm256_load_ps (a);
   __m256 vb = _mm256_load_ps (b); 
   __m256 vc = _mm256_mul_ps(va,vb); // multiplica

   _mm256_store_ps(c, vc);

  float *d = (float*)_mm_malloc (sizeof(float) * 64, 32);
  float *e = (float*)_mm_malloc (sizeof(float) * 64, 32);
  float *f = (float*)_mm_malloc (sizeof(float) * 64, 32);
  float *g = (float*)_mm_malloc (sizeof(float) * 64, 32);

  int i = 0;
  
  for (i = 0; i < 4; ++i) {
    d[i] = c[0];
    e[i] = c[1];
    f[i] = c[2];
    g[i] = c[3];
   
  }

   __m256 vd = _mm256_load_ps (d);
   __m256 ve = _mm256_load_ps (e);
   __m256 vf = _mm256_load_ps (f);
   __m256 vg = _mm256_load_ps (g);

   __m256 vh =  _mm256_add_ps(vd,ve);
   __m256 vi = _mm256_add_ps(vf,vg);
   __m256 final = _mm256_add_ps(vh,vi);

   _mm256_store_ps(c, final); 

}

void produtoEscalar3(float *a, float *b, float *c){
    
   __m256 va = _mm256_load_ps (a);
   __m256 vb = _mm256_load_ps (b); 
   __m256 vc = _mm256_mul_ps(va,vb); // multiplica

   _mm256_store_ps(c, vc);

   for (int i = 0; i < 8 ;i++)
   {
     c[0] += c[i];
   }
}

void show(float *c){
  int i;
  for (i = 0; i < 8; ++i) {
    printf("%f\n", c[i]);
  }
}




int main (int argc, char *argv[])
{
  float *a = (float*)_mm_malloc (sizeof(float) * 64, 32); //aloca um vetor de 32 bytes (256 bits) alinhado em endereços múltiplos de 16 bytes.
  float *b = (float*)_mm_malloc (sizeof(float) * 64, 32);
  float *c = (float*)_mm_malloc (sizeof(float) * 64, 32);
  
  int i = 0;
  
  for (i = 0; i < 4; ++i) {
    a[i] = i;
    b[i] = i;
   
  }

   produtoEscalar1(a, b, c);
  //produtoEscalar2(a, b, c);
  //produtoEscalar3(a, b, c);

  show(c);
  
  _mm_free(a);
  _mm_free(b);
  _mm_free(c);
  

  return 0;
}
