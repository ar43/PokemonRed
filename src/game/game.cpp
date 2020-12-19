#include "../sys/system.h"

Game::Game()
{

}

void Game::prelogic()
{

}

void Game::update()
{
	player.update();
	
	for (std::vector<Npc>::iterator it = game.world.currentMap->npcs.begin(); it != game.world.currentMap->npcs.end(); ++it)
	{
		it->update();
	}

	textbox.update();
}

void Game::init()
{
	game.world.currentMap = res.getMap("pallet_town");
	player.init();
}