#include "../sys/system.h"

Player::Player()
{
	x = 16;
	y = 12;
	dir = Direction::DOWN;
}

void Player::update()
{
	move();
}

void Player::move()
{
	bool action = true;
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
		action = false;
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
		if (moveIndex % 2 == 1)
		{
			switch (dir)
			{
				case Direction::UP:
				{
					y -= 2;
					break;
				}
				case Direction::DOWN:
				{
					y += 2;
					break;
				}
				case Direction::LEFT:
				{
					x -= 2;
					break;
				}
				case Direction::RIGHT:
				{
					x += 2;
					break;
				}
			}
		}
		moveIndex++;
		if (moveIndex == 16)
			moving = false;
	}
	else if (action)
	{
		if (newDir != dir)
		{
			turning = 1;
			turnDir = newDir;
		}
		else
		{
			moving = true;
			moveIndex = 0;
		}
	}
}