#pragma once

#include "../sys/render.h"
#include "map.h"
#include "enums.h"

#define PLAYER_OFFSET_X 64
#define PLAYER_OFFSET_Y 60

#define WORLD_OFFSET_X 16
#define WORLD_OFFSET_Y 8

class Player 
{
public:
	Player();
	void getSquarePosition(Position *position);
	void getBlockPosition(Position* position);
	Position* getPosition();
	Sprite* sprite;
	void update();
	void init();
	void render();
	void warp();
	void set_emote(EmotionBubble index);
	int get_emote_time();
	void block_input(int time);
	int warpIndex;
	bool jumping;
	int jumpIndex;
	bool moving;
	int moveIndex;
	Direction dir;
	bool freeze;
	void addMovement(Direction dir, int times);
	bool is_mq_empty();
	std::string name;
	int trainerId;
private:
	
	Position pos;
	Direction turnDir;
	int turning;
	int emoteTime;
	EmotionBubble emote;
	std::queue<Direction> movementQueue;
	bool forcedMovement;

	bool warping;
	void move();
	void change_map();
	void warp_check(bool carpet);
	void ledge_check(Block* currBlock, Block* newBlock, int iOld, int iNew);
	bool collision_check();
	std::string lastMap;
	Warp* nextWarp;
	bool canUse;
	//bool get_block(Position* p_pos, Map* currMap, Block*& block, int* i);
	void sign_check();
	void object_check();
};