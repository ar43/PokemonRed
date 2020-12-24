#include "..\sys\system.h"

Trainer::Trainer()
{
	//init();
	displacement.x = 0;
	displacement.y = 0;
}


void Trainer::update()
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

void Trainer::render()
{
	if (!active)
		return;

	Position loc;
	get_screen_pos(&loc);
	if (spriteDraw)
		sprite->render(&loc, dir);
}

void Trainer::init()
{
	waiting = true;
	displacement.x = 0;
	displacement.y = 0;
	movDir_to_dir();
}

void Trainer::get_screen_pos(Position* pnt)
{
	pnt->x = pos.x * 16 + displacement.x + GAME_WIDTH / 2 - game.player.getPosition()->x - WORLD_OFFSET_X;
	pnt->y = pos.y * 16 + displacement.y + GAME_WIDTH / 2 - game.player.getPosition()->y - WORLD_OFFSET_Y - 12;
}

void Trainer::get_block_pos(Position* pos)
{
	pos->x = this->pos.x + displacement.x / 16;
	pos->y = this->pos.y + displacement.y / 16;
}

void Trainer::get_world_pos(Position* pos)
{
	pos->x = this->pos.x * 16 + displacement.x;
	pos->y = this->pos.y * 16 + displacement.y;
}