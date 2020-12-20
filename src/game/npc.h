#pragma once

#include "object.h"

class Npc : public Object
{
private:
	Position displacement;
	bool waiting;
public:
	Npc();

	void update();
	void init();
	void render();
};
