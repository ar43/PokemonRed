#pragma once


class Block
{
public:
	Block() {
		width = 32;
		height = 32;
		valid = false;
		surface = NULL;
		texture = NULL;
	}
	SDL_Surface* surface;
	SDL_Texture* texture;

	int width;
	int height;

	bool valid;

	void render(int x, int y);
	void render_static(int x, int y);
};

class Blockset
{
public:
	Block* blocks;
};

class Connection
{
public:
	std::string north;
	std::string west;
	std::string east;
	std::string south;
};

class Map
{
public:
	Map(int h, int w, Blockset *blk, int background, std::string north, std::string west, std::string east, std::string south) {
		width = w;
		height = h;
		blockset = blk;
		this->background = background;
		connection.west = west;
		connection.north = north;
		connection.south = south;
		connection.east = east;
	}
	int width;
	int height;
	int background;
	std::vector<Uint8> blocks;
	Blockset* blockset;
	Connection connection;
	void render(int x, int y);
};

class Tileset
{
public:
	SDL_Surface* surface;
	SDL_Texture* texture;
	Uint32 format;
};
