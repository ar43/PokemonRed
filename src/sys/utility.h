#pragma once
#include <vector>
#undef QDECL
#define	QDECL	__cdecl



namespace util
{
	extern char	*QDECL va(const char *format, ...);

	extern char *cleanStr(char *string);

	extern int square_to_pixel(int a);

	extern void remove_spaces(char* s);
}

