#include "..\sys\system.h"

Item::Item()
{
	init();
}

void Item::update()
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
	else if (spriteDraw == false && sprite->is_on_screen(&loc))
	{
		spriteDraw = true;
	}

	if (spriteDraw)
	{
		//logic, movement etc
	}
}

void Item::render()
{
	if (!active)
		return;

	Position loc;
	get_world_pos(&loc);
	if (spriteDraw)
		sprite->render(&loc, Direction::DOWN);
}

void Item::init()
{

}