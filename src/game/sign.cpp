#include "../sys/system.h"

void Sign::activate()
{
	std::string textStr = game.world.currentMap->fileName + "Text" + std::to_string(textID);
	printf("Activating text id: %i\nString: %s\n", textID, textStr.c_str());
	bool found = false;
	for (std::vector<Textset>::iterator it2 = game.world.currentMap->texts.begin(); it2 != game.world.currentMap->texts.end(); ++it2)
	{
		if (SDL_strcmp(textStr.c_str(), it2->name.c_str()) == 0)
		{
			found = true;
			game.textbox.currText = it2->start;
			game.textbox.index = 0;
			game.textbox.cleared = false;
			break;
		}
	}
	if (found)
		input.keycatchers = KEYCATCHERS_TEXTBOX;
	else
		sys.error(util::va("Could not find text %s", textStr.c_str()));
}