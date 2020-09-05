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