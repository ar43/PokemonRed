#pragma once

#include "object.h"

class Npc : public Object
{
private:
	
	int waitIndex;
	int moveIndex;
	bool moving;
	void wait();
	void move();
	void generateDir();
	bool collision_check();
public:
	Npc();
	Position displacement;
	void update();
	void init();
	void render();
	
	void get_world_pos(Position* pnt);
	void get_world_pos(Position* pnt, Position* custompos);
	
};
