/*
 ============================================================================
 Name        : Pokemon.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "Pokemon.h"
pPokemon createPokemon(char* name, pType type, char* species, bio_Pokemon biolo ){
	pPokemon pokemon=(pPokemon)malloc(sizeof(Pokemon));
	if(pokemon == NULL){
		exit(1);
	}
	pokemon->name=(char*)malloc(strlen(name)+1);
	if(pokemon->name == NULL){
		printf ("No memory available.\n");
		free(pokemon);
	}
	pokemon->species=(char*)malloc(strlen(species)+1);
	if(pokemon->species == NULL){
		printf ("No memory available.\n");
		free(pokemon->name);
		free(pokemon);
	}
	strcpy(pokemon->name,name);
	strcpy(pokemon->species,species);
	pokemon->biolo=biolo;
	pokemon->type=type;
	return pokemon;
}


bio_Pokemon create_Bio(float height, float weight, int attack){
	bio_Pokemon bio;
	bio.attack=attack;
	bio.height=height;
	bio.weight=weight;
	return bio;
}
bool effective_against_me(pType pokemon_A, pType pokemon_B){
	if(pokemon_A->num_me==0){
		pokemon_A->effective_against_me=(pType*)malloc(sizeof(pType));
		pokemon_A->effective_against_me[0]=pokemon_B;
		pokemon_A->num_me++;
		return true;
	}
	pokemon_A->num_me++;
	pokemon_A->effective_against_me=(pType*)realloc(pokemon_A->effective_against_me,(pokemon_A->num_me)*sizeof(pType));
	int temp= pokemon_A->num_me-1;
	pokemon_A->effective_against_me[temp]=pokemon_B;
	return true;

}


bool effective_against_others(pType pokemon_A, pType pokemon_B){
	if(pokemon_A->num_other==0){
		pokemon_A->effective_against_others=(pType*)malloc(sizeof(pType));
		pokemon_A->effective_against_others[0]=pokemon_B;
		pokemon_A->num_other++;
		return true;
	}
	int size= sizeof(pokemon_A->effective_against_others)+sizeof(pType);
	pokemon_A->num_other++;
	pokemon_A->effective_against_others=(pType*)realloc(pokemon_A->effective_against_others,(pokemon_A->num_other)*(size));
	int temp= pokemon_A->num_other-1;
	pokemon_A->effective_against_others[temp]=pokemon_B;
	return true;

}
status erase_Effective_Against_Me_Pokemon(pType pokemon_A, char* pokemon_B){
	int i;
	int found;
	for(i=0; i<pokemon_A->num_me;i++){
		if(strcmp(pokemon_A->effective_against_me[i]->name,pokemon_B)==0){
			pokemon_A->effective_against_me[i]=NULL;
			if(i<pokemon_A->num_me-1)
			for(found=i;found<pokemon_A->num_me-1;found++){
				pokemon_A->effective_against_me[found]=pokemon_A->effective_against_me[found+1];
			}
			pokemon_A->num_me=pokemon_A->num_me-1;
			break;

		}
		if(i==pokemon_A->num_me-1){
			return failure;
		}
	}
	pokemon_A->effective_against_me=(pType*)realloc(pokemon_A->effective_against_me,(pokemon_A->num_me)*sizeof(pType));
	return success;
}


status erase_Effective_Against_Other_Pokemon(pType pokemon_A, char* pokemon_B){
	int i;
	int found;
	for(i=0; i<pokemon_A->num_other;i++){
		if(strcmp(pokemon_A->effective_against_others[i]->name,pokemon_B)==0){
			pokemon_A->effective_against_others[i]=NULL;
			if(i<pokemon_A->num_other-1){
			for(found=i;found<pokemon_A->num_other-1;found++){
				pokemon_A->effective_against_others[found]=pokemon_A->effective_against_others[found+1];
			}
			}
			pokemon_A->num_other=pokemon_A->num_other-1;
			break;

		}
		if(i==pokemon_A->num_other-1){
			return failure;
		}
	}
	pokemon_A->effective_against_others=(pType*)realloc(pokemon_A->effective_against_others,(pokemon_A->num_other)*sizeof(pType));
	return success;
}


status print_Pokemon(pPokemon pokemon){
	if(pokemon==NULL)
		return failure;
	else{
	printf("%s :\n",pokemon->name);
	printf("%s, %s Type.\n",pokemon->species,pokemon->type->name);
	printf("Height: %.2f m    Weight: %.2f kg    Attack: %d\n\n", pokemon->biolo.height,pokemon->biolo.weight,pokemon->biolo.attack);
	return success;
	}
}

pType creatType(char* type_Name){
	pType type = (pType)malloc(sizeof(Type));
	if(type == NULL){
		exit(1);
	}
	type->name=(char*)malloc(strlen(type_Name)+1);
	if(type->name == NULL){
		exit(1);
	}
	strcpy(type->name,type_Name);
	type->pokemon_Num=0;
	type->effective_against_me=NULL;
	type->effective_against_others=NULL;
	type->num_me=0;
	type->num_other=0;
	return type;
}
status print_Type(pType type){
	if(type==NULL)
		return failure;
	printf("Type %s -- %d pokemons",type->name,type->pokemon_Num);
	int i;
	if(type->num_me!=0){
		printf("\n\t");
		printf("These types are super-effective against %s:",type->name);
		for(i=0;i<type->num_me;i++){
			printf("%s",type->effective_against_me[i]->name);
			if(i!=type->num_me-1)
				printf(" ,");
		}
	}
	int i2;
	if(type->num_other!=0){
		printf("\n\t%s",type->name);
			printf(" moves are super-effective against:");
		for(i2=0;i2<type->num_other;i2++){
			printf("%s",type->effective_against_others[i2]->name);
			if(i2!=type->num_other-1)
			printf(" ,");
	}
	}
	printf("\n\n");
	return success;

}

char* getCategory(element elm){
	if(elm==NULL)
		return NULL;
	pPokemon pok = (pPokemon)elm;
	return pok->type->name;
}
int getpokemonAttack(element firstElem ,element secondElem ,int* attackFirst,int* attackSecond){
	pPokemon pok1 = (pPokemon)firstElem;
	pPokemon pok2 = (pPokemon)secondElem;
	if(pok2==NULL)
		return NULL;
	int pok1attack =pok1->biolo.attack;
	int pok2attack= pok2->biolo.attack;
	int j;
	for(j=0;j<pok1->type->num_me;j++){
		if(strcmp(pok2->type->name,pok1->type->effective_against_me[j]->name)==0){
			pok1attack-=10;
		}
	}
	for(j=0;j<pok2->type->num_me;j++){
		if(strcmp(pok1->type->name,pok2->type->effective_against_me[j]->name)==0){
			pok2attack-=10;
		}
	}
	int i= pok1attack - pok2attack;
	memcpy(attackFirst,&pok1attack,sizeof(int));
	memcpy(attackSecond,&pok2attack,sizeof(int));
	return i;
}
status freeFunction_type(element elm){
	if(elm==NULL)
		return failure;
	int i;
	int y;
	pType type = (pType)elm;
//	for(i=0;i<type->num_me;i++){
//		free(type->effective_against_me[i]->name);
//		type->effective_against_me[i]->name=NULL;
//		free(type->effective_against_me[i]);
//	}
//	for(y=0;y<type->num_other;y++){
//		free(type->effective_against_others[y]->name);
//		type->effective_against_others[y]->name=NULL;
//		free(type->effective_against_others[y]);
//	}
	free(type->name);
	free(type->effective_against_me);
	free(type->effective_against_others);
	free(type);
	return success;
}
status freeFunction_pokemon(element elm){
	if(elm==NULL)
		return failure;
	free(((pPokemon)elm)->name);
	((pPokemon)elm)->name=NULL;
	free(((pPokemon)elm)->species);
	((pPokemon)elm)->species=NULL;
	((pPokemon)elm)->type=NULL;
	free(((pPokemon)elm));
	return success;
}
status printPokemon(element elm){
	if(elm==NULL)
		return failure;
	pPokemon pok  =(pPokemon)elm;
	printf("%s :\n",pok->name);
	printf("%s, %s Type.\n",pok->species,pok->type->name);
	printf("Height: %.2f m    Weight: %.2f kg    Attack: %d\n\n", pok->biolo.height,pok->biolo.weight,pok->biolo.attack);
	return success;
}
status printType(element elm){
	if(elm==NULL)
		return failure;
	pType type = (pType)elm;
	printf("Type %s -- %d pokemons",type->name,type->pokemon_Num);
	int i;
	if(type->num_me!=0){
		printf("\n\t");
		printf("These types are super-effective against %s:",type->name);
		for(i=0;i<type->num_me;i++){
			printf("%s",type->effective_against_me[i]->name);
			if(i!=type->num_me-1)
				printf(" ,");
		}
	}
	int i2;
	if(type->num_other!=0){
		printf("\n\t%s",type->name);
			printf(" moves are super-effective against:");
		for(i2=0;i2<type->num_other;i2++){
			printf("%s",type->effective_against_others[i2]->name);
			if(i2!=type->num_other-1)
			printf(" ,");
	}
	}
	printf("\n\n");
	return success;

}

int equalPok(element firstElem ,element secondElem ){
	if(firstElem==NULL || secondElem==NULL)
		return 2;
	pPokemon pok1 = (pPokemon)firstElem;
	pPokemon pok2 = (pPokemon)secondElem;
	if(pok1->biolo.attack>pok2->biolo.attack)
		return 1;
	else if(pok1->biolo.attack < pok2->biolo.attack)
		return -1;
	else
		return 0;
}

element copyPok(element pok){

	if(pok==NULL)
		return NULL;
	pPokemon newpok = createPokemon(((pPokemon)pok)->name,((pPokemon)pok)->type,((pPokemon)pok)->species,((pPokemon)pok)->biolo);

//	if(newpok==NULL){
//		printf("No memory available.\n");
//		return NULL;
//	}
//	newpok->biolo =create_Bio(((pPokemon)pok)->biolo.height,((pPokemon)pok)->biolo.weight,((pPokemon)pok)->biolo.attack);
//	newpok->name = (char*)malloc(strlen(((pPokemon)pok)->name)+1);
//	strcpy(newpok->name,((pPokemon)pok)->name);
//	if(newpok->name==NULL){
//		printf("No memory available.\n");
//		free(newpok);
//		return NULL;
//	}
//	newpok->species = (char*)malloc(strlen(((pPokemon)pok)->species)+1);
//	strcpy(newpok->species,((pPokemon)pok)->species);
//	if(newpok->species==NULL){
//		printf("No memory available.\n");
//		free(newpok->name);
//		free(newpok);
//		return NULL;
//	}
//	newpok->type=((pPokemon)pok)->type;
	return newpok;
	}





