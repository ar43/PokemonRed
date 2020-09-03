#pragma once

enum Keycatchers
{
	KEYCATCHERS_NORMAL,
	KEYCATCHERS_CONSOLE,
	KEYCATCHERS_INVENTORY
};

enum SomeKeys
{
	ARROW_DOWN,
	ARROW_UP,
	ARROW_LEFT,
	ARROW_RIGHT,
	NUM_KEYS
};



class Input
{
public:
	Input();
	SDL_Event e;
	Keycatchers keycatchers;
	void process(SDL_Event *e);
	bool keyDown[NUM_KEYS];
	

private:
	void catchMain(SDL_Event *e);
	void catchConsole(SDL_Event *e);
	void catchPriority(SDL_Event *e);
	bool clicked;
	void clickOn(int x, int y);
};