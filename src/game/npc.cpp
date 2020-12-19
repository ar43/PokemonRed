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
	Position loc;
	get_world_pos(&loc);
	sprite->render(&loc, Direction::DOWN);
}

void Npc::get_world_pos(Position* pnt)
{
	pnt->x = pos.x * 16 + GAME_WIDTH / 2 - game.player.getPosition()->x - WORLD_OFFSET_X;
	pnt->y = pos.y * 16 + GAME_WIDTH / 2 - game.player.getPosition()->y - WORLD_OFFSET_X;
}