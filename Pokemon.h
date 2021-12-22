#ifndef POKEMON_H_
#define POKEMON_H_
#include <string.h>
#include "Defs.h"
typedef struct Type_t{
	char* name;
	int pokemon_Num;
	struct Type_t** effective_against_me;
	int num_me;
	struct Type_t** effective_against_others;
	int num_other;
}Type;
typedef Type* pType;

typedef struct bio_Pokemon_t{
	float height;
	float weight;
	int attack;
}bio_Pokemon;

typedef struct Pokemon_t{
	char* name;
	pType type;
	char* species;
	bio_Pokemon biolo;
}Pokemon;
typedef Pokemon* pPokemon;


pPokemon createPokemon(char* name, pType type, char* species, bio_Pokemon biolo );
//pType copytype(pType type);
bio_Pokemon create_Bio(float height, float weight, int attack);
bool effective_against_me(pType pokemon_A, pType pokemon_B);
bool effective_against_others(pType pokemon_A, pType pokemon_B);
status erase_Effective_Against_Me_Pokemon(pType pokemon_A, char* pokemon_B);
status erase_Effective_Against_Other_Pokemon(pType pokemon_A, char* pokemon_B);
status print_Pokemon(pPokemon pokemon);
status print_Type(pType type);
pType creatType(char* type_Name);

char* getCategory(element);
int getpokemonAttack(element firstElem ,element secondElem ,int* attackFirst,int* attackSecond);
status freeFunction_type(element);
status freeFunction_pokemon(element);
status printPokemon(element);
status printType(element);
int equalPok(element firstElem ,element secondElem );
element copyPok(element pok);
#endif /* POKEMON_H_ */
