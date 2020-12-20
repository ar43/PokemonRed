#pragma once

class Object {
protected:
	Direction dir;
public:
	Object();
	Position pos;
	std::string spriteName;
	Sprite* sprite;
	bool spriteDraw;
	int textID;
	bool active;

	NpcMovementMode movMode;
	NpcMovementDir movDir;

	virtual void update() = 0;
	virtual void init() = 0;
	virtual void render() = 0;
	void get_world_pos(Position* pnt);
};