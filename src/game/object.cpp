#include "..\sys\system.h"
 
Object::Object()
{
	active = true;
	spriteDraw = false;
}

void Object::movDir_to_dir()
{
	switch (movDir)
	{
		case NpcMovementDir::UP:
		{
			dir = Direction::UP;
			break;
		}
		case NpcMovementDir::LEFT:
		{
			dir = Direction::LEFT;
			break;
		}
		case NpcMovementDir::RIGHT:
		{
			dir = Direction::RIGHT;
			break;
		}
		case NpcMovementDir::LEFT_RIGHT:
		{
			dir = Direction::RIGHT;
			break;
		}
		default:
		{
			dir = Direction::DOWN;
			break;
		}
	}
}