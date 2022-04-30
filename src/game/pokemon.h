#pragma once
#include "pokemon_data.h"

enum class PokemonStatus
{
	NONE,
	PSN,
	BRN,
	FRZ,
	PAR
};

class Pokemon
{
public:
	Pokemon(PokemonData* p_data, int p_level);
	PokemonData *data;
	std::string nickname;
	PokemonStats stats;
	int hp;
	int maxHp();
	int level;
	PokemonStatus status;
	std::string moves[4];
	int exp;
	PokemonStats ev;
	PokemonStats iv;
	int pp[4];
	int trainerId;

	void calculateStats();
	void generateIV();
	int calculateEXP(int level);
};