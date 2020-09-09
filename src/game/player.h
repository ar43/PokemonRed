#pragma once

#include "../sys/render.h"
#include "map.h"
#include "enums.h"

#define PLAYER_OFFSET_X 64
#define PLAYER_OFFSET_Y 60

#define WORLD_OFFSET_X 16
#define WORLD_OFFSET_Y 8

class Player 
{
public:
	Player();
	void getSquarePosition(Position *position);
	void getBlockPosition(Position* position);
	Position* getPosition();
	Sprite* sprite;
	void update();
	void init();
	void render();
	void warp();
	int warpIndex;
private:
	Direction dir;
	Position pos;
	Direction turnDir;
	int turning;
	bool moving;
	int moveIndex;
	bool warping;
	void move();
	void change_map();
	void warp_check(bool carpet);
	bool collision_check();
	std::string lastMap;
	Warp* nextWarp;
};