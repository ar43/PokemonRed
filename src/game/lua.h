#pragma once

namespace lua
{
	extern void set_active(std::string HSid, bool flag);
	extern Position* get_player_pos();
	extern void print_error(int ret);
	extern lua_State* L;
	extern bool check_event(std::string eventName);
	extern void set_event(std::string eventName, bool set);
	extern void set_object_dir(int i, int dir);
	extern void display_text(std::string textId, bool autoClose);
	extern void close_text();
	extern int get_current_script();
	extern void set_current_script(int id);
	extern void text_auto_scroll(bool flag);
	extern void set_emote(int i, int emote);
	extern int get_emote_time(int i);
	extern void set_freeze(int i, bool flag);
	extern void add_movement(int i, int dir, int times);
	extern bool is_mq_empty(int i);
	extern int get_keycatchers();
	extern void speedup(int i, bool flag);
	extern void give_pokemon(std::string monName, int level);
}