#include "..\sys\system.h"

Trainer::Trainer()
{
	//init();
	moving = false;
	moveIndex = 0;
	
}


void Trainer::update()
{
	Npc::update();
	
}

void Trainer::render()
{
	Npc::render();
}

void Trainer::init()
{
	Npc::init();
	if (movMode == NpcMovementMode::WALK)
		printf("WARNING: Trainer %s walks\n", trainerClass.c_str());
}

void Trainer::activate()
{

}

void Trainer::get_screen_pos(Position* pnt)
{
	Npc::get_screen_pos(pnt);
}

void Trainer::get_block_pos(Position* pos)
{
	Npc::get_block_pos(pos);
}

void Trainer::get_world_pos(Position* pos)
{
	Npc::get_world_pos(pos);
}