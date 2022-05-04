#pragma once

struct Party
{
	std::vector<Pokemon*> pokemonList;
	void addPokemon(Pokemon *pokemon);

	std::string firstMonNick();
	int firstMonId();
	void statusReport(int *status);

};

class TrainerData
{
public:
	void addParty(Party* party);
	Party* getParty(int rosterID);
private:
	std::vector<Party*> parties;
};