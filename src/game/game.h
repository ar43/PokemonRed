#pragma once
#include "../sys/frame.h"
#include "player.h"
#include "world.h"

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
	//Action action;
private:
};