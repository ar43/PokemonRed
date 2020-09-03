#pragma once
#include <vector>
#undef QDECL
#define	QDECL	__cdecl



namespace util
{
	extern char	*QDECL va(const char *format, ...);

	extern char *cleanStr(char *string);
}

