#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include "mymalloc.h"

/*Malloc and immediately free 1-byte chunk, 120 times*/
double grindOne(){
    int i;
    struct timeval tval1, tval2;
    void *arr[20000];
    gettimeofday(&tval1, NULL);
    for(i = 0; i < 2; i++){
        printList();
        arr[i] = (void *) malloc(1);
        free(arr[i]);
    }
    gettimeofday(&tval2, NULL);
  
    double totalTime = (double)(tval2.tv_sec - tval1.tv_sec) + (double)(tval2.tv_usec - tval1.tv_usec)/1000000;
    return totalTime;
}

/*Malloc 120 1-byte chunks, storing pointers in array, then use free to deallocate the chunks*/
double grindTwo(){
    int i;
    struct timeval tval1, tval2;
    int *arr[20000];
  
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

double grindFour(){
    struct timeval tval1, tval2;
    int *arr[1000];
    int count = 0;
    int size = 0;
    int random = 0;
  
    gettimeofday(&tval1, NULL);
    while(count < 120){
        arr[size] = malloc(1);
        random = rand() % 2;
        if(random == 1){
            free(arr[size]);
            arr[size] = NULL;
        }
        else{
            size++;
        }
        count++;
    }
    for(int i = 0; i<size; i++){
        free(arr[i]);
        arr[i] = NULL;
    }
    gettimeofday(&tval2, NULL);
  
    double totalTime = (double)(tval2.tv_sec - tval1.tv_sec) + (double)(tval2.tv_usec - tval1.tv_usec)/1000000;
    return totalTime;
}

double grindFive(){
    int i, j;
    struct timeval tval1, tval2;
    int **arr[100][100];
  
    gettimeofday(&tval1, NULL);
    for(i = 0; i < 10; i++){
        for(j = 0; j < 12; j++){
            arr[i][j] = malloc(1);
        }  
    }
    for(i = 0; i < 10; i++){
        for(j = 0; j < 12; j++){
            free(arr[i][j]);
            arr[i][j] = NULL;
        }
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
    double fourth = 0;
    double fifth = 0;
  
    for(i = 0; i < 50; i++){
        first += grindOne();
        printf("-------------------------\n");
    }
    for(i = 0; i < 50; i++){
        //second += grindTwo();
    }
    for(i = 0; i < 50; i++){
        //third += grindThree();
    }
    for(i = 0; i < 50; i++){
        //fourth += grindFour();
    }
    for(i = 0; i < 50; i++){
        //fifth += grindFive();
    }

    printf("Total of Immediate: %f seconds\n", first);
    printf("Total of Delayed: %f seconds\n", second);
    printf("Total of Random: %f seconds\n", third);
    printf("Seconds:\n");
    printf("\tTotal of Immediate: %f seconds\n", first);
    printf("\tAverage of Immediate: %f seconds\n", first/50);
    printf("\n");
    printf("\tTotal of Delayed: %f seconds\n", second);
    printf("\tAverage of Delayed: %f seconds\n", second/50);
    printf("\n");
    printf("\tTotal of Random: %f seconds\n", third);
    printf("\tAverage of Random: %f seconds\n", third/50);
    printf("\n");
    printf("\tTotal of Combination: %f seconds\n", fourth);
    printf("\tAverage of Combination: %f seconds\n", fourth/50);
    printf("\n");
    printf("\tTotal of Double Array: %f seconds\n", fifth);
    printf("\tAverage of Double Array: %f seconds\n", fifth/50);
    printf("\n");
    printf("Milliseconds:\n");
    printf("\tTotal of Immediate: %f milliseconds\n", first*1000000);
    printf("\tAverage of Immediate: %f milliseconds\n", first*20000);
    printf("\n");
    printf("\tTotal of Delayed: %f milliseconds\n", second*1000000);
    printf("\tAverage of Delayed: %f milliseconds\n", second*20000);
    printf("\n");
    printf("\tTotal of Random: %f milliseconds\n", third*1000000);
    printf("\tAverage of Random: %f milliseconds\n", third*20000);
    printf("\n");
    printf("\tTotal of Combination: %f milliseconds\n", fourth*1000000);
    printf("\tAverage of Combination: %f milliseconds\n", fourth*20000);
    printf("\n");
    printf("\tTotal of Double Array: %f milliseconds\n", fifth*1000000);
    printf("\tAverage of Double Array: %f milliseconds\n", fifth*20000);
    printf("\n");
    return 0;
}
