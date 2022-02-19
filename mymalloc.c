#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

#define memSize 4096
static char memBlock[memSize];

//Main area of memory started out as one whole block
struct node *head = (struct node *) memBlock;

struct node *prevPtr(struct node *curr)
{
  char *retr = (char *) curr;
  retr = retr - curr->preBlockSz - sizeof(struct node);
  return (struct node *) retr;
}

struct node *nextPtr(struct node *curr)
{
  char *retr = (char *) curr;
  retr = retr + sizeof(struct node) + curr->BlockSz;
  return (struct node *) retr;
}

void *mymalloc(size_t size, char *file, int line)
{
  printf("testing");
  //Creates the inital area of memory if not already initialized
  if(head->BlockSz == 0){
    head->start_address = (void *) head + sizeof(struct node);
    head->BlockSz = memSize - sizeof(struct node);
    head->free = 1;
    head->next = NULL;
    head->prev = NULL;
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
  if((size + sizeof(struct node)) >= memSize){
   fprintf(stderr, "%s: line: %d: error: allocation size exceeds memory limit.\n", file, line);
   EXIT_FAILURE;
  }

  struct node *curr = head;
  
  //Looks for first empty chunk that fits both metadata and allocated data
  while(curr->next != NULL){
    
    //Condition checks if given chunk has sufficient size and is free
    if((curr->free == 1) && (size <= curr->BlockSz)){

      //The current memory chunk is equal to the necessary size
      if(size == curr->BlockSz){
        curr->free = 0;
        return curr->start_address;
      }

      //Size of required allocated memory plus metadata header is smaller than the size of the current memory chunk
      else if((size + sizeof(struct node)) < curr->BlockSz){
        //Divide the current chunk into two parts for memory allocation

        //Creates new node to represent right part of the divided chunk, the free section
        struct node temp;
        temp.BlockSz = curr->BlockSz - size - sizeof(struct node);
        temp.free = 1;
        temp.start_address = (void *)curr + size + sizeof(struct node);
        temp.next = curr->next;
        temp.prev = curr;

        //Changes attributes of current node to represent left part of the divided chunk, the allocated section
        curr->BlockSz = size;
        curr->free = 0;
        curr->next = &temp;
        return curr->start_address;
      }

    }

    curr = curr->next;
  }

  //Error for not enough memory in the virtual heap
  fprintf(stderr, "%s: line: %d: error: not enough memory in the heap.\n", file, line);
  return NULL;

  while((curr >= head) && ((char *) curr <= &memBlock[memSize-1])){
    
  }

}

void myfree(void *ptr, char *file, int line)
{
  //Checks if the heap was not initialized
  if(head->BlockSz == 0){
    head->BlockSz = memSize - sizeof(struct node);
    head->free = 1;
    head->next = NULL;
    head->prev = NULL;
  }
}
