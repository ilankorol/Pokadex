#ifndef MAXHEAP_C_
#define MAXHEAP_C_
#include "MaxHeap.h"

struct maxheap_t
{
	element* elm;
	printFunction printfuc;
	freeFunction freefunc;
	copyFunction copyfunc;
	equalFunction compFunc;
	int next_ind;
	int max_size;
	char* heapID;
};
maxheap createheap(int size_max,char* name,printFunction plm,freeFunction frelm, copyFunction cpyelm,equalFunction cmpf){
	if(size_max==0 || name==NULL || plm==NULL || frelm==NULL || cpyelm==NULL)
		return NULL;
	maxheap mxp = (maxheap)malloc(sizeof(struct maxheap_t));
	if(mxp==NULL){
		printf("No memory available.\n");
		exit(1);
	}
	mxp->max_size = size_max;
	mxp->heapID = (char*)malloc(sizeof(name)+1);
	strcpy(mxp->heapID,name);
	if(mxp->heapID==NULL){
		printf ("No memory available.\n");
		free(mxp);
	}
	mxp->copyfunc=cpyelm;
	mxp->freefunc=frelm;
	mxp->printfuc=plm;
	mxp->compFunc=cmpf;
	}
	mxp->elm=(element*)malloc(sizeof(element)*size_max);
	mxp->next_ind=0;
	return mxp;
}

void destroyHeap(maxheap mxp){
	if(mxp==NULL)
		return;
	int i;
	for(i=mxp->next_ind-1;i>=0;i--){
		(mxp->freefunc(mxp->elm[i]));
		mxp->elm[i]=NULL;
	}
	free(mxp->heapID);
	free(mxp->elm);
	free(mxp);
}

maxheap copyHeap(maxheap mxp){
	if(mxp==NULL)
		return NULL;
	maxheap tempheap = (maxheap)malloc(sizeof(struct maxheap_t));
	if(tempheap==NULL){
		printf ("No memory available.\n");
	}
	tempheap->max_size=mxp->max_size;
	tempheap->compFunc=mxp->compFunc;
	tempheap->copyfunc=mxp->copyfunc;
	tempheap->freefunc=mxp->freefunc;
	tempheap->printfuc=mxp->printfuc;
	tempheap->heapID = (char*)malloc(strlen(mxp->heapID)+1);
	if(tempheap->heapID==NULL){
		printf ("No memory available.\n");
		free(tempheap);
		return NULL;
	}
	tempheap->elm = (element*)malloc(sizeof(element)*mxp->max_size);
	return tempheap;
}





status insertToHeap(maxheap mxp, element elm){
	if(mxp==NULL|| elm==NULL)
		return failure;
	if(mxp->next_ind==mxp->max_size){
		return failure;
	}
	mxp->elm[mxp->next_ind] = elm;
	heapifyinsert(mxp,mxp->next_ind);
	mxp->next_ind++;
	return success;
}

status printHeap(maxheap mxp){
	if(mxp==NULL){
		return failure;
	}
	if(mxp->next_ind==0){
		printf("%s:\n",mxp->heapID);
		printf("No elements.\n\n");
		return failure;
	}
	maxheap tempheap =createheap(mxp->max_size,mxp->heapID,mxp->printfuc,mxp->freefunc,mxp->copyfunc,mxp->compFunc);
	if(tempheap==NULL){
		printf ("No memory available.\n");
	}
	element temp;
	int i;
	int j;
	int cur_size = mxp->next_ind;
	printf("%s:\n",mxp->heapID);
	for(i=0;i<cur_size;i++){
		temp=PopMaxHeap(mxp);
		printf("%d. ",i+1);
		mxp->printfuc(temp);
		insertToHeap(tempheap,temp);
	}
	for(j=0;j<cur_size;j++){
		temp = PopMaxHeap(tempheap);
		insertToHeap(mxp,temp);
	}
	destroyHeap(tempheap);
	return success;
}

element PopMaxHeap(maxheap mxp){
	if(mxp==NULL || mxp->next_ind==0)
		return NULL;
	element max=mxp->elm[0];
	mxp->elm[0]=mxp->elm[mxp->next_ind-1];
	mxp->elm[mxp->next_ind-1]=NULL;
	mxp->next_ind--;
	mxp->freefunc(mxp->elm[mxp->next_ind]);
	heapifyPop(mxp,mxp->next_ind);
	return max;
}



element TopMaxHeap(maxheap mxp){
	if(mxp==NULL || mxp->next_ind==0)
		return NULL;
	if(mxp->elm==NULL)
		return NULL;
	return mxp->elm[0];
}

char* getHeapId(maxheap mxp){
	if(mxp==NULL)
		return NULL;
	return mxp->heapID;
}

int getHeapCurrentSize(maxheap mxp){
	if(mxp==NULL)
		return 0;
	return mxp->next_ind;
}

void heapifyinsert(maxheap mxp,int index){
	if(mxp==NULL || index<0)
		return;
	if(index==0){
		return;
	}
	int i;
	int parent=(index/2)-1;
	if(index==1)
		parent=0;
	for(i=parent;i>=0;i=(i/2)-1)
	if(mxp->compFunc(mxp->elm[i],mxp->elm[index])==1)
		return;
	else{
		element hold = mxp->elm[i];
		mxp->elm[i]=mxp->elm[index];
		mxp->elm[index]= hold;
	}
}

void heapifyPop(maxheap mxp,int index){
	if(mxp==NULL || index==0)
		return;
	int k =0;
	int l =2*k+1;
	while(l<mxp->next_ind){
		int max = l;
		int r = l+1;
		if(r<mxp->next_ind){
			if(mxp->compFunc(mxp->elm[max],mxp->elm[r])==-1||mxp->compFunc(mxp->elm[max],mxp->elm[r])==0){
				max++;
			}
		}
		if(mxp->compFunc(mxp->elm[max],mxp->elm[k])==1){
			//switch
			element temp = mxp->elm[k];
			mxp->elm[k]=mxp->elm[max];
			mxp->elm[max]=temp;
			k=max;
			l = 2*k+1;
		}
		else{
			break;
		}
	}
}

int copmfunc(maxheap e1,char* e2){
	if(strcmp(e1->heapID,e2)==0)
		return 1;
	else
		return 0;
}













#endif /* MAXHEAP_C_ */
