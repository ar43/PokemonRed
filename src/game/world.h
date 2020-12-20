#pragma once
#include "map.h"

class World
{
public:
	Map *currentMap;
	void set_active(std::string HSid,bool flag);
};