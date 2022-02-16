#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

#define memSize 4096
static char memBlock[memSize];
static int initialized = 0;

//Main area of memory started out as one whole block
node *head = (node *) memBlock;

node *prevPtr(node *curr)
{
  char *retr = (char *) curr;
  retr = retr - curr->preBlockSz - sizeof(node);
  return (node *) retr;
}

node *nextPtr(node *curr)
{
  char *retr = (char *) curr;
  retr = retr + sizeof(node) + curr->BlockSz;
  return (node *) retr;
}

void *mymalloc(size_t size, char *file, int line)
{
  //Checks if the heap attributes were not initialized
  if(initialized == 0){
    head->BlockSz = memSize - sizeof(node);
    head->free = 1;
    head->next = NULL;
    head->prev = NULL;
    initialized = 1;
  }

  //Given size is equal to zero
  if(size == 0){
    fprintf(stderr, "%s: line: %d: error: No memory was allocated.\n", file, line);
    return NULL;
  }

  //Given size was less than 0
  if(size < 0){
   fprintf(stderr, "%s: line: %d: error: cannot allocate negative memory.\n", file, line);
   EXIT_FAILURE;
  }

  //Given size exceeds the memory limit
  if((size + sizeof(node)) >= memSize){
   fprintf(stderr, "%s: line: %d: error: allocation size exceeds memory limit.\n", file, line);
   EXIT_FAILURE;
  }

  node *curr = head;
  
  while((curr >= head) && ((char *) curr <= &memBlock[memSize-1])){
    
  }
}

void myfree(void *ptr, char *file, int line)
{
  //Checks if the heap was not initialized
  if(initialized == 0){
    head->BlockSz = memSize - sizeof(node);
    head->free = 1;
    head->next = NULL;
    head->prev = NULL;
  }
}
