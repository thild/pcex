// gcc produtoEscalar.c -o escalar

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
    int i, esc[3] = {2, 2, 2}, x=0;
    long vetA[size]={0}, vetB[size]; 
    srand(time(NULL));
    for (i=0; i<size; i++){
        vetA[i] = rand() % 10;
        // printf("\n %d fak \n", vetA[i]); 
    }

    // printf("\n\n %d \n\n", x);

    for (i=0; i<size-2; i++)
    {
        x=0;
        x = vetA[i]*esc[0];
        x += vetA[i+1]*esc[1];
        x += vetA[i+2]*esc[2];
        vetB[i+1] = x;
        // printf("\n %d", vetB[i]);
    }
}
