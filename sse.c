#include <stdio.h>

#include <xmmintrin.h> // SSE (Required to use the __m128, and __m128d type)
#include <emmintrin.h> // SSE2 (Required to use the __m128i type)
#include <pmmintrin.h> // SSE3
#include <smmintrin.h> // SSE4.1

int main ()
{
    int i, y, x;
    int w = 8, h = 5;
    __m128 c = {10, 10, 10, 10};
    float *a __attribute__ ((aligned(16))) = (float*) malloc (sizeof(float) * (h * w));
    float *b;

    for(y = 0; y < h; ++y){
		for(x = 0; x < w; ++x){
            a[y*w+x] = x + y + 200;
			printf("%.2f\t", a[y*w+x]);
		}
		printf("\n");
	}

    b = a;
    for(y = 0; y < h; ++y){
		for(x = 0; x < w; ++x){
			__m128 img = _mm_load_ps(b);
			__m128 r = _mm_add_ps(img, c);
			_mm_store_ps(b, r);

			b += 4;
		}
    }

    printf("\ndepois da execucaoo\n");
    for(y = 0; y < h; ++y){
		for(x = 0; x < w; ++x){
			printf("%.2f ",a[y*w+x]);
		}
		printf("\n");
	}

    return 0;
}
