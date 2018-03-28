#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <immintrin.h> // AVX MUITO LOCO - novo Hero da Marvel
#define MAX 50000

void produtoEscalar(int imgIn[], int mult[], int result[], int n)
{
   	int  i, j;
    for (i = 0; i < n; i++){
    	for(j=0;j<3;j++){
   	    	result[i] += imgIn[i]*mult[j];
   		}
    }
}


int main()
{
	int i = 0;
	srand(time(NULL));
	int imgIn[MAX]; 
  	int result[MAX];
  	int mult[3] = {1,2,3};

  	for(i=0;i<MAX;i++){
		result[i] = 0;	
	}

	for(i=0;i<MAX;i++){
		imgIn[i] = rand() % 10;	
	}


	clock_t tic = clock();

	for(i=0;i<50;i++){

		produtoEscalar(imgIn, mult, result, MAX);   

	}

    clock_t toc = clock();

    printf("Elapsed: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);

    return 0;
}