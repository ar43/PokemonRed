#pragma once

namespace lua
{
	extern void set_active(std::string HSid, bool flag);
	extern Position* get_player_pos();
	extern void print_error(int ret);
	extern lua_State* L;
}