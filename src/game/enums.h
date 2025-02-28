#pragma once

enum class TextType
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
	NUM_TEXT_TYPE
};

enum class NpcMovementMode
{
	WALK,
	STAY
};

enum class NpcMovementDir
{
	ANY_DIR, 
	UP_DOWN,
	LEFT_RIGHT,
	DOWN,
	UP, 
	LEFT,
	RIGHT,
	NONE,
	BOULDER_MOVEMENT_BYTE_2
};

enum class Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

enum class Permission
{
	INDOOR,
	CAVE,
	OUTDOOR
};

enum class EmotionBubble
{
	SHOCK,
	QUESTION,
	HAPPY
};

enum class GrowthRate
{
	GROWTH_MEDIUM_FAST,
	GROWTH_SLIGHTLY_FAST,
	GROWTH_SLIGHTLY_SLOW,
	GROWTH_MEDIUM_SLOW,
	GROWTH_FAST,
	GROWTH_SLOW
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

enum BRIGHTNESS
{
	BRIGHTNESS_LIGHT3,
	BRIGHTNESS_LIGHT2,
	BRIGHTNESS_LIGHT1,
	BRIGHTNESS_NORMAL,
	BRIGHTNESS_DARK1,
	BRIGHTNESS_DARK2,
	BRIGHTNESS_DARK3,
	NUM_BRIGHTNESS
};