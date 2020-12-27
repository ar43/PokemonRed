#pragma once

#include "object.h"
#include <queue>

class Npc : public Object
{
protected:
	
	int waitIndex;
	int moveIndex;
	bool moving;
	

	void wait();
	void move();
	void generateDir();
	bool collision_check();
	int emoteTime;
	EmotionBubble emote;
	std::queue<Direction> movementQueue;
public:
	Npc();
	Position displacement;
	void update();
	void init();
	void render();
	void set_emote(EmotionBubble index);
	int get_emote_time();
	void get_screen_pos(Position* pnt);
	void get_screen_pos(Position* pnt, Position* custompos);
	void get_world_pos(Position* pos);
	void get_block_pos(Position* pos);
	void activate();
	void addMovement(Direction dir, int times);
	bool is_mq_empty();
	bool freeze;
	bool speedup;
	
	
};
