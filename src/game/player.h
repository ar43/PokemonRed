#pragma once

enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

#define PLAYER_OFFSET_X 64
#define PLAYER_OFFSET_Y 60

#define WORLD_OFFSET_X 16
#define WORLD_OFFSET_Y 24

class Player 
{
public:
	Player();
	int x;
	int y;
	void update();
private:
	Direction dir;
	Direction turnDir;
	int turning;
	bool moving;
	int moveIndex;
	void move();
};