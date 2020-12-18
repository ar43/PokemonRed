#pragma once

class Npc
{
private:
	Position displacement;
	bool waiting;
public:
	Npc();
	Position pos;
	std::string spriteName;
	
	NpcMovementMode movMode;
	NpcMovementDir movDir;
	int textID;
	void update();
	void init();
	void render();
};
