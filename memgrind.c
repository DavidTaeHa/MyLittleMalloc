#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include "mymalloc.h"

/*Malloc and immediately free 1-byte chunk, 120 times*/
double grindOne(){
    int i;
    struct timeval tval1, tval2;
    int *arr[200];
  
    gettimeofday(&tval1, NULL);
    for(i = 0; i < 120; i++){
        arr[i] = (int *) malloc(1);
        free(arr[i]);
        arr[i] = NULL;
    }
    gettimeofday(&tval2, NULL);
  
    double totalTime = (double)(tval2.tv_sec - tval1.tv_sec) + (double)(tval2.tv_usec - tval1.tv_usec)/1000000;
    return totalTime;
}

/*Malloc 120 1-byte chunks, storing pointers in array, then use free to deallocate the chunks*/
double grindTwo(){
    int i;
    struct timeval tval1, tval2;
    int *arr[200];
  
    gettimeofday(&tval1, NULL);
    for(i = 0; i < 120; i++){
        arr[i] = (int *) malloc(1);
    }
    for(i = 0; i < 120; i++){
        free(arr[i]);
        arr[i] = NULL;
    }
    gettimeofday(&tval2, NULL);
  
    double totalTime = (double)(tval2.tv_sec - tval1.tv_sec) + (double)(tval2.tv_usec - tval1.tv_usec)/1000000;
    return totalTime;
}

/*Randomly choose to malloc or free a 1-byte chunk. Perform until malloc is used 120 times, then free all remaining chunks*/
double grindThree(){
    struct timeval tval1, tval2;
    int *arr[1000];
    int count = 0;
    int size = 0;
    int fcount = 0;
    int random = 0;
  
    gettimeofday(&tval1, NULL);
    while(count < 120){
        random = rand() % 2;
        if(random == 0 && count < 120){
            arr[size] = (int *) malloc(1);
            count++;
            size++;
        }
        else{
            if(arr[fcount] == NULL){
                arr[size] = (int *) malloc(1);
                size++;
                count++;
            }
            else{
                free(arr[fcount]);
                arr[fcount] = NULL;
                fcount++;
            }
        }
    }
    for(size = fcount; size < 120; size++){
        free(arr[size]);
	    arr[size] = NULL;
    }
    gettimeofday(&tval2, NULL);
  
    double totalTime = (double)(tval2.tv_sec - tval1.tv_sec) + (double)(tval2.tv_usec - tval1.tv_usec)/1000000;
    return totalTime;
}



int main(){
    int i;
    double first = 0;
    double second = 0;
    double third = 0;
    //double fourth = 0;
    //double fifth = 0;
  
    for(i = 0; i < 50; i++){
        first += grindOne();
    }
    for(i = 0; i < 50; i++){
        second += grindTwo();
    }
    for(i = 0; i < 50; i++){
        third += grindThree();
    }
    printf("Total of Immediate: %f seconds\n", first);
    printf("Total of Delayed: %f seconds\n", second);
    printf("Total of Random: %f seconds\n", third);
    printf("\n");
    printf("Average of Immediate: %f seconds\n", first/50);
    printf("Average of Delayed: %f seconds\n", second/50);
    printf("Average of Random: %f seconds\n", third/50);

    return 0;
}