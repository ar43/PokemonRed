#pragma once

namespace util
{
	extern char	*QDECL va(const char *format, ...);

	extern char *cleanStr(char *string);

	extern int square_to_pixel(int a);

	extern void remove_spaces(char* s);

	extern void to_lower(char* s);

	extern int random(int min, int max);

	extern bool get_block(Position* p_pos, Map* currMap, Block*& block, int* i);

	extern bool file_exists(const std::string& Filename);

	extern void clearStats(PokemonStats* stats);

	extern int ipow(int base, int exp);
}

