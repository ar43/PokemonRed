#pragma once
#include "text.h"
class Textbox
{
public:
	Textbox();
	void render();
	void update();
	bool show(std::string idString);
	Text *currText;
	char line[2][32];
	size_t index;
	bool canInput;
	bool cleared;
	Texture lineText[2];
	bool autoTextbox;
	void close();
	
	bool autoClose;
private:
	void clear();
	void updateRenderer(int num);
	void update_text(int num);

	int animIndex;
	bool scrollAnim;

	bool activated;
	bool drawArrow;
	

	void transition();
	void render_arrow();
	void render_anim();
	int delay;
};