#pragma once
#include "trainer_data.h"

struct BattleAnimation
{
	void reset();

	bool play = false;
	int* counter = nullptr;
	int x_offset = 0;
	int y_offset = 0;
};

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
	void pre_render();
	
	bool inBattle = false;
	bool starting = false;
	
	int battleIndex = 0;
	int brightness = 3;

	int scriptIndex = 0;

	std::string enemyMonNick = "???";
	std::string battleMonNick = "???";
	
private:
	void first_animation();
	void second_animation();
	void render_player_pokeballs();
	void render_frame_bottom();
	void render_enemy_info();
	void render_hp(int hp, int max_hp, int x_start, int y);
	void render_player_info();
	void render_player_pokemon();

	void update_enemy_hp();
	void update_player_hp();

	Party* opp_party;
	Party* player_party;
	bool trainerBattle = false;
	std::string trainerName;
	Position ash_position;

	int scrollIndex = 0;
	int enemyScrollIndex = 0;
	int delayScript = 0;
	int currEnemyMonIndex = 0;
	int currPlayerMonIndex = 0;

	int enemyHp = 0;
	int playerHp = 0;

	bool drawPlayerPokeballs = true;
	bool drawFrameBottom = true;
	bool drawEnemyInfo = false;
	bool drawPlayerInfo = true;
	int drawPlayerMon = 0;

	Texture enemyPokemonText;
	Texture enemyPokemonLvl;

	Texture playerPokemonText;
	Texture playerPokemonLvl;
	Texture playerPokemonHp;

	void create_enemy_pokemon_text_texture();
	void create_player_pokemon_text_texture();

	BattleAnimation pokemonAppear;
	void playanim_pokemonappear();
};