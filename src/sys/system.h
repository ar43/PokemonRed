#pragma once
#undef QDECL
#define	QDECL	__cdecl

extern "C"
{
	#include "../include/lua/lua.h"
	#include "../include/lua/lauxlib.h"
	#include "../include/lua/lualib.h"
}

#include "../include/LuaBridge/LuaBridge.h"

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
#include "frame.h"
#include "input.h"
#include "render.h"
#include "../game/game.h"
#include "../game/player.h"
#include "../game/pokemon_data.h"
#include "resource_manager.h"
#include "../game/map.h"
#include "../game/world.h"
#include "../game/constants.h"
#include "../game/sign.h"
#include "../game/textbox.h"
#include "../game/text.h"
#include "../game/object.h"
#include "../game/npc.h"
#include "../game/trainer.h"
#include "../game/item.h"
#include "console/console.h"
#include "console/cmds.h"
#include "utility.h"
#include "../game/lua.h"

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
	void load_tilesets();
	void load_blocksets();
	void load_sprites();
	void load_pkm_textures();
	void load_pkm_data();
	void load_text_redefinitions();
	void hide_show_objects();
};

extern System sys;
extern Game game;
extern Input input;
extern Render rend;
extern ResourceManager res;
