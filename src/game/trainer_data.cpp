#include "../sys/system.h"

void Party::addPokemon(Pokemon* pokemon)
{
	if (pokemonList.size() >= MAX_POKEMON_PARTY)
	{
		util::error("Trying to add a pokemon to a full party!");
		return;
	}
	pokemonList.push_back(pokemon);
	//printf("dbg: added pokemon to inventory\n");
}

void TrainerData::addParty(Party* party)
{
	parties.push_back(party);
}

Party* TrainerData::getParty(int rosterID)
{
	int fixed_roster_id = rosterID - 1;
	if (fixed_roster_id < 0 || fixed_roster_id >= parties.size())
	{
		sys.error("Bad rosterID in TrainerData::getParty");
		return nullptr;
	}
	return parties.at(fixed_roster_id);
}

std::string Party::firstMonNick()
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

int Party::firstMonId()
{
	int num = 0;
	for (auto it : pokemonList)
	{
		if (it->hp > 0)
		{
			return num;
		}
		num++;
	}
	return -1;
}

void Party::statusReport(int* status)
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
