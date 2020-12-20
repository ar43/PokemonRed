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
};