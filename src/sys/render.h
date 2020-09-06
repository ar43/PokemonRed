#pragma once
#include "../game/enums.h"

class Render
{
public:
	void render();
	void debug();
	void draw_map();
	void draw_overlay();
};

class Sprite
{
public:
	SDL_Surface* surface;
	SDL_Texture* texture;
	Uint32 format;
	int w;
	int h;
	int size;
	int animIndex;
	void render(int x, int y, Direction dir);
	void render_static(int x, int y, Direction dir);
};


