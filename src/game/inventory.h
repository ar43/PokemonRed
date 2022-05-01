#pragma once
#include "pokemon.h"
#include <vector>

#define BOX_CAPACITY 20
#define NUM_BOXES 12
#define MAX_POKEMON_PARTY 6

class Inventory
{
public:
	Inventory();
	void addPokemon(Pokemon *pokemon);
	void movePokemonToBox(size_t i, size_t box_num);
	void addPokemonToBox(Pokemon* pokemon, size_t box_num);
	void swapPokemon(size_t i, size_t j);
	void releasePokemon(size_t box_num, size_t i);
	void deletePokemon(size_t i);
	void statusReport(int *status);
private:
	std::vector<Pokemon*> pokemonList;
	std::vector<Pokemon*> PC[NUM_BOXES];
};