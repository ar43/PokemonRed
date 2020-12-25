#include "../sys/system.h"

Player::Player()
{
	pos.x = util::square_to_pixel(1);
	pos.y = util::square_to_pixel(2);
	dir = Direction::DOWN;
}

void Player::init()
{
	sprite = res.getSprite("red");
	lastMap = "pallet_town";
}

void Player::update()
{
	if (input.keycatchers == KEYCATCHERS_TEXTBOX)
	{
		if (game.debug.forceExitKeycatcher)
		{
			if (input.keyDown[KEY_B])
				input.keycatchers = KEYCATCHERS_NORMAL;
		}
		return;
	}

	if (warping)
		warpIndex++;

	move();

	if (warpIndex == 47 && warping)
		warp();

	if (input.block > 0)
		input.block--;
}

void Player::render()
{
	sprite->render_static(PLAYER_OFFSET_X, PLAYER_OFFSET_Y,dir);
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
	bool requestUse = false;
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
		if (!moving && !jumping)
			sprite->animIndex = 0;
	}

	if (input.keyDown[KEY_A] && canUse)
	{
		canUse = false;
		requestUse = true;
	}
	

	if (!input.keyDown[KEY_A] && !canUse)
		canUse = true;

	if (jumping)
	{
		sprite->animIndex++;
		if (jumpIndex % 2 == 1)
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
		jumpIndex++;
		if (jumpIndex >= 32)
		{
			jumping = false;
		}
	}
	else if (turning)
	{
		turning++;
		if (turning == 3)
		{
			turning = 0;
			dir = turnDir;
		}
	}
	else if (moving)
	{
		sprite->animIndex++;
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
			moving = false;
			change_map();
			warp_check(false);
			
		}
	}
	else if (requestUse)
	{
		if (game.textbox.canInput)
		{
			sign_check();
			object_check();
		}
	}
	else if (requestMove)
	{
		if (newDir != dir)
		{
			sprite->animIndex = 0;
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
			else
			{
				warp_check(true);
			}
			sprite->animIndex++;
		}
	}
	
}


void Player::sign_check()
{
	Map* currMap = game.world.currentMap;
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

	Position sq = { newpos.x / 16,newpos.y / 16 };
	for (std::vector<Sign>::iterator it = currMap->signs.begin(); it != currMap->signs.end(); ++it)
	{
		if (it->pos.x == sq.x && it->pos.y == sq.y)
		{
			input.clear();
			sprite->animIndex = 0;
			it->activate();
			return;
		}
	}

}

void Player::object_check()
{
	Map* currMap = game.world.currentMap;
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

	Position sq = { newpos.x / 16,newpos.y / 16 };
	Position sqo;

	for (auto it : game.world.currentMap->objects)
	{
		if(it->active && it->spriteDraw)
		{ 
			it->get_block_pos(&sqo);
			printf("sqo.x: %i, sqo.y: %i, sq.x: %i, sq.y: %i\n", sqo.x, sqo.y, sq.x, sq.y);
			if (sqo.x == sq.x && sqo.y == sq.y)
			{
				input.clear();
				sprite->animIndex = 0;
				it->activate();
				return;
			}
		}
	}

}

bool Player::collision_check()
{

	if (game.debug.noclip)
		return true;



	Map* currMap = game.world.currentMap;

	Block* currBlock = nullptr;
	int iOld;

	if (!util::get_block(&pos, currMap, currBlock, &iOld))
		return true;
	

	Position newpos = { pos.x,pos.y };
	Position screen_offset = { 0,0 };
	switch (dir)
	{
		case Direction::UP:
		{
			newpos.y -= 16;
			screen_offset.y -= 16;
			break;
		}
		case Direction::DOWN:
		{
			newpos.y += 16;
			screen_offset.y += 16;
			break;
		}
		case Direction::LEFT:
		{
			newpos.x -= 16;
			screen_offset.x -= 16;
			break;
		}
		case Direction::RIGHT:
		{
			newpos.x += 16;
			screen_offset.x += 16;
			break;
		}
	}

	for (auto it : game.world.currentMap->objects)
	{
		if(it->active && it->spriteDraw)
		{ 
			Position loc;
			it->get_screen_pos(&loc);
			SDL_Rect a = { loc.x,loc.y,16,16 };
			SDL_Rect b = { PLAYER_OFFSET_X+screen_offset.x,PLAYER_OFFSET_Y+ screen_offset.y,16,16 };
			if (SDL_HasIntersection(&a, &b))
				return false;
			/*
			Position loc;
			it->get_world_pos(&loc);
			Position offset;
			offset.x = loc.x % 16;
			offset.y = loc.y % 16;
			bool condition_a = newpos.x == loc.x - offset.x && newpos.y == loc.y - offset.y;
			bool condition_b = newpos.x == loc.x - offset.x + 16 && newpos.y == loc.y && offset.x != 0;
			bool condition_c = newpos.x == loc.x - offset.x && newpos.y == loc.y - offset.y+16 && offset.y != 0;
			if (condition_a || condition_b || condition_c)
				return false;
			*/
			//printf("name: %s , loc.x: %i, loc.y: %i, myloc.x: %i, myloc.y: %i\n", it->spriteName.c_str(), loc.x, loc.y,newpos.x,newpos.y);
		}
	}

	
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

	Block* newBlock = nullptr;
	int i = 0;
	if (!util::get_block(&newpos, currMap, newBlock, &i))
		return true;

	//ledge jumping (check "from" tile and "to" tile)
	if(currMap->blockset->name == "overworld")
		ledge_check(currBlock, newBlock,iOld,i);


	if (!newBlock->solid[i][2]) //if the bottom left tile is solid, block movement, else dont
		return true;
	else
		return false;

	
}

void Player::ledge_check(Block *currBlock,Block* newBlock, int iOld, int iNew)
{
	switch (dir)
	{
		case Direction::UP:
		{
			return;
		}
		case Direction::DOWN:
		{
			if (currBlock->tile[iOld] == 0x2C && newBlock->tile[iNew] == 0x37 || currBlock->tile[iOld] == 0x39 && newBlock->tile[iNew] == 0x36 || currBlock->tile[iOld] == 0x39 && newBlock->tile[iNew] == 0x37)
			{
				jumping = true;
				jumpIndex = 0;
			}
			break;
		}
		case Direction::RIGHT:
		{
			if (currBlock->tile[iOld] == 0x2C && newBlock->tile[iNew] == 0x0D || currBlock->tile[iOld] == 0x2C && newBlock->tile[iNew] == 0x1D || currBlock->tile[iOld] == 0x39 && newBlock->tile[iNew] == 0x0D)
			{
				jumping = true;
				jumpIndex = 0;
			}
			break;
		}
		case Direction::LEFT:
		{
			if (currBlock->tile[iOld] == 0x2C && newBlock->tile[iNew] == 0x27 || currBlock->tile[iOld] == 0x39 && newBlock->tile[iNew] == 0x27)
			{
				jumping = true;
				jumpIndex = 0;
			}
			break;
		}
	}
}


void Player::change_map()
{
	Position newpos;
	getSquarePosition(&newpos);
	bool changed = false;
	if (newpos.x < 0)
	{
		pos.y -= util::square_to_pixel(game.world.currentMap->connection.westOffset * 2);
		game.world.currentMap = res.getMap(game.world.currentMap->connection.west);
		pos.x = util::square_to_pixel(game.world.currentMap->width * 2 - 1);
		changed = true;
	}
	else if (newpos.x >= game.world.currentMap->width * 2)
	{
		pos.y -= util::square_to_pixel(game.world.currentMap->connection.eastOffset * 2);
		game.world.currentMap = res.getMap(game.world.currentMap->connection.east);
		pos.x = util::square_to_pixel(0);
		changed = true;
	}
	else if (newpos.y < 0)
	{
		pos.x -= util::square_to_pixel(game.world.currentMap->connection.northOffset * 2);
		game.world.currentMap = res.getMap(game.world.currentMap->connection.north);
		pos.y = util::square_to_pixel(game.world.currentMap->height * 2 - 1);
		changed = true;
	}
	else if (newpos.y >= game.world.currentMap->height * 2)
	{
		pos.x -= util::square_to_pixel(game.world.currentMap->connection.southOffset * 2);
		game.world.currentMap = res.getMap(game.world.currentMap->connection.south);
		pos.y = util::square_to_pixel(0);
		changed = true;
	}

	if (changed)
		game.world.on_map_change();
}

void Player::warp_check(bool carpet)
{
	if (warping)
		return;
	Map* currMap = game.world.currentMap;
	Position newpos = { pos.x,pos.y };

	Block* newBlock = nullptr;

	int i;

	if (!util::get_block(&newpos, currMap, newBlock, &i))
		return;

	bool check;
	//bool check_carpet = (newBlock->warp_up[i] && dir == Direction::UP || newBlock->warp_down[i] && dir == Direction::DOWN || newBlock->warp_left[i] && dir == Direction::LEFT || newBlock->warp_right[i] && dir == Direction::RIGHT);
	bool check_carpet = !newBlock->warp[i];
	bool check_normal = newBlock->warp[i];
	if (carpet)
		check = check_carpet;
	else
		check = check_normal;

	if (check)
	{
		Position sq;
		getSquarePosition(&sq);
		for (std::vector<Warp>::iterator it = currMap->warps.begin(); it != currMap->warps.end(); ++it)
		{
			if (it->at.x == sq.x && it->at.y == sq.y)
			{
				nextWarp = &(*it);
				block_input(64);
				warpIndex = 0;
				warping = true;
				return;
			}
		}

	}
}

void Player::block_input(int time)
{
	input.block = time;
	input.clear();
}

void Player::warp()
{
	if (game.world.currentMap->tileset->permission == Permission::OUTDOOR) //is current map outdoors?
	{
		lastMap = game.world.currentMap->name;
	}

	if (nextWarp->to == "last_map")
		game.world.currentMap = res.getMap(lastMap);
	else
		game.world.currentMap = res.getMap(nextWarp->to);

	if (game.world.currentMap == nullptr)
	{ 
		sys.error("Unimplemented warp.");
		return;
	}

	pos.x = util::square_to_pixel(game.world.currentMap->warps[nextWarp->warpIn].at.x);
	pos.y = util::square_to_pixel(game.world.currentMap->warps[nextWarp->warpIn].at.y);
	if (game.world.currentMap->tileset->permission == Permission::OUTDOOR) //is next map outdoors?
	{
		moving = true;
		moveIndex = 0;
		sprite->animIndex = 0;
	}
	warpIndex = 0;
	warping = false;
	game.world.on_map_change();
}