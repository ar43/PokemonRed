#pragma once

class Npc
{
private:
	Position displacement;
	bool waiting;
	Direction dir;
public:
	Npc();
	Position pos;
	std::string spriteName;
	Sprite *sprite;
	
	NpcMovementMode movMode;
	NpcMovementDir movDir;
	int textID;
	void update();
	void init();
	void render();
	void get_world_pos(Position* pnt);
};
