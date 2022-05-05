#pragma once

struct PokemonStats
{
	int hp;
	int attack;
	int defense;
	int speed;
	int special;
};

class PokemonData
{
public:
	std::string dexId;
	std::string rawName;
	PokemonStats baseStats;
	std::string type[2];
	int catchRate;
	int baseEXP;
	std::string baseLearnset[4];
	GrowthRate growthRate;
	std::vector <std::string> tmhm;
	Texture* front;
	Texture* back;
	std::string getId();
};