#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_
#include <string.h>
#include "Defs.h"
typedef struct node_t *Node;
typedef struct linked_List *lList;
typedef void* element;



Node createnode(element);
lList createlList(copyFunction,freeFunction,equalFunction,printFunction);
element getNodebyNumber(lList l ,int number);
void destroylist(lList);
status appendNode(lList,element);
status deleteNode(lList,element);
void displayList(lList);
element searchByKeyInList(lList,element);
#endif /* LINKEDLIST_H_ */
