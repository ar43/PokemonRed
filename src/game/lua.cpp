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

	bool check_event(std::string eventName)
	{
		return game.checkEvent(eventName);
	}

	void set_event(std::string eventName, bool set)
	{
		game.setEvent(eventName, set);
	}

	void set_player_dir(int dir)
	{
		game.player.dir = (Direction)dir;
	}

	void text_auto_scroll(bool flag)
	{
		game.textbox.autoTextbox = flag;
	}

	void display_text(std::string textId, bool autoClose)
	{
		game.player.sprite->animIndex = 0;
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
}