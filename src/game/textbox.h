#pragma once
#include "text.h"
class Textbox
{
public:
	Textbox();
	void render();
	void update();
	bool show(std::string idString, bool doClear = true);
	Text *currText;
	char line[2][32];
	std::string filteredText;
	size_t index;
	bool canInput;
	bool cleared;
	Texture lineText[2];
	bool autoTextbox;
	void close();
	void clear();
	
	bool autoClose;
private:
	
	void begin(Textset *it, bool doClear);

	void updateRenderer(int num);
	void update_text(int num);

	int animIndex;
	bool scrollAnim;

	bool activated;
	bool drawArrow;

	int curLine = 0;
	

	void transition();
	void render_arrow();
	void render_anim();
	int delay;
};