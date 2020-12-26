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
}