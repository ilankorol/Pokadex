/*
 * BattleByCatergory.c
 *
 *  Created on: Dec 10, 2021
 *      Author: ise
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "MaxHeap.h"
#include "LinkedList.h"
#include "BattleByCategory.h"
#include "Pokemon.h"
struct battle_s{
	lList llist;
	int size;
	int numcat;
	equalFunction equalElement;
	copyFunction copyElement;
	freeFunction freeElement;
	getCategoryFunction getCategory;
	getAttackFunction getAttack;
	printFunction printElement;
};








Battle createBattleByCategory(int capacity,int numberOfCategories,char* categories,equalFunction equalElement,copyFunction copyElement,freeFunction freeElement,getCategoryFunction getCategory,getAttackFunction getAttack,printFunction printElement){
	if(capacity==0|| categories==NULL ||  equalElement==NULL|| copyElement==NULL || freeElement==NULL || getCategory==NULL|| getAttack==NULL|| printElement==NULL)
		return NULL;
	Battle battle = (Battle)malloc(sizeof(struct battle_s));
	if(battle==NULL){
		printf ("No memory available.\n");
		return NULL;
	}
	battle->numcat = numberOfCategories;
	battle->size=capacity;
	battle->copyElement=copyElement;
	battle->equalElement=equalElement;
	battle->freeElement=freeElement;
	battle->getAttack=getAttack;
	battle->getCategory=getCategory;
	battle->printElement=printElement;
	battle->llist=createlList(copyElement,destroyHeap,copmfunc,printHeap);
	int j ;
	int a =300;
	char  buffer[a];
	strcpy(buffer,categories);
	char* tempo;
	tempo=strtok(buffer,",");
	for(j=0;j<battle->numcat;j++){
	//create  heap
		if(j==battle->numcat-2){
		maxheap into=createheap(capacity,tempo,printElement,freeElement,copyElement,equalElement);
		appendNode(battle->llist,into);
		tempo = strtok(NULL,"\r\n");
		}
		else{
		maxheap into=createheap(capacity,tempo,printElement,freeElement,copyElement,equalElement);
		appendNode(battle->llist,into);
		tempo = strtok(NULL,",");
		}
	}
	return battle;

}
status destroyBattleByCategory(Battle b){
	if(b==NULL)
		return failure;
	destroylist(b->llist);
	free(b);
	return success;
}
status insertObject(Battle b, element elem){
	if(b==NULL|| elem==NULL){

		return failure;
	}
	char* namecatstr = b->getCategory(elem);
	maxheap namecat=(maxheap)searchByKeyInList(b->llist,namecatstr);
	if(namecat==NULL)
		return failure;
	return insertToHeap(namecat,elem);
}
void displayObjectsByCategories(Battle b){
	if(b==NULL){
		return ;
	}
	displayList(b->llist);

}
element removeMaxByCategory(Battle b,char* category){
	if(b==NULL || category==NULL){
		return NULL;
	}
	element search = (element)category;
	element namecat=searchByKeyInList(b->llist,search);
	if(namecat==NULL)
		return NULL;
	maxheap mxp=(maxheap)namecat;
	return PopMaxHeap(mxp);
}
int getNumberOfObjectsInCategory(Battle b,char* category){
	if(b==NULL || category==NULL){
		return failure;
	}
	maxheap namecat=(maxheap)searchByKeyInList(b->llist,category);
	return getHeapCurrentSize(namecat);
}




element fight(Battle b,element elem){
	if(b==NULL || elem==NULL)
		return NULL;
	int i=0;
	int j=0;
	int str;
	char* namecatstr = b->getCategory(elem);
	maxheap heap = (maxheap)searchByKeyInList(b->llist,namecatstr);
	element strongest = TopMaxHeap(heap);
	int strong=-100;
	int tempor;
	int check;
	int mine;
	if(strongest!=NULL){
	strong = b->getAttack(elem,strongest,&i,&j);
	}
	str=j;
	mine=i;
	for(check=0;check<b->numcat;check++){
		element checking = getNodebyNumber(b->llist,check);
		char* namecatstr1 = getHeapId(checking);
		maxheap heap = (maxheap)searchByKeyInList(b->llist,namecatstr1);
		if(getHeapCurrentSize(heap)!=0){
		element temp = TopMaxHeap(heap);
		tempor = b->getAttack(elem,temp,&i,&j);
		if(strongest==NULL){
			strong = tempor;
			strongest = temp;
			str=j;
			mine=i;
		}
		if(tempor<strong ){
			strong = tempor;
			strongest = temp;
			str=j;
			mine=i;
		}
		}
	}
	if(strongest==NULL){
		printf("There are no Pokemons to fight against you.\n");
		return elem;
	}
	printf("You choose to fight with:\n");
	b->printElement(elem);
	printf("The final battle between:\n");
	b->printElement(elem);
	printf("In this battle his attack is :%d\n\n",mine);
	printf("against ");
	b->printElement(strongest);
	printf("In this battle his attack is :%d\n\n",str);
	if(str>mine){
		printf("THE WINNER IS:\n");
		b->printElement(strongest);
	}
	else if((str<mine)){
		printf("THE WINNER IS:\n");
		b->printElement(elem);
	}
	else{
		printf("IT IS A DRAW.\n");
	}
	return strongest;
}









