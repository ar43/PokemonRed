#pragma once

enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

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