#ifndef MAXHEAP_H_
#define MAXHEAP_H_
#include <string.h>
#include "Defs.h"

typedef struct maxheap_t *maxheap;

maxheap createheap(int size_max,char* name,printFunction plm,freeFunction frelm, copyFunction cpyelm,equalFunction cmpf);
void destroyHeap(maxheap mxp);
maxheap copyHeap(maxheap mxp);
status insertToHeap(maxheap mxp, element elm);
int copmfunc(maxheap e1,char* e2);
status printHeap(maxheap mxp);
element PopMaxHeap(maxheap mxp);
element TopMaxHeap(maxheap mxp);
char* getHeapId(maxheap mxp);
int getHeapCurrentSize(maxheap mxp);
void heapifyinsert(maxheap mxp,int index);
void heapifyPop(maxheap mxp,int index);
#endif /* MAXHEAP_H_ */
