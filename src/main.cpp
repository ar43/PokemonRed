#include "sys/system.h"

System sys;
Game game;
Input input;
Render rend;
ResourceManager res;

int main(int argc, char* args[])
{
	sys.init();
	sys.load_media();
	game.frame.init();
	game.init();

	SDL_version compiled;
	SDL_version linked;

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	SDL_Log("We compiled against SDL version %u.%u.%u ...\n",
		compiled.major, compiled.minor, compiled.patch);
	SDL_Log("But we are linking against SDL version %u.%u.%u.\n",
		linked.major, linked.minor, linked.patch);
	
	while (!sys.requestQuit)
	{
		game.frame.start();

		if(game.frame.capTimer.tick())
		{
			input.process(&input.e);

			game.prelogic();

			game.update();

			rend.render();

			game.frame.end_f();
			
		}

		game.frame.end();

	}

	sys.close();
	return 0;
}