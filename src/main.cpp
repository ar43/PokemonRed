#include "sys/system.h"

System sys;
Game game;
Input input;
Render rend;

int main(int argc, char* args[])
{
	sys.init();
	game.frame.init();
	//sys.loadMedia();



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