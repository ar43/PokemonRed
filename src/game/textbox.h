#pragma once
#include "text.h"
class Textbox
{
public:
	void render();
	void update();
	Text *currText;
	char line[2][32];
	bool refresh = true;
	Texture lineText[2];
};