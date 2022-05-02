#include "../sys/system.h"

void Sign::activate()
{
	std::string textStr = game.world.currentMap->fileName + "Text" + std::to_string(textID);
	printf("Activating text id: %i\nString: %s\n", textID, textStr.c_str());
	game.textbox.show(textStr);
}