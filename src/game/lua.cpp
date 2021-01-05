#include "../sys/system.h"

namespace lua
{
	lua_State* L = nullptr;

	void set_active(std::string HSid, bool flag)
	{
		Object* obj = res.getObject(HSid);
		obj->active = flag;
	}

	Position *get_player_pos()
	{
		return game.player.getPosition();
	}

	void print_error(int ret)
	{
		if (ret != 0)
		{
			printf("-- %s\n", lua_tostring(lua::L, -1));
			lua_pop(lua::L, 1); // remove error message
		}
	}

	void set_freeze(int i, bool flag)
	{
		if (i == 0)
		{
			game.player.freeze = flag;
		}
		else
		{
			i--;
			if (i < 0 || i >= (int)game.world.currentMap->objects.size())
			{
				printf("ERROR: set_freeze index out of range");
				return;
			}
			Npc* npc = (Npc*)game.world.currentMap->objects.at(i);
			npc->freeze = flag;
		}
	}

	int get_keycatchers()
	{
		return (int)input.keycatchers;
	}

	void speedup(int i, bool flag)
	{
		if (i == 0)
		{
		}
		else
		{
			i--;
			if (i < 0 || i >= (int)game.world.currentMap->objects.size())
			{
				printf("ERROR: speedup index out of range");
				return;
			}
			Npc* npc = (Npc*)game.world.currentMap->objects.at(i);
			npc->speedup = flag;
		}
	}

	void add_movement(int i, int dir, int times)
	{
		if (i == 0)
		{
			game.player.addMovement((Direction)dir, times);
		}
		else
		{
			i--;
			if (i < 0 || i >= (int)game.world.currentMap->objects.size())
			{
				printf("ERROR: add_movement index out of range");
				return;
			}
			Npc* npc = (Npc*)game.world.currentMap->objects.at(i);
			npc->addMovement((Direction)dir, times);
		}
	}

	bool check_event(std::string eventName)
	{
		return game.checkEvent(eventName);
	}

	void set_event(std::string eventName, bool set)
	{
		game.setEvent(eventName, set);
	}

	void set_object_dir(int i, int dir)
	{
		if (i == 0)
		{
			game.player.dir = (Direction)dir;
		}
		else
		{
			i--;
			if (i < 0 || i >= (int)game.world.currentMap->objects.size())
			{
				printf("ERROR: set_object_dir index out of range");
				return;
			}
			Npc* npc = (Npc*)game.world.currentMap->objects.at(i);
			npc->dir = (Direction)dir;
		}
	}

	bool is_mq_empty(int i)
	{
		if (i == 0)
		{
			return game.player.is_mq_empty();
		}
		else
		{
			i--;
			if (i < 0 || i >= (int)game.world.currentMap->objects.size())
			{
				printf("ERROR: is_mq_empty index out of range");
				return false;
			}
			Npc* npc = (Npc*)game.world.currentMap->objects.at(i);
			return npc->is_mq_empty() && npc->sprite->animIndex == 0;
		}
	}

	void text_auto_scroll(bool flag)
	{
		game.textbox.autoTextbox = flag;
	}

	void display_text(std::string textId, bool autoClose)
	{
		game.player.sprite->animIndex = 0;
		//for (auto it : game.world.currentMap->objects)
		//{
			//it->sprite->animIndex = 0;
		//}
		game.textbox.autoClose = autoClose;
		if (!game.textbox.show(textId))
			sys.error(util::va("Could not find text %s", textId.c_str()));
	}

	void close_text()
	{
		game.textbox.close();
	}

	void set_emote(int i, int emote)
	{
		if (i == 0)
		{
			game.player.set_emote((EmotionBubble)emote);
		}
		else
		{
			i--;
			if (i < 0 || i >= (int)game.world.currentMap->objects.size())
			{
				printf("ERROR: set_emote index out of range");
				return;
			}
			Npc *npc = (Npc*)game.world.currentMap->objects.at(i);
			npc->set_emote((EmotionBubble)emote);
		}
	}

	int get_emote_time(int i)
	{
		if (i == 0)
		{
			return game.player.get_emote_time();
		}
		else
		{
			Npc* npc = (Npc*)game.world.currentMap->objects.at(i);
			return npc->get_emote_time();
		}
	}

	void set_current_script(int id)
	{
		game.world.currentMap->currentScript = id;
	}
	
	int get_current_script()
	{
		return game.world.currentMap->currentScript;
	}

	void give_pokemon(std::string monName, int level)
	{
		game.player.inv.addPokemon(new Pokemon(res.getPokemonData(monName), level));
	}
}