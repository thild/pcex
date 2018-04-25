#include <stdio.h>

#include <xmmintrin.h> // SSE (Required to use the __m128, and __m128d type)
#include <emmintrin.h> // SSE2 (Required to use the __m128i type)
#include <pmmintrin.h> // SSE3
#include <smmintrin.h> // SSE4.1

#define H 4
#define W 7

void add_nivel_cinza(float* img, float* cinza, int tam) {
	__m128 vc = _mm_load_ps(cinza);

	int i = 0;
	while(i < tam) {
		__m128 vimg = _mm_load_ps(img);
		__m128 r = _mm_add_ps(vimg, vc);
		_mm_store_ps(img, r);
		img += 4;
		i += 4;
	}
}

int main() {
	int i, j;
	float img[H][W];
	for(i = 0; i < H; i++) {
		for(j = 0; j < W; j++) {
			img[i][j] = i+j;
		}
	}

	int stride = 0;
	if(W%4 == 0)
		stride = 0;
	else if(W >= 4)
		stride = 4 - (W)%4;
	else
		stride = 4 - (W+4)%4;

	int tam = (W+stride) * H;

	float *vectorImg __attribute__ ((aligned(16))) = (float*)malloc (sizeof(float) * tam); //aloca um vetor de 16bytes (128bits) alinhado em endereços múltiplos de 16bytes.
	float *cinza __attribute__ ((aligned(16))) = (float*)malloc (sizeof(float) * 4); //Nível de cinza

	int k = 0;
	int a = 0;

	for(i = 0; i < H; i++) {
		for(j = 0; j < W; j++) {		
			*(vectorImg+a) = img[i][j];
			a++;
		}
		if(stride > 0) {
			for(k = 0; k < stride; k++) {
				*(vectorImg+a) = -255;
				a++;
			}
		}
	} 

	for(i = 0; i < 4; i++) {
		cinza[i] = 10;
	}

	printf("Antes: ");

	for(i = 0; i < tam; i++) {
		printf("%.0f ", vectorImg[i]);
	}

	printf("\n");

	a = 0;
	for(i = 0; i < H; i++) {
		for(j = 0; j < W; j++) {		
			printf("%.0f " ,*(vectorImg+a));
			a++;
		}
		if(stride > 0) {
			for(k = 0; k < stride; k++) {
				a++;
			}
		}
	}

	add_nivel_cinza(vectorImg, cinza, tam);
	free(cinza);

	printf("\n\nDepois: ");

	for(i = 0; i < tam; i++) {
		printf("%.0f ", vectorImg[i]);
	}

	printf("\n");

	a = 0;
	for(i = 0; i < H; i++) {
		for(j = 0; j < W; j++) {		
			printf("%.0f " ,*(vectorImg+a));
			a++;
		}
		if(stride > 0) {
			for(k = 0; k < stride; k++) {
				a++;
			}
		}
	}

	free(vectorImg);
	return 0;
}
