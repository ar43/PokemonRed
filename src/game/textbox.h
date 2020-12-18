#pragma once
#include "text.h"
class Textbox
{
public:
	void render();
	void update();
	Text *currText;
	char line[2][32];
	int index;
	bool cleared;
	Texture lineText[2];
private:
	void clear();
	void updateRenderer(int num);
};