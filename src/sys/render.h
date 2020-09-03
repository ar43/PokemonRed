#pragma once

class Render
{
public:
	void render();
	void test();
};

class Tileset
{
public:
	SDL_Surface *surface;
	SDL_Texture* texture;
	Uint32 format;
};

class Block
{
public:
	Block() {
		width = 32;
		height = 32;
	}
	SDL_Surface* surface;
	SDL_Texture* texture;
	
	int width;
	int height;
	void render(int x, int y);
};