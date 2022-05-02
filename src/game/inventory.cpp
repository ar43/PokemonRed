#include "../sys/system.h"

Inventory::Inventory()
{

}

void Inventory::addPokemon(Pokemon* pokemon)
{
	if (pokemonList.size() >= MAX_POKEMON_PARTY)
	{
		util::error("Trying to add a pokemon to a full party!");
		return;
	}
	pokemonList.push_back(pokemon);
	printf("dbg: added pokemon to inventory\n");
}

void Inventory::movePokemonToBox(size_t i, size_t box_num)
{
	if (i < 0 || i >= pokemonList.size())
	{
		util::error("invalid index");
		return;
	}
	Pokemon* mon = pokemonList.at(i);
	pokemonList.erase(pokemonList.begin() + i);
	addPokemonToBox(mon, box_num);

}

void Inventory::swapPokemon(size_t i, size_t j)
{
	if (i < 0 || i >= pokemonList.size())
	{
		util::error("invalid index i");
		return;
	}
	else if (j < 0 || j >= pokemonList.size())
	{
		util::error("invalid index j");
		return;
	}

	std::swap(pokemonList[i], pokemonList[j]);

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
	if (i < 0 || i >= pokemonList.size())
	{
		util::error("invalid index");
		return;
	}
	Pokemon* mon = pokemonList.at(i);
	delete mon;
	pokemonList.erase(pokemonList.begin() + i);
}

void Inventory::statusReport(int *status)
{
	if (pokemonList.size() == 0)
	{
		sys.error("Entered battle with empty party.");
	}

	for (int j = 0; j < 6; j++)
		status[j] = 24;

	int i = 0;

	for (Pokemon* pokemon : pokemonList)
	{
		if (pokemon->hp > 0)
			status[i] = 0;
		else
			status[i] = 16;
		i++;
	}
}

std::string Inventory::firstMonNick()
{
	for (auto it : pokemonList)
	{
		if (it->hp > 0)
		{
			if (it->nickname.empty())
			{
				return it->data->getId();
			}
			else
			{
				return it->nickname;
			}
		}
	}
	return "ERRORNAME";
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