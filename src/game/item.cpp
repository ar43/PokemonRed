#include "..\sys\system.h"

Item::Item()
{
	//init();
}

void Item::update()
{
	if (!active)
		return;

	Position loc;
	get_screen_pos(&loc);

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
	get_screen_pos(&loc);
	if (spriteDraw)
		sprite->render(&loc, Direction::DOWN);
}

void Item::init()
{

}

void Item::get_screen_pos(Position* pnt)
{
	pnt->x = pos.x * 16 + GAME_WIDTH / 2 - game.player.getPosition()->x - WORLD_OFFSET_X;
	pnt->y = pos.y * 16 + GAME_HEIGHT / 2 - game.player.getPosition()->y - 12;
}

void Item::get_block_pos(Position* pos)
{
	pos->x = this->pos.x;
	pos->y = this->pos.y;
}

void Item::get_world_pos(Position* pos)
{
	pos->x = this->pos.x * 16;
	pos->y = this->pos.y * 16;
}

void Item::activate()
{

}