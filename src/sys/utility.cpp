#include "system.h"

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

	int square_to_pixel(int a)
	{
		return a * 16;
	}

	void remove_spaces(char* s) {
		const char* d = s;
		do {
			while (*d == ' ') {
				++d;
			}
		} while (*s++ = *d++);
	}
	
}