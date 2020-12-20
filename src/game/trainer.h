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
};