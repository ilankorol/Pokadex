#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
struct node_t{
	element data;
	struct node_t *next;
};
struct linked_List{
	Node head;
	copyFunction copyElment;
	freeFunction freeElement;
	equalFunction searchElement;
	printFunction printElement;
};

Node createnode(element elem){
	if(elem==NULL)
		return NULL;
	Node node =(Node)(malloc)(sizeof( struct node_t));
	if(node==NULL){
		printf ("No memory available.\n");
		exit(1);
	}
	node->data=elem;
	if(node->data==NULL){
		free(node);
		printf("No memory available.\n");
		exit(1);
	}
	node->next=NULL;
	return node;
}

lList createlList(copyFunction cpf,freeFunction frf,equalFunction sef,printFunction pef){
	if(cpf==NULL || frf==NULL || sef==NULL)
		return NULL;
	lList linked = (lList)malloc(sizeof(struct linked_List ));
	if(linked==NULL){
		printf ("No memory available.\n");
		exit(1);
	}
	linked->copyElment=cpf;
	if(linked->copyElment==NULL){
		free(linked);
		printf("No memory available.\n");
		exit(1);
	}
	linked->freeElement=frf;
	if(linked->copyElment==NULL){
		free(linked->copyElment);
		free(linked);
		printf("No memory available.\n");
		exit(1);
	}
	linked->searchElement=sef;
	if(linked->searchElement==NULL){
		free(linked->freeElement);
		free(linked->copyElment);
		free(linked);
		printf("No memory available.\n");
		exit(1);
	}
	linked->printElement=pef;
	linked->head=NULL;
	return linked;
}

void destroylist(lList lst){
	if (lst==NULL)
		return;
	Node next = NULL;
	while(lst->head!=NULL){
		next = lst->head->next;
		lst->freeElement(lst->head->data);
		free(lst->head);
		lst->head=NULL;
		lst->head=next;
	}
	free(lst);
	lst=NULL;
}

status appendNode(lList lst,element elem){
	if(lst==NULL || elem==NULL)
		return failure;
	Node ind =lst->head;
	//element newelm=lst->copyElment(elem);
	Node node =  createnode(elem);
	if(lst->head==NULL){
		lst->head=node;
		lst->head->next=NULL;
		return success;
	}

	while(ind->next!=NULL)
	{
		ind = ind->next;
	}
	ind->next=node;
	ind->next->data=node->data;
	node->next=NULL;
	return success;

}
status deleteNode(lList lst,element elem){
	if(lst==NULL || elem==NULL)
		return failure;
	element elem1 = searchByKeyInList(lst,elem);
	if(elem1==NULL)
		return failure;
	if(lst->head->next==NULL){
		destroylist(lst);
		return success;
	}
	Node ind = lst->head;
	while(ind->next!=NULL){
		if(ind->next->data==elem1){
			Node i = ind->next;
			ind->next = i->next;
			lst->freeElement(i->data);
			free(i);
			return success;
//			free(i->data);
//			free(i);
			return success;
		}
		ind=ind->next;

	}
	return success;

}


void displayList(lList lst){
	if(lst==NULL){
		return;
	}
	Node ind = lst->head;
	while (ind!=NULL){
		lst->printElement(ind->data);
		ind = ind->next;
	}
}

element searchByKeyInList(lList lst,element elem){
	if(lst==NULL || elem==NULL){
		return NULL;
	}
	if(lst->head->data==NULL)
		return NULL;
	Node ind = lst->head;
//	Node search = createnode(elem);
	while(ind!=NULL){
		if(lst->searchElement(ind->data,elem)==1)
			return ind->data;
	else{
		ind = ind->next;
	}
	}
	return NULL;
}
element getNodebyNumber(lList lst ,int number){
	if(lst==NULL)
		return NULL;
	Node j= lst->head;

	element i = lst->head->data;
	if(number==0)
		return i;
	int f;
	for(f=0;f<number;f++){
		j = j->next;
	}
	return j->data;
}
