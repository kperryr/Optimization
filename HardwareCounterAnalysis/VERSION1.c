/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>

void flush(int * g, int size){
    int i;for(i = 0; i<size; i++){
        g[i]++;
    }
}

int main(){
    int * a;int * garbage;
    const int arraysize = 9*(1 << 20);
    int i, j, ii, stride;
    int iter, numOfIter;
    struct timeval start, end;
    int r;
    
    printf("array size = %d\n", arraysize);
    srand(time(NULL));
    
    garbage = (int *) malloc(sizeof(int) * arraysize);
    for (i = 0; i < arraysize; i++) {
 
        garbage[i] = rand();
    }
    a = (int *) malloc(sizeof(int) * arraysize);
    for (i = 0; i < arraysize; i++) {
        a[i] = rand();
    }
    numOfIter = 10;
    
    /* ver. 1: sequential access */
    flush(garbage, arraysize);
    gettimeofday(&start, NULL);
    for(j = 0; j < 4; j++){  //Change
        for(iter = 0; iter < numOfIter; iter++){        
            for (i = 1; i < (1 << 20); i++) {
            //for(j = 0; j < 4; j++){
                a[8*i+j] = a[8*(i-1)+j] * 2;
            }
        }
    }
    
    gettimeofday(&end, NULL);
    printf("v1: %lf us\n", (((end.tv_sec * 1000000 + end.tv_usec)- (start.tv_sec * 1000000 + start.tv_usec)))*1.0/numOfIter);
    
    /* end */
    /* ver. 2: sequential access */
    stride = 4;
    flush(garbage, arraysize);
    gettimeofday(&start, NULL);
    for (ii =1; ii <= stride ; ii++){
        for(iter = 0; iter < numOfIter; iter++){
            for (i = ii; i < (1 << 20); i+=stride) {
                for(j = 3; j >= 0; j--){
                    a[8*i+j] = a[8*(i-1)+j] * 2;
                }
            }
        }
    }
    
    gettimeofday(&end, NULL);
    printf("v2: %lf us\n", (((end.tv_sec * 1000000 + end.tv_usec)- (start.tv_sec * 1000000 + start.tv_usec)))*1.0/numOfIter);
    /* end */
    r = rand() % arraysize;
    printf("a[%d] = %d\n", r, a[r]);
    free(a);
    free(garbage);
    return 0;
} 
