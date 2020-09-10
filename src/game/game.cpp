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
	textbox.update();
}

void Game::init()
{
	game.world.currentMap = res.getMap("pallet_town");
	player.init();
	SDL_strlcpy(game.textbox.line[0], "Technology is", 32);
	SDL_strlcpy(game.textbox.line[1], "incredible!", 32);
}