#pragma once
#include <vector>
#include <string>

class Evolution
{
public:
	std::string type;
	int level;
	std::string item;
	std::string to;
	int itemCount;
};

class EvolutionSet
{
public:
	std::vector<Evolution*> evolutionList;
};