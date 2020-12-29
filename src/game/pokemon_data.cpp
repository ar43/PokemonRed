#include "../sys/system.h"

std::string PokemonData::getId()
{
	return dexId.substr(4, std::string::npos);
}
