#include <stdio.h>
#include <stdlib.h>
#include "malloc.h"

int main(int argc, char* argv[]){
    void *test = malloc(5000);
    printf("Address: %p\n", test);
    return 0;
}