#pragma once
#include "../sys/frame.h"
#include "player.h"
#include "world.h"
#include "textbox.h"

struct Debug
{
	bool drawPlayer = false;
	bool drawSquare = false;
	bool drawColl = false;
	bool fastMode = false;
	bool noclip = false;
	bool darken = false;
	bool forceExitKeycatcher = true;
	bool showAllObjects = false;
};

class Game
{
public:
	Game();
	void update();
	void prelogic();
	void init();
	void setEvent(std::string eventName, bool set);
	bool checkEvent(std::string eventName);
	void runDebugScript();
	bool canRunScript;
	//Camera camera;
	Frame frame;
	Player player;
	World world;
	Debug debug;
	Textbox textbox;
	//Action action;
private:
	std::map<std::string, bool> eventMap;
};