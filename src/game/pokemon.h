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
	Pokemon(PokemonData* p_data, int p_level, bool trainer = false);
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

private:
	void calculateStats();
	void setMoves();
	void generateIV(bool trainer);
	int calculateEXP(int level);
};