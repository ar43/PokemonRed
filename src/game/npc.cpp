#include "../sys/system.h"


Npc::Npc()
{
	init();
}


void Npc::init()
{
	waiting = true;
	displacement.x = 0;
	displacement.y = 0;
}


void Npc::update()
{
	if (!active)
		return;

	Position loc;
	get_world_pos(&loc);

	//system to mimic game's sprite rendering system.
	if (!sprite->is_on_screen_strict(&loc))
	{ 
		spriteDraw = false;
	}
	else if(spriteDraw == false && sprite->is_on_screen(&loc))
	{
		spriteDraw = true;
	}

	if (spriteDraw)
	{
		//logic, movement etc
	}
}

void Npc::render()
{
	if (!active)
		return;

	Position loc;
	get_world_pos(&loc);
	if(spriteDraw)
		sprite->render(&loc, Direction::DOWN);
}