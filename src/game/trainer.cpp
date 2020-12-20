#include "..\sys\system.h"

Trainer::Trainer()
{
	init();
}


void Trainer::update()
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
	else if (sprite->draw == false && sprite->is_on_screen(&loc))
	{
		sprite->draw = true;
	}

	if (sprite->draw)
	{
		//logic, movement etc
	}
}

void Trainer::render()
{
	if (!active)
		return;

	Position loc;
	get_world_pos(&loc);
	sprite->render(&loc, Direction::DOWN);
}

void Trainer::init()
{
	waiting = true;
	displacement.x = 0;
	displacement.y = 0;
}