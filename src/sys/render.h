#pragma once
#include "../game/enums.h"

#define TEXTBOX_WIDTH 160
#define TEXTBOX_HEIGHT 48

class Render
{
public:
	void render();
	void debug();
	void draw_map();
	void draw_overlay();
	void draw_objects();
private:
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
	void render(Position *pos, Direction dir, bool speedup = false);
	void render_static(int x, int y, Direction dir);
	bool is_on_screen(Position *pos);
	bool is_on_screen_strict(Position* pos);
	
};


