#pragma once

enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

enum Permission
{
	INDOOR,
	CAVE,
	OUTDOOR
};

struct Position
{
	int x;
	int y;
};

struct Warp
{
	std::string from;
	std::string to;
	Position at;
	int warpIn;
};