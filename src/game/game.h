#pragma once
#include "../sys/frame.h"
#include "player.h"

class Game
{
public:
	Game();
	void update();
	void prelogic();
	//Camera camera;
	Frame frame;
	Player player;
	//World world;
	//Action action;
private:
};