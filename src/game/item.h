#pragma once
#include "object.h"

class Item : public Object 
{
private:
public:
	Item();

	std::string itemID;

	void update();
	void init();
	void render();
	void get_screen_pos(Position* pnt);
	void get_world_pos(Position* pos);
	void get_block_pos(Position* pos);
	void activate();
};