#pragma once

struct Party
{
	std::vector<Pokemon*> pokemonList;
	void addPokemon(Pokemon *pokemon);
};

class TrainerData
{
public:
	void addParty(Party* party);
	Party* getParty(int rosterID);
private:
	std::vector<Party*> parties;
};