#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

static char memBlock[4096];
#define memSize 4096

node *head = (node *) &memBlock[0];

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
  if(size == 0){
    fprintf(stderr, "%s: line: %d: error: No memory was allocated.\n", file, line);
    return NULL;
  }

  if(size < 0){
   fprintf(stderr, "%s: line: %d: error: cannot allocate negative memory.\n", file, line);
   EXIT_FAILURE;
  }

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

}
