#pragma once
#define MAX_CONSOLE_TEXT 100
#define NUM_CONSOLE_LINES 18

#include "cmds.h"

struct Cursor
{
	void render();
	double lastBlink;
	double blinkTime;
	bool show;
	Timer blink;
};

struct ConsoleLine
{
	ConsoleLine(char *pText);
	ConsoleLine(char *pText, bool input);
	//Text draw_text;
	char text[MAX_CONSOLE_TEXT];
};

class Console
{
public:
	void init();
	void open();
	void close();
	std::vector<std::unique_ptr<ConsoleLine>> lines;

	std::vector<char*> history;
	Uint32 historypointer;

	char buffer[MAX_CONSOLE_TEXT];
	void render();
	void addLine(char *text);
	void addLine(char *text, bool input);
	void QDECL print(const char *fmt, ...);

	void renderText();

	void handleInput(SDL_Event* e);
	
	Cursor cursor;
	Uint32 lineCount;
	Uint32 scrollIndex;

	

	Cmds cmds;

private:
	bool queueUpdate;
	Texture bufferTex;
	Texture arrow;
	
};