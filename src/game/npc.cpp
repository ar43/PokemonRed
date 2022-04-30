#include "../sys/system.h"


Npc::Npc()
{
	//init();
	moving = false;
	moveIndex = 0;
	emoteTime = 0;
	freeze = false;
	speedup = false;
}

void Npc::activate()
{
	if (!moving)
	{
		switch (game.player.dir)
		{
			case Direction::DOWN:
			{
				dir = Direction::UP;
				break;
			}
			case Direction::LEFT:
			{
				dir = Direction::RIGHT;
				break;
			}
			case Direction::UP:
			{
				dir = Direction::DOWN;
				break;
			}
			case Direction::RIGHT:
			{
				dir = Direction::LEFT;
				break;
			}
		}
		std::string textStr = game.world.currentMap->fileName + "Text" + std::to_string(textID);
		printf("Activating text id: %i\nString: %s\n", textID, textStr.c_str());
		if (!game.textbox.show(textStr))
		{ 
			printf("ERROR:Could not find text %s\n", textStr.c_str());
			return;
		}
	}
}


void Npc::init()
{
	waitIndex = 1;
	displacement.x = 0;
	displacement.y = 0;
	
	movDir_to_dir();
	//printf("init called\n");
}

void Npc::get_block_pos(Position* pos)
{
	pos->x = this->pos.x + displacement.x / 16;
	pos->y = this->pos.y + displacement.y / 16;
}

void Npc::get_world_pos(Position* pos)
{
	pos->x = this->pos.x * 16 + displacement.x;
	pos->y = this->pos.y * 16 + displacement.y;
}

void Npc::addMovement(Direction dir, int times)
{
	for (int i = 0; i < times; i++)
	{
		movementQueue.push(dir);
	}
}


void Npc::update()
{
	if (emoteTime)
		emoteTime--;

	if (!active || input.keycatchers == KEYCATCHERS_TEXTBOX)
		return;

	Position loc;
	get_screen_pos(&loc);

	//system to mimic game's sprite rendering system.
	if (!sprite->is_on_screen_strict(&loc))
	{ 
		spriteDraw = false;
	}
	else if(spriteDraw == false && sprite->is_on_screen(&loc))
	{
		spriteDraw = true;
	}

	if (spriteDraw)
	{	 
		if (moving)
		{
			if (speedup)
			{
				if (moveIndex % 2 == game.player.moveIndex % 2 && !game.player.is_mq_empty())
				{
					return;
				}
			}
			move();
		}
		else
		{
			sprite->animIndex = 0;
		}

		if (!movementQueue.empty() && !moving)
		{
			static Direction lastdir = Direction::DOWN;
			
			dir = movementQueue.front();
				
			moving = true;
			moveIndex = 0;
			sprite->animIndex = 0;
			
			wait(); //just in case to avoid catastrophe
			lastdir = dir;
		}
		else if (waitIndex == 0 && !freeze)
		{
			generateDir();
			if (collision_check() && movMode == NpcMovementMode::WALK)
			{ 
				moving = true;
				moveIndex = 0;
				sprite->animIndex = 0;
			}
			wait();
		}
		

		if (!moving && waitIndex > 0 && game.frame.getFrame() % 2 == 1)
			waitIndex--;
	}
}

bool Npc::collision_check()
{
	Map* currMap = game.world.currentMap;

	Block* currBlock = nullptr;
	int iOld;
	Position newpos = { pos.x * 16 + displacement.x,pos.y * 16 + displacement.y };

	if (!util::get_block(&newpos, currMap, currBlock, &iOld))
		return true;


	
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

	Position loc;
	get_screen_pos(&loc,&newpos);
	if (!sprite->is_on_screen_strict(&loc)) // block walk if npc will no longer be on screen
		return false;

	//applying npc movement clauses found in glitchcity
	//this will cause the movement to be glitched https://archives.glitchcity.info/wiki/NPC_walking_behavior_glitches.html
	//maybe add a setting to fix this?
	if (dir == Direction::UP && displacement.y / 16 == 8)
		return false;

	if (dir != Direction::UP && (displacement.y / 16 >= 5))
		return false;

	if (dir == Direction::LEFT && (displacement.x / 16 == 8))
		return false;

	//is player there?

	SDL_Rect a = {loc.x,loc.y,16,16};
	SDL_Rect b = { PLAYER_OFFSET_X,PLAYER_OFFSET_Y,16,16 };

	if (SDL_HasIntersection(&a,&b))
		return false;


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
		if (currMap->connection.south == "none")
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

	if (!newBlock->solid[i][2]) //if the bottom left tile is solid, block movement, else dont
		return true;
	else
		return false;
}

void Npc::wait()
{
	waitIndex = util::random(0, 127);
	if (waitIndex == 0)
		waitIndex = 256;
}

void Npc::generateDir()
{
	switch (movDir)
	{
		case NpcMovementDir::NONE:
		case NpcMovementDir::ANY_DIR:
		{
			dir = (Direction)util::random(0, 3);
			break;
		}
		case NpcMovementDir::UP_DOWN:
		{
			dir = (Direction)util::random(0, 1);
			break;
		}
		case NpcMovementDir::LEFT_RIGHT:
		{
			dir = (Direction)util::random(2, 3);
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
		case NpcMovementDir::UP:
		{
			dir = Direction::UP;
			break;
		}
		case NpcMovementDir::DOWN:
		{
			dir = Direction::DOWN;
			break;
		}
		default:
		{
			sys.error(util::va("generateDir with NpcMovementDir: %i", (int)movDir));
			return;
		}
	}
}

void Npc::move()
{
	int step = 1;
	int maxframe = 32;
	if (speedup)
	{
		step = 2;
		maxframe = 16;
	}
	sprite->animIndex++;
	if (moveIndex % 2 == 1)
	{
		switch (dir)
		{
		case Direction::UP:
		{
			displacement.y -= step;
			break;
		}
		case Direction::DOWN:
		{
			displacement.y += step;
			break;
		}
		case Direction::LEFT:
		{
			displacement.x -= step;
			break;
		}
		case Direction::RIGHT:
		{
			displacement.x += step;
			break;
		}
		}
	}
	moveIndex++;
	if (moveIndex >= maxframe)
	{
		moving = false;
		if(!movementQueue.empty())
			movementQueue.pop();
	}
}

bool Npc::is_mq_empty()
{
	return movementQueue.empty();
}

void Npc::get_screen_pos(Position* pnt)
{
	pnt->x = pos.x * 16 + displacement.x + GAME_WIDTH / 2 - game.player.getPosition()->x - WORLD_OFFSET_X;
	pnt->y = pos.y * 16 + displacement.y + GAME_HEIGHT / 2 - game.player.getPosition()->y - 12;
}

void Npc::get_screen_pos(Position* pnt,Position *custompos)
{
	pnt->x = custompos->x + GAME_WIDTH / 2 - game.player.getPosition()->x - WORLD_OFFSET_X;
	pnt->y = custompos->y + GAME_HEIGHT / 2 - game.player.getPosition()->y - 12;
}

void Npc::render()
{
	if (!active || !spriteDraw)
		return;

	Position loc;
	get_screen_pos(&loc);
	sprite->render(&loc, dir,speedup);
	//printf("drew npc at: %i %i; player pos: %i %i; displacement: %i %i; \n", loc.x, loc.y,game.player.getPosition()->x,game.player.getPosition()->y, displacement.x, displacement.y);

	if (emoteTime)
	{
		switch (emote)
		{
			case EmotionBubble::HAPPY:
			{
				res.getTexture("happy")->render(loc.x, loc.y - 16);
				break;
			}
			case EmotionBubble::QUESTION:
			{
				res.getTexture("question")->render(loc.x, loc.y - 16);
				break;
			}
			case EmotionBubble::SHOCK:
			{
				res.getTexture("shock")->render(loc.x, loc.y - 16);
				break;
			}
		}
	}
}

void Npc::set_emote(EmotionBubble index)
{
	emote = index;
	emoteTime = 60;
}

int Npc::get_emote_time()
{
	return emoteTime;
}