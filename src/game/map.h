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
};

class Blockset
{
public:
	Block* blocks;
};

class Map
{
public:
	Map(int h, int w, Blockset *blk) {
		width = w;
		height = h;
		blockset = blk;
	}
	int width;
	int height;
	std::vector<Uint8> blocks;
	Blockset* blockset;
	void render();
};

class Tileset
{
public:
	SDL_Surface* surface;
	SDL_Texture* texture;
	Uint32 format;
};
