#ifndef MYMALLOC_H_
#define MYMALLOC_H_
#include <stdio.h>
#include <stdlib.h>
#define malloc(s) mymalloc(s, __FILE__, __LINE__);
#define free(p) myfree(p, __FILE__, __LINE__);

typedef struct{
  unsigned int BlockSz;
  unsigned int preBlockSz;
  int free;
  struct node *next;
  struct node *prev;
} node;

//For free, 1 is true, 0 is false

node *prevPtr(node *);
node *nextPtr(node *);
void *mymalloc(size_t size, char *file, int line);
void myfree(void *ptr, char *file, int line);

#endif
