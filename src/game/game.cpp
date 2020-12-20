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
	
	for (auto it : game.world.currentMap->objects)
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