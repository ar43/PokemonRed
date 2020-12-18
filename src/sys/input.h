#pragma once

enum Keycatchers
{
	KEYCATCHERS_NORMAL,
	KEYCATCHERS_CONSOLE,
	KEYCATCHERS_TEXTBOX
};

enum SomeKeys
{
	ARROW_DOWN,
	ARROW_UP,
	ARROW_LEFT,
	ARROW_RIGHT,
	KEY_Y,
	KEY_X,
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
	int block;
	void clear();

private:
	void catchMain(SDL_Event *e);
	void catchTextbox(SDL_Event* e);
	void catchConsole(SDL_Event *e);
	void catchPriority(SDL_Event *e);
	bool clicked;
	void clickOn(int x, int y);
};