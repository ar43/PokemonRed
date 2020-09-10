#pragma once
#include "enums.h"
class Text
{
public:
	char text[32];
	TextType type;
	Text* next = nullptr;
};


struct Textset
{
	std::string name = "error";
	Text* start = nullptr;
};

