#pragma once

enum TextType
{
	TYPE_TEXT,
	TYPE_NEXT,
	TYPE_LINE,
	TYPE_PARA,
	TYPE_CONT,
	TYPE_DONE,
	TYPE_PROMPT,
	TYPE_PAGE,
	TYPE_DEX,
	TYPE_TEXT_END,
	TYPE_TEXT_START,
	TYPE_TEXT_RAM,
	TYPE_TEXT_DECIMAL,
	TYPE_TEXT_BCD,
};

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