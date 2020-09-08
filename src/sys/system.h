#pragma once

#include <stdio.h>
#include <Windows.h>
#include <math.h>
#include <map>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <string>
#include <time.h>
#include <iostream>

#include "timer.h"
#include "utility.h"
#include "frame.h"
#include "console/console.h"
#include "console/cmds.h"
#include "input.h"
#include "render.h"
#include "../game/game.h"
#include "../game/player.h"
#include "resource_manager.h"
#include "../game/map.h"
#include "../game/world.h"
#include "../game/constants.h"

#define GAME_WIDTH 160
#define GAME_HEIGHT 144

class System
{

public:
	System();
	void init();
	void close();
	void load_media();
	bool requestQuit;
	SDL_Window* getWindow();
	SDL_Renderer* getRenderer();
	void error(const char* pMsg);
	//void loadMedia();
	Console console;

private:
	//void loadFonts();
	//void loadTexts();
	//void loadTextures();
	//void loadEnts();
	//void loadMaps();
	//void startTimers();
	SDL_Window* window;
	SDL_Renderer* renderer;
	void load_maps();
};

extern System sys;
extern Game game;
extern Input input;
extern Render rend;
extern ResourceManager res;
