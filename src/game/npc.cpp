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
		sprite->draw = false;
	}
	else if(sprite->draw == false && sprite->is_on_screen(&loc))
	{
		sprite->draw = true;
	}

	if (sprite->draw)
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
	sprite->render(&loc, Direction::DOWN);
}