#include "..\sys\system.h"

void Object::get_world_pos(Position* pnt)
{
	pnt->x = pos.x * 16 + GAME_WIDTH / 2 - game.player.getPosition()->x - WORLD_OFFSET_X;
	pnt->y = pos.y * 16 + GAME_WIDTH / 2 - game.player.getPosition()->y - WORLD_OFFSET_Y - 12;
}
 
Object::Object()
{
	active = true;
	spriteDraw = false;
}