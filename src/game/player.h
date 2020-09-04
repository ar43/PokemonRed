#pragma once

enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

struct Position
{
	int x;
	int y;
};

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
	void update();
private:
	Direction dir;
	Position pos;
	Direction turnDir;
	int turning;
	bool moving;
	int moveIndex;
	void move();
	void change_map();
	bool collision_check();
};