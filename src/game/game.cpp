#include "../sys/system.h"

Game::Game()
{
	rivalName = "BLUE";
}

void Game::prelogic()
{

}

void Game::update()
{
	player.update();

	world.currentMap->runScript();
	
	for (auto it : world.currentMap->objects)
	{
		it->update();
	}

	textbox.update();
}

void Game::init()
{
	world.currentMap = res.getMap("pallet_town");
	player.init();
	canRunScript = true;
}

void Game::setEvent(std::string eventName, bool set)
{
	eventMap[eventName] = set;
}

bool Game::checkEvent(std::string eventName)
{
	if (!(eventMap.find(eventName) == eventMap.end()))
	{
		return eventMap[eventName];
	}
	else
	{
		return false;
	}
}

void Game::runDebugScript()
{
    char filename[128] = { 0 };
    SDL_snprintf(filename, sizeof(filename), "assets/scripts/debug.lua");
    if (!util::file_exists(filename))
        return;

    int ret = luaL_dofile(lua::L, filename);
    lua::print_error(ret);
}