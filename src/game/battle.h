#pragma once
#include "trainer_data.h"

class Battle
{
public:
	Battle();
	void begin_trainer(std::string trainerName, Party* opp_party);
	void begin_wild(std::string pokemonName, int level);
	void start();
	void on_begin();
	void update();
	void render();
	
	bool inBattle = false;
	bool starting = false;
	
	int battleIndex = 0;
	int brightness = 3;

	std::string enemyMonNick = "???";
	
private:
	void first_animation();
	void second_animation();
	void render_player_pokeballs();
	Party* opp_party;
	bool trainerBattle = false;
	std::string trainerName;
	Position ash_position;
	int scrollIndex = 0;
};