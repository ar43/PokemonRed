#pragma once
#include "map.h"

class World
{
public:
	Map *currentMap;
	void set_active(std::string HSid,bool flag);
	void on_map_change();
	std::vector<Textset*> common_texts;
};