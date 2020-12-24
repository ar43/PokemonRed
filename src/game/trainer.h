#pragma once
#include "object.h"

class Trainer : public Object 
{
private:
	Position displacement;
	bool waiting;
public:
	Trainer();

	NpcMovementMode movMode;
	NpcMovementDir movDir;

	std::string trainerClass;
	int rosterID;

	void update();
	void init();
	void render();
	void get_screen_pos(Position* pnt);
	void get_world_pos(Position* pos);
	void get_block_pos(Position* pos);
};