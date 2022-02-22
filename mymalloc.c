#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

#define memSize 4096
static char memBlock[memSize];

//Main area of memory started out as one whole block
struct node *head = (struct node *) memBlock;

void *mymalloc(size_t size, char *file, int line)
{

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
   return NULL;
  }

  struct node *curr = head;
  int count = 1;

  void *address = NULL;

  //printf("!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
  //Looks for first empty chunk that fits both metadata and allocated data
  while(curr != NULL){
    //printf("-----------------------------\n");
    //printf("Iteration %d:\n", count);
    //printf("Chunk Size: %d\n",curr->BlockSz);

    //Condition checks if given chunk has sufficient size and is free
    if((curr->free == 1) && (size <= curr->BlockSz)){

      //The current memory chunk is equal to the necessary size, no need to divide into two parts
      if(size == curr->BlockSz){
        curr->free = 0;
        address = curr->start_address;
        return address;
      }

      //Size of required allocated memory plus metadata header is smaller than the size of the current memory chunk
      else if((size + sizeof(struct node)) < curr->BlockSz){
        //Divide the current chunk into two parts for memory allocation
        //printf("Diving chunk into two parts:\n");
        //printf("Whole Chunk: %d\n",curr->BlockSz);

        //Creates new node to represent right part of the divided chunk, the free section
        struct node *temp = (void *)curr + size + sizeof(struct node);
        temp->start_address = (void *)curr + size + sizeof(struct node);
        temp->BlockSz = curr->BlockSz - size;
        temp->free = 1;
        temp->next = curr->next;
        temp->prev = curr;

        //Changes attributes of current node to represent left part of the divided chunk, the allocated section
        curr->BlockSz = size;
        curr->free = 0;
        curr->next = temp;
        
        //printf("Left Side: %d\n",curr->BlockSz);
        //printf("Right Side: %d\n",temp->BlockSz);
        //printf("Head: %d\n",head->BlockSz);
        address = curr->start_address;
        return address;
      }

    }

    curr = curr->next;
    count++;
  }

  //Error for not enough memory in the virtual heap
  fprintf(stderr, "%s: line: %d: error: not enough memory in the heap.\n", file, line);
  return NULL;

}

void myfree(void *ptr, char *file, int line)
{
  //Checks if the heap was not initialized
  if(head->BlockSz == 0){
    printf("Heap has not been initialized");
    return;
  }

  struct node *curr = head;

  while(curr != NULL){

    //See if the address of given and current node matches
    if(ptr == curr->start_address){

      //The target node is already freed
      if(curr->free == 1){
        fprintf(stderr, "%s: line: %d: error: allocated memory is already freed.\n", file, line);
        return;
      }
      else if(curr->free == 0){
        curr->free = 1;
      }

      //Handle coalescence of adjacent free blocks, check both left and right block
      if(curr->prev != NULL && curr->prev->free == 1){
        curr->prev->BlockSz = curr->prev->BlockSz + curr->BlockSz;
        if(curr->next != NULL){
        curr->next->prev = curr->prev;
        }
        curr->prev->next = curr->next;
        curr = curr->prev;
      }
      //FIXME: may need to fix this part, further testing required
      if(curr->next != NULL && curr->next->free == 1){
        curr->BlockSz = curr->BlockSz + curr->next->BlockSz; 
        if(curr->next->next != NULL){
          curr->next->next->prev = curr;
        }
        curr->next = curr->next->next;
      }
      return;
    }

    curr = curr->next;

  }

  //Never found the address of given pointer, the allocated memory does not exist
  fprintf(stderr, "%s: line: %d: error: attempting to free allocated memory that does not exist.\n", file, line);

}

void printList(){
  struct node *curr = head;
  int count = 1;
  while(curr != NULL){
    printf("Chunk %d: %d Free: %d\n", count, curr->BlockSz, curr->free);
    curr = curr->next;
    count++;
  }
}

/*
int main(int argc, char* argv[]){
    void *test = malloc(100);
    void *test2 = malloc(200);
    void *test3 = malloc(300);
    void *test4 = malloc(400);
    printf("Address: %p\n", test);
    printf("Address: %p\n", test2);
    //printf("Address: %p\n", test3);
    //printf("Address: %p\n", test4);
    printList();
    free(test);
    free(test3);
    free(test2);
    //free(test4);
    printf("--------------------\n");
    printList();
    return 0;
}
*/