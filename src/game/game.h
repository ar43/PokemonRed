#pragma once
#include "../sys/frame.h"
#include "player.h"
#include "world.h"

struct Debug
{
	bool drawPlayer = false;
	bool drawSquare = false;
	bool drawColl = false;
	bool fastMode = false;
	bool noclip = false;
	bool darken = false;
};

class Game
{
public:
	Game();
	void update();
	void prelogic();
	void init();
	//Camera camera;
	Frame frame;
	Player player;
	World world;
	Debug debug;
	//Action action;
private:
};