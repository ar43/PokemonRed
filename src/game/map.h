#pragma once
#include "enums.h"
#include "sign.h"
#include "text.h"
#include "npc.h"
#include <vector>

enum MapAnimation
{
	ANIMATION_NONE,
	ANIMATION_FLOWER,
	ANIMATION_WATER
};

class Tileset
{
public:
	SDL_Surface* surface;
	SDL_Texture* texture[NUM_BRIGHTNESS];
	Uint32 format;
	std::vector<Uint8>* collData;
	std::vector<Uint8>* warpData;
	int w;
	int h;
	Uint8 grassTile;
	std::string grassName;
	Uint8 counterTiles[3];
	Permission permission;
};

class Block
{
public:
	Block() {
		width = 32;
		height = 32;
		valid = false;
		surface = NULL;
		for (int i = 0; i < NUM_BRIGHTNESS; i++)
		{
			texture[i] = NULL;
		}
		

		for (int i = 0; i < 4; i++)
		{
			for(int j = 0; j < 4; j++)
			{ 
				solid[i][j] = true;
			}
		}

		for (int i = 0; i < 4; i++)
		{
			warp[i] = false;
		}
		for (int i = 0; i < 4; i++)
		{
			warp_up[i] = false;
		}
		for (int i = 0; i < 4; i++)
		{
			warp_down[i] = false;
		}
		for (int i = 0; i < 4; i++)
		{
			warp_left[i] = false;
		}
		for (int i = 0; i < 4; i++)
		{
			warp_right[i] = false;
		}

		for (int i = 0; i < 16; i++)
		{
			animation[i] = ANIMATION_NONE;
		}

		for (int i = 0; i < 16; i++)
		{
			grassTile[i] = false;
		}
	}
	SDL_Surface* surface;
	SDL_Texture* texture[NUM_BRIGHTNESS];

	int width;
	int height;

	bool valid;
	bool solid[4][4];
	bool warp[4];
	bool warp_up[4];
	bool warp_down[4];
	bool warp_left[4];
	bool warp_right[4];
	bool grassTile[16];
	Uint8 tile[4];
	
	MapAnimation animation[16];

	void render(int x, int y);
	void render_static(int x, int y);
};

class Blockset
{
public:
	Block* blocks;
	std::string name;
	Tileset* tileset;
};

class Connection
{
public:
	std::string north;
	int northOffset;

	std::string west;
	int westOffset;

	std::string east;
	int eastOffset;

	std::string south;
	int southOffset;
};



class Map
{
public:
	Map(int h, int w, Blockset *blk, int background, std::string north, int northOffset, std::string west, int westOffset, std::string east, int eastOffset, std::string south, int southOffset) {
		width = w;
		height = h;
		blockset = blk;
		this->background = background;
		connection.west = west;
		connection.westOffset = westOffset;
		connection.north = north;
		connection.northOffset = northOffset;
		connection.south = south;
		connection.southOffset = southOffset;
		connection.east = east;
		connection.eastOffset = eastOffset;
		currentScript = 0;
	}
	std::string name;
	std::string fileName;
	int width;
	int height;
	int background;
	std::vector<Uint8> blocks;
	Blockset* blockset;
	Tileset* tileset;
	Connection connection;
	std::vector<Position> grassEffect;
	std::vector<Warp> warps;
	std::vector<Sign> signs;
	std::vector<Textset*> texts;
	std::vector<Object*> objects;
	void render(int x, int y);
	int currentScript;
	void runScript();
};


class Texture
{
public:
	SDL_Surface* surface; //kind of useless ngl
	SDL_Texture* texture = nullptr;
	SDL_Texture* tilemap_3x3 = nullptr;
	SDL_Texture* tilemap_5x5 = nullptr;
	Uint32 format;
	int w;
	int h;
	void scale(int new_w, int new_h);
	void generate_tilemaps();
	void render(int x, int y, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void render_tilemap(int x, int y, bool t3);
	void render_scale(int x, int y, int new_w, int new_h, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void render_ex(int x, int y, int x2, int y2, int w, int h, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void render_special(int x, int y, int num, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void render_grass(int x, int y, bool upper);
};
