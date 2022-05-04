#include "../sys/system.h"

Inventory::Inventory()
{

}

void Inventory::addPokemon(Pokemon* pokemon)
{
	if (party.pokemonList.size() >= MAX_POKEMON_PARTY)
	{
		util::error("Trying to add a pokemon to a full party!");
		return;
	}
	party.pokemonList.push_back(pokemon);
	printf("dbg: added pokemon to inventory\n");
}

void Inventory::movePokemonToBox(size_t i, size_t box_num)
{
	if (i < 0 || i >= party.pokemonList.size())
	{
		util::error("invalid index");
		return;
	}
	Pokemon* mon = party.pokemonList.at(i);
	party.pokemonList.erase(party.pokemonList.begin() + i);
	addPokemonToBox(mon, box_num);

}

void Inventory::swapPokemon(size_t i, size_t j)
{
	if (i < 0 || i >= party.pokemonList.size())
	{
		util::error("invalid index i");
		return;
	}
	else if (j < 0 || j >= party.pokemonList.size())
	{
		util::error("invalid index j");
		return;
	}

	std::swap(party.pokemonList[i], party.pokemonList[j]);

}

void Inventory::releasePokemon(size_t box_num, size_t i)
{
	if (box_num >= NUM_BOXES || box_num < 0)
	{
		util::error("invalid box index");
		return;
	}
	else if (i < 0 || i >= PC[box_num].size())
	{
		util::error("bad mon index");
		return;
	}
	Pokemon* mon = PC[box_num].at(i);
	delete mon;
	PC[box_num].erase(PC[box_num].begin() + i);
}

void Inventory::deletePokemon(size_t i) //debug, should not be used in actual game
{
	if (i < 0 || i >= party.pokemonList.size())
	{
		util::error("invalid index");
		return;
	}
	Pokemon* mon = party.pokemonList.at(i);
	delete mon;
	party.pokemonList.erase(party.pokemonList.begin() + i);
}

Party* Inventory::getParty()
{
	return &party;
}



void Inventory::addPokemonToBox(Pokemon* pokemon, size_t box_num)
{
	if (box_num >= NUM_BOXES || box_num < 0)
	{
		util::error("invalid box index");
		return;
	}
	else if (PC[box_num].size() >= BOX_CAPACITY)
	{
		util::error("box is full");
		return;
	}
	PC[box_num].push_back(pokemon);
}