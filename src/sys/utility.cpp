#include "system.h"
#include <cassert>

#ifdef _WIN32
#include <io.h> 
#define access    _access_s
#else
#include <unistd.h>
#endif

namespace util
{

	char	* QDECL va(const char *format, ...)
	{
		va_list		argptr;
		static char		string[2][32000];	// in case va is called by nested functions
		static int		index = 0;
		char	*buf;

		buf = string[index & 1];
		index++;

		va_start(argptr, format);
		vsprintf(buf, format, argptr);
		va_end(argptr);

		return buf;
	}
	

	char *cleanStr(char *string)
	{
		char*	d = string;
		char*	s = string;
		int		c;

		while ((c = *s) != 0) {
			if (c >= 0x20 && c <= 0x7E) {
				*d++ = c;
			}
			s++;
		}
		*d = '\0';

		return string;
	}

	bool is_numeric(const char *str) 
	{
		while(*str != '\0')
		{
			if(*str < '0' || *str > '9')
				return false;
			str++;
		}
		return true;
	}

	int square_to_pixel(int a)
	{
		return a * 16;
	}

	void remove_spaces(char* s) {
		const char* d = s;
		do {
			while (*d == ' ' || *d == '\t') {
				++d;
			}
		} while (*s++ = *d++);
	}

	void to_lower(char* s)
	{
		for (size_t i = 0; s[i]; i++)
		{
			s[i] = (char)tolower((int)s[i]);
		}
	}

	int random(int min, int max)
	{
		assert("min < max");
		int n = max - min;
		int ret = (rand() % (n + 1)) + min;
		assert("ret >= min && ret <= max");
		return ret;
	}

	bool get_block(Position* p_pos, Map* currMap, Block*& block, int* i)
	{

		//we are not out of bounds, check for current map
		size_t index = (p_pos->y / 32) * currMap->width + p_pos->x / 32;
		if (index < 0 || index >= currMap->blocks.size() || p_pos->x < 0 || p_pos->x >= currMap->width * 32) //else it would throw error
			return false;

		block = &currMap->blockset()->blocks[currMap->blocks[index]];

		if (p_pos->x % 32 == 0)
		{
			if (p_pos->y % 32 == 0)
				*i = 0;
			else
				*i = 2;
		}
		else
		{
			if (p_pos->y % 32 == 0)
				*i = 1;
			else
				*i = 3;
		}
		return true;
	}

	bool file_exists(const std::string& Filename)
	{
		return access(Filename.c_str(), 0) == 0;
	}

	bool is_special(const std::string& type_name)
	{
		return std::find(Constants::Pokemon::special.begin(), Constants::Pokemon::special.end(), type_name) != Constants::Pokemon::special.end();
	}

	bool is_physical(const std::string& type_name)
	{
		return std::find(Constants::Pokemon::physical.begin(), Constants::Pokemon::physical.end(), type_name) != Constants::Pokemon::physical.end();
	}

	void clearStats(PokemonStats* stats)
	{
		stats->attack = 0;
		stats->hp = 0;
		stats->defense = 0;
		stats->special = 0;
		stats->speed = 0;
	}

	int ipow(int base, int exp)
	{
		assert(base >= 0 && exp >= 0);
		int result = 1;
		for (;;)
		{
			if (exp & 1)
				result *= base;
			exp >>= 1;
			if (!exp)
				break;
			base *= base;
		}

		return result;
	}

	void error(const char* pMsg)
	{
		sys.error(pMsg);
	}
	
}