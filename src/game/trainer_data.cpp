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
