#ifndef MYMALLOC_H_
#define MYMALLOC_H_
#include <stdio.h>
#include <stdlib.h>
#define malloc(s) mymalloc(s, __FILE__, __LINE__);
#define free(p) myfree(p, __FILE__, __LINE__);

struct node{
  void *start_address;
  unsigned int BlockSz;
  int free;
  struct node *next;
  struct node *prev;
};
//For free, 1 is true, 0 is false

struct node *prevPtr(struct node *);
struct node *nextPtr(struct node *);
void *mymalloc(size_t size, char *file, int line);
void myfree(void *ptr, char *file, int line);

#endif
