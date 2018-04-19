#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#define MAX 10

void prode()
{
    int i, esc[3] = {2,2,2}, x=0;
    long buf[MAX]={0}; 
    srand(time(NULL));
    for (i=0; i<MAX; i++){
        buf[i] = rand() % 10;
        printf(" %d ", buf[i]);
    }


    for (i=0; i<MAX; i++)
    {
        x = buf[i]*esc[0];
        x += buf[i+1]*esc[1];
        x += buf[i+2]*esc[2];
        buf[i+1] = x;
        printf("\n %d", buf[i]);
    }
}

//5,8,3

int main()
{
    clock_t tic = clock();

    prode();

    clock_t toc = clock();

    printf("\n\n Essa bagaca demorou: %f fuking segundos\n", (double)(toc - tic) / CLOCKS_PER_SEC);

    return 0;
}