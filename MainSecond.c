#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Pokemon.h"
#include "Defs.h"
#include "LinkedList.h"
#include "MaxHeap.h"
#include "BattleByCategory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Pokemon.h"
#include "Defs.h"



int* numTypes;
int counter=0;




int poki=0;
pType searchtype(char* name,int numTypes,Type** all_types){

	int i;
	for(i=0;i<numTypes;i++){
		if(strcmp(all_types[i]->name,name)==0)
			return all_types[i];
	}
	return NULL;
}

int main(int argc, char* argv[]){
	Battle battle;
	char* category;
	char* effective_me;
	int count=0;
	int ind=0;
	char* end;
	int type = strtod(argv[1],&end);
	int capacityInType;
	capacityInType= strtod(argv[2], &end);
	Type* all_types[type];
	//pPokemon all_pokemons[capacityInType*type];
//	int f;
//	for(f=0;f<capacityInType*type;f++){
//		all_pokemons[f]=NULL;
//	}
	FILE * fp;


	fp = fopen(argv[3], "r");
	int a =300;
	int typeORpokemon=0;
	char buffer[a];
	char* param;
	while(fgets(buffer,a,fp)){
		if(strcmp(buffer,"Types\r\n")==0){
			typeORpokemon=1;

			continue;
		}



		else if((strncmp(buffer, "\t", strlen("\t"))==0)){
		while(strcmp(buffer,"Pokemons\r\n")!=0){
			if(strstr(buffer,"me:")!=NULL){
				char* tempo=buffer;
				tempo = strtok(tempo,"\t");
				effective_me=strtok(tempo," ");
				pType add_to=searchtype(effective_me,type,all_types);
				tempo=strtok(NULL,"");
				tempo=strtok(tempo,":");
				tempo=strtok(NULL,"");
				tempo=strtok(tempo,"\r\n");
				int i =0;
				while(tempo!=NULL){
					if(i==0){
					tempo=strtok(tempo,",");
					pType to_add=searchtype(tempo,type,all_types);
					effective_against_me(add_to,to_add);
					i=1;
					}
					else{
					tempo=strtok(NULL,",");
					if(tempo==NULL){
						break;
					}
					Type* to_add=searchtype(tempo,type,all_types);
					effective_against_me(add_to,to_add);
					i=0;
					tempo=strtok(NULL,",");
					}
				}
				fgets(buffer,a,fp);

			}
			else if(strstr(buffer,"other:")!=NULL){
				char* tempo=buffer;
				tempo = strtok(tempo,"\t");
				effective_me=strtok(tempo," ");
				Type* add_to=searchtype(effective_me,type,all_types);
				tempo=strtok(NULL,"");
				tempo=strtok(tempo,":");
				tempo=strtok(NULL,"");
				tempo=strtok(tempo,"\r\n");
				int i =0;
				while(tempo!=NULL){
					if(i==0){
					tempo=strtok(tempo,",");
					Type* to_add=searchtype(tempo,type,all_types);
					effective_against_others(add_to,to_add);
					i=1;
					}
					else{
						tempo=strtok(NULL,",");
						if(tempo==NULL){
							break;
						}
					Type* to_add=searchtype(tempo,type,all_types);
					effective_against_others(add_to,to_add);
					i=0;
					tempo=strtok(NULL,",");
					}
				}
				fgets(buffer,a,fp);
			}
		}
		if(strcmp(buffer,"Pokemons\r\n")==0){
			typeORpokemon=3;
			continue;
		}
		}
	while(typeORpokemon==1){
		char* temporaly = strtok(buffer,"\r\n");
		category = (char*)malloc(strlen(temporaly)+1);
		strcpy(category,temporaly);
		battle = createBattleByCategory(capacityInType,type,category,equalPok,copyPok,freeFunction_pokemon,getCategory,getpokemonAttack,printPokemon);
		param = strtok(buffer,",");
		pType tempty=creatType(param);
		all_types[counter]=tempty;
		counter++;
		int ind;
		for(ind=0;ind<type-2;ind++){
			param = strtok(NULL,",");
			pType tempty=creatType(param);
			all_types[counter]=tempty;
			counter++;
		}
		param = strtok(NULL,"\r\n");
		tempty=creatType(param);
		all_types[counter]=tempty;
		counter++;
		break;
	}
	while(typeORpokemon==3){
		if(ind==1){
			if(fgets(buffer,a,fp)==NULL){
				break;
			}
		}
		param = strtok(buffer,",");
		char* name=param;
		param = strtok(NULL,",");
		char* species=param;
		param = strtok(NULL,",");
		float height=atof(param);
		param = strtok(NULL,",");
		float weight=atof(param);
		param = strtok(NULL,",");
		int attack=atoi(param);
		param = strtok(NULL,"\r\n");
		pType typ= searchtype(param,type,all_types);
		typ->pokemon_Num++;
		bio_Pokemon bio = create_Bio( height,  weight,  attack);
		pPokemon poke=createPokemon(name,typ,species,bio);
		insertObject(battle,poke);
		count++;
		ind=1;
	}
}






	fclose(fp);
	char ch='0';

		while (ch!='6'){
	 	printf("Please choose one of the following numbers:\n");
	 	printf("1 : Print all Pokemons by types\n");
		printf("2 : Print all Pokemons types\n");
		printf("3 : Insert Pokemon to battles training camp\n");
		printf("4 : Remove strongest Pokemon by type\n");
		printf("5 : Fight\n");
		printf("6 : Exit\n");

		scanf(" %s", &ch );
		switch( ch ){
		case '1':

			displayObjectsByCategories(battle);
			break;


		case '2':
			for(int size4=0;size4<type;size4++){
				print_Type(all_types[size4]);
			}
			break;
		case '3':
			printf("Please enter Pokemon type name:\n");
			char type_find[300];
			scanf("%s",type_find);
			int k;
			int f=0;
			pType typefound;
			for(k=0;k<type;k++){
				if(strcmp(all_types[k]->name,type_find)==0){
					f=1;
					typefound = all_types[k];
				}
			}
			if(f==0){
				printf("Type name doesn't exist.\n");
				break;
			}
			int tocheck = getNumberOfObjectsInCategory(battle,type_find);
			if(tocheck==capacityInType){
				printf("Type at full capacity.\n");
				break;
			}
			char pok_name[300];
			char pok_species[300];
			float pok_height=0;
			float pok_weight=0;
			int pok_attack=0;
			printf("Please enter Pokemon name:\n");
			scanf("%s",pok_name);

			printf("Please enter Pokemon species:\n");
			scanf("%s",pok_species);

			printf("Please enter Pokemon height:\n");
			scanf("%f",&pok_height);

			printf("Please enter Pokemon weight:\n");
			scanf("%f",&pok_weight);

			printf("Please enter Pokemon attack:\n");
			scanf("%d",&pok_attack);
			bio_Pokemon bio = create_Bio(pok_height,pok_weight,pok_attack);
			pPokemon pok = createPokemon(pok_name,typefound,pok_species,bio);
			typefound->pokemon_Num++;
			insertObject(battle,pok);
			printf("The Pokemon was successfully added.\n");
			count++;
			print_Pokemon(pok);
				break;

		case '4':
			printf("Please enter type name:\n");
			char type_find1[300];
			int ind=0;
			int j ;
			int m ;
			scanf("%s",type_find1);
			for(j=0;j<type;j++){
				if(strcmp(all_types[j]->name,type_find1)==0){
					ind=1;
					m=j;
				}
			}
			if (ind==0){
				printf("Type name doesn't exist.\n");
				break;
			}
			int tocheck1 = getNumberOfObjectsInCategory(battle,type_find1);
			if(tocheck1==0){
				printf("There is no Pokemon to remove.\n");
				break;
			}
			printf("The strongest Pokemon was removed:\n");
			all_types[m]->pokemon_Num--;
			pPokemon pokd = removeMaxByCategory(battle,type_find1);
			print_Pokemon(pokd);
			freeFunction_pokemon(pokd);
			count--;
			break;

		case '5':
			printf("Please enter Pokemon type name:\n");
				char type_fight[300];
				scanf("%s",type_fight);
				pType tempor;
				int ind1=0;
				int l;
				for(l=0;l<type;l++){
					if(strcmp(all_types[l]->name,type_fight)==0){
						ind1=1;
						tempor= all_types[l];
					}
				}
				if (ind1==0){
					printf("Type name doesn't exist.\n");
					break;
				}
				char pok_name1[300];
				char pok_species1[300];
				float pok_height1=0;
				float pok_weight1=0;
				int pok_attack1=0;
				printf("Please enter Pokemon name:\n");
				scanf("%s",pok_name1);

				printf("Please enter Pokemon species:\n");
				scanf("%s",pok_species1);

				printf("Please enter Pokemon height:\n");
				scanf("%f",&pok_height1);

				printf("Please enter Pokemon weight:\n");
				scanf("%f",&pok_weight1);

				printf("Please enter Pokemon attack:\n");
				scanf("%d",&pok_attack1);
				bio_Pokemon bio1 = create_Bio(pok_height1,pok_weight1,pok_attack1);
				pPokemon pok1 = createPokemon(pok_name1,tempor,pok_species1,bio1);
				fight(battle,pok1);
				freeFunction_pokemon(pok1);
				break;

		case '6':
			destroyBattleByCategory(battle);

			printf("All the memory cleaned and the program is safely closed.\n");
			exit(1);
			break;
		default: printf("Please choose a valid number.\n");
				break;

}
		}
}
