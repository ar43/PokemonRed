#include "system.h"

System::System()
{
	
	requestQuit = false;
	window = NULL;
	renderer = NULL;
}

void System::init()
{

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		sys.error(util::va("SDL could not initialize! SDL Error: %s\n", SDL_GetError()));
	}
	else
	{
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

		//Create window
		sys.window = SDL_CreateWindow("Pokemon", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, GAME_WIDTH*4, GAME_HEIGHT*4, SDL_WINDOW_SHOWN);
		if (sys.window == NULL)
		{
			sys.error(util::va("Window could not be created! SDL Error: %s\n", SDL_GetError()));
		}
		else
		{
			//Create renderer for window
			sys.renderer = SDL_CreateRenderer(sys.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (sys.renderer == NULL)
			{
				sys.error(util::va("Renderer could not be created! SDL Error: %s\n", SDL_GetError()));
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(sys.renderer, 0xFF, 0xFF, 0xFF, 0xFF);


				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					sys.error(util::va("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError()));
				}
				SDL_RenderSetScale(sys.renderer, 4, 4);
			}
			//Init Sound
			if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
			{
				sys.error("Sound error");
			}
			//init Font
			if (TTF_Init() == -1)
			{
				sys.error("Font error");
			}
		}
	}

}

void System::error(const char* pMsg)
{
	char		msg[4096];
	strncpy(msg, pMsg, sizeof(msg));
	SDL_strlcat(msg, "\nGame will exit.", sizeof(msg));
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
		"Fatal ERROR",
		msg,
		NULL);
	printf("(FATAL ERROR): %s\n", msg);
	sys.requestQuit = true;
}

SDL_Window* System::getWindow()
{
	return sys.window;
}

SDL_Renderer* System::getRenderer()
{
	return sys.renderer;
}

void System::close()
{
	//Destroy window	
	SDL_DestroyRenderer(sys.renderer);
	SDL_DestroyWindow(sys.window);
	sys.window = NULL;
	sys.renderer = NULL;

	//Quit SDL subsystems
	Mix_CloseAudio();
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

void System::load_media()
{
	res.loadTileset("overworld", "assets/tilesets/overworld.png");

	res.loadBlockset("overworld", "assets/blocksets/overworld.bst");

	res.loadMap("pallet_town", "assets/maps/PalletTown.blk", "overworld", 9, 10);
}
