#pragma once
#include "enums.h"

enum MapAnimation
{
	ANIMATION_NONE,
	ANIMATION_FLOWER,
	ANIMATION_WATER
};

class Block
{
public:
	Block() {
		width = 32;
		height = 32;
		valid = false;
		surface = NULL;
		texture = NULL;

		for (int i = 0; i < 4; i++)
		{
			for(int j = 0; j < 4; j++)
			{ 
				solid[i][j] = true;
			}
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
	SDL_Texture* texture;

	int width;
	int height;

	bool valid;
	bool solid[4][4];
	bool grassTile[16];
	
	MapAnimation animation[16];

	void render(int x, int y);
	void render_static(int x, int y);
};

class Blockset
{
public:
	Block* blocks;
	std::string name;
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

class Tileset
{
public:
	SDL_Surface* surface;
	SDL_Texture* texture;
	Uint32 format;
	std::vector<Uint8>* collData;
	int w;
	int h;
	Uint8 grassTile;
	std::string grassName;
	Uint8 counterTiles[3];
	Permission permission;
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
	}
	int width;
	int height;
	int background;
	std::vector<Uint8> blocks;
	Blockset* blockset;
	Tileset* tileset;
	Connection connection;
	std::vector<Position> grassEffect;
	void render(int x, int y);
};


class Texture
{
public:
	SDL_Surface* surface;
	SDL_Texture* texture;
	Uint32 format;
	int w;
	int h;
	void render(int x, int y);
	void render_grass(int x, int y);
};
