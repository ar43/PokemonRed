#pragma once
#include "../sys/frame.h"
#include "player.h"
#include "world.h"

struct Debug
{
	bool drawPlayer = true;
	bool drawSquare = false;
	bool drawColl = false;
};

class Game
{
public:
	Game();
	void update();
	void prelogic();
	//Camera camera;
	Frame frame;
	Player player;
	World world;
	Debug debug;
	//Action action;
private:
};