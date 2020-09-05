#include "../sys/system.h"

Player::Player()
{
	pos.x = util::square_to_pixel(1);
	pos.y = util::square_to_pixel(2);
	dir = Direction::DOWN;
}

void Player::update()
{
	move();
}

void Player::getSquarePosition(Position *position)
{
	position->x = pos.x / 16;
	position->y = pos.y / 16;
}

void Player::getBlockPosition(Position* position)
{
	position->x = pos.x / 32;
	position->y = pos.y / 32;
}

Position *Player::getPosition()
{
	return &pos;
}

void Player::move()
{
	bool requestMove = true;
	Direction newDir;
	if (input.keyDown[ARROW_UP])
	{
		newDir = Direction::UP;
	}
	else if (input.keyDown[ARROW_DOWN])
	{
		newDir = Direction::DOWN;
	}
	else if (input.keyDown[ARROW_LEFT])
	{
		newDir = Direction::LEFT;
	}
	else if (input.keyDown[ARROW_RIGHT])
	{
		newDir = Direction::RIGHT;
	}
	else
	{
		requestMove = false;
	}

	if (turning)
	{
		turning++;
		if (turning == 4)
		{
			turning = 0;
			dir = turnDir;
		}
	}
	else if (moving)
	{
		if (game.debug.fastMode && moveIndex == 0)
		{
			switch (dir)
			{
				case Direction::UP:
				{
					pos.y -= 16;
					break;
				}
				case Direction::DOWN:
				{
					pos.y += 16;
					break;
				}
				case Direction::LEFT:
				{
					pos.x -= 16;
					break;
				}
				case Direction::RIGHT:
				{
					pos.x += 16;
					break;
				}
			}
			moveIndex = 18;
		}
		if (moveIndex % 2 == 1)
		{
			switch (dir)
			{
				case Direction::UP:
				{
					pos.y -= 2;
					break;
				}
				case Direction::DOWN:
				{
					pos.y += 2;
					break;
				}
				case Direction::LEFT:
				{
					pos.x -= 2;
					break;
				}
				case Direction::RIGHT:
				{
					pos.x += 2;
					break;
				}
			}
		}
		moveIndex++;
		if (moveIndex >= 16)
		{
			change_map();
			moving = false;
		}
	}
	else if (requestMove)
	{
		if (newDir != dir)
		{
			turning = 1;
			turnDir = newDir;
		}
		else
		{
			bool canMove = collision_check();
			if(canMove)
			{ 
				moving = true;
				moveIndex = 0;
			}
		}
	}
}

bool Player::collision_check()
{

	if (game.debug.noclip)
		return true;

	Position newpos = { pos.x,pos.y };
	switch (dir)
	{
		case Direction::UP:
		{
			newpos.y -= 16;
			break;
		}
		case Direction::DOWN:
		{
			newpos.y += 16;
			break;
		}
		case Direction::LEFT:
		{
			newpos.x -= 16;
			break;
		}
		case Direction::RIGHT:
		{
			newpos.x += 16;
			break;
		}
	}

	Map* currMap = game.world.currentMap;
	Position newpos_s = { newpos.x / 16,newpos.y / 16 };
	bool outOfBounds = false;
	Position newpos_ss = { newpos_s.x,newpos_s.y };
	Map* tempMap = nullptr;

	// out of bounds check
	if (newpos_s.x < 0)
	{
		if (currMap->connection.west == "none")
			return false;

		tempMap = res.getMap(currMap->connection.west);
		newpos_ss.y -= game.world.currentMap->connection.westOffset * 2;
		newpos_ss.x = tempMap->width * 2 - 1;
		outOfBounds = true;
	}
	else if (newpos_s.x >= game.world.currentMap->width * 2)
	{
		if (currMap->connection.east == "none")
			return false;

		tempMap = res.getMap(currMap->connection.east);
		newpos_ss.y -= game.world.currentMap->connection.eastOffset * 2;
		newpos_ss.x = 0;

		outOfBounds = true;
	}
	else if (newpos_s.y < 0)
	{
		if (currMap->connection.north == "none")
			return false;

		tempMap = res.getMap(currMap->connection.north);
		newpos_ss.x -= game.world.currentMap->connection.northOffset * 2;
		newpos_ss.y = tempMap->height * 2 - 1;

		outOfBounds = true;
	}
	else if (newpos_s.y >= game.world.currentMap->height * 2)
	{
		if(currMap->connection.south == "none")
			return false;

		tempMap = res.getMap(currMap->connection.south);
		newpos_ss.x -= game.world.currentMap->connection.southOffset * 2;
		newpos_ss.y = 0;

		outOfBounds = true;
	}
	

	if (outOfBounds)
	{
		newpos.y = newpos_ss.y * 16;
		newpos.x = newpos_ss.x * 16;
		currMap = tempMap;
	}
	//end of out of bounds

	//we are not out of bounds, check for current map
	int index = (newpos.y / 32) * currMap->width + newpos.x / 32;
	if (index < 0 || index >= currMap->blocks.size() || newpos.x < 0 || newpos.x >= currMap->width*32) //else it would throw error
		return true;

	Block* newBlock = &currMap->blockset->blocks[currMap->blocks[index]];

	int i = 0;
	if (newpos.x % 32 == 0)
	{
		if (newpos.y % 32 == 0)
			i = 0;
		else
			i = 2;
	}
	else
	{
		if (newpos.y % 32 == 0)
			i = 1;
		else
			i = 3;
	}

	//todo: ledge jumping (check "from" tile and "to" tile)



	if (!newBlock->solid[i][2]) //if the bottom left tile is solid, block movement, else dont
		return true;
	else
		return false;

	
}


void Player::change_map()
{
	Position newpos;
	getSquarePosition(&newpos);
	if (newpos.x < 0)
	{
		pos.y -= util::square_to_pixel(game.world.currentMap->connection.westOffset * 2);
		game.world.currentMap = res.getMap(game.world.currentMap->connection.west);
		pos.x = util::square_to_pixel(game.world.currentMap->width * 2 - 1);

	}
	else if (newpos.x >= game.world.currentMap->width * 2)
	{
		pos.y -= util::square_to_pixel(game.world.currentMap->connection.eastOffset * 2);
		game.world.currentMap = res.getMap(game.world.currentMap->connection.east);
		pos.x = util::square_to_pixel(0);
	}
	else if (newpos.y < 0)
	{
		pos.x -= util::square_to_pixel(game.world.currentMap->connection.northOffset * 2);
		game.world.currentMap = res.getMap(game.world.currentMap->connection.north);
		pos.y = util::square_to_pixel(game.world.currentMap->height * 2 - 1);
	}
	else if (newpos.y >= game.world.currentMap->height * 2)
	{
		pos.x -= util::square_to_pixel(game.world.currentMap->connection.southOffset * 2);
		game.world.currentMap = res.getMap(game.world.currentMap->connection.south);
		pos.y = util::square_to_pixel(0);
	}
}