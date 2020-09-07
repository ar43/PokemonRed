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
	close();
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
	//exit(0);
}

void System::load_media()
{
	/*
	tileset Overworld_Block,   Overworld_GFX,   Overworld_Coll,   $FF,$FF,$FF, $52, OUTDOOR
	tileset RedsHouse1_Block,  RedsHouse1_GFX,  RedsHouse1_Coll,  $FF,$FF,$FF, $FF, INDOOR
	tileset Mart_Block,        Mart_GFX,        Mart_Coll,        $18,$19,$1E, $FF, INDOOR
	tileset Forest_Block,      Forest_GFX,      Forest_Coll,      $FF,$FF,$FF, $20, CAVE
	tileset RedsHouse2_Block,  RedsHouse2_GFX,  RedsHouse2_Coll,  $FF,$FF,$FF, $FF, INDOOR
	tileset Dojo_Block,        Dojo_GFX,        Dojo_Coll,        $3A,$FF,$FF, $FF, OUTDOOR
	tileset Pokecenter_Block,  Pokecenter_GFX,  Pokecenter_Coll,  $18,$19,$1E, $FF, INDOOR
	tileset Gym_Block,         Gym_GFX,         Gym_Coll,         $3A,$FF,$FF, $FF, OUTDOOR
	tileset House_Block,       House_GFX,       House_Coll,       $FF,$FF,$FF, $FF, INDOOR
	tileset ForestGate_Block,  ForestGate_GFX,  ForestGate_Coll,  $17,$32,$FF, $FF, INDOOR
	tileset Museum_Block,      Museum_GFX,      Museum_Coll,      $17,$32,$FF, $FF, INDOOR
	tileset Underground_Block, Underground_GFX, Underground_Coll, $FF,$FF,$FF, $FF, INDOOR
	tileset Gate_Block,        Gate_GFX,        Gate_Coll,        $17,$32,$FF, $FF, INDOOR
	tileset Ship_Block,        Ship_GFX,        Ship_Coll,        $FF,$FF,$FF, $FF, CAVE
	tileset ShipPort_Block,    ShipPort_GFX,    ShipPort_Coll,    $FF,$FF,$FF, $FF, CAVE
	tileset Cemetery_Block,    Cemetery_GFX,    Cemetery_Coll,    $12,$FF,$FF, $FF, INDOOR
	tileset Interior_Block,    Interior_GFX,    Interior_Coll,    $FF,$FF,$FF, $FF, INDOOR
	tileset Cavern_Block,      Cavern_GFX,      Cavern_Coll,      $FF,$FF,$FF, $FF, CAVE
	tileset Lobby_Block,       Lobby_GFX,       Lobby_Coll,       $15,$36,$FF, $FF, INDOOR
	tileset Mansion_Block,     Mansion_GFX,     Mansion_Coll,     $FF,$FF,$FF, $FF, INDOOR
	tileset Lab_Block,         Lab_GFX,         Lab_Coll,         $FF,$FF,$FF, $FF, INDOOR
	tileset Club_Block,        Club_GFX,        Club_Coll,        $07,$17,$FF, $FF, INDOOR
	tileset Facility_Block,    Facility_GFX,    Facility_Coll,    $12,$FF,$FF, $FF, CAVE
	tileset Plateau_Block,     Plateau_GFX,     Plateau_Coll,     $FF,$FF,$FF, $45, CAVE
*/
	res.loadTileset("overworld", "assets/gfx/tilesets/overworld.png",&Constants::Coll::overworld, &Constants::Warp::overworld, 0xFF,0xFF,0xFF,0x52,OUTDOOR);
	res.loadTileset("reds_house", "assets/gfx/tilesets/reds_house.png", &Constants::Coll::reds_house, &Constants::Warp::reds_house, 0xFF, 0xFF, 0xFF, 0xFF, INDOOR);

	res.loadBlockset("overworld", "overworld", "assets/data/blocksets/overworld.bst");
	res.loadBlockset("reds_house", "reds_house", "assets/data/blocksets/reds_house.bst");

	res.loadMap("pallet_town", "PalletTown", "overworld", 0xb,"route_1",0,"none",0,"none",0,"route_21",0);
	res.loadMap("viridian_city", "ViridianCity", "overworld", 0xf, "route_2",5, "route_22",4, "none",0, "route_1",5);
	res.loadMap("route_1", "Route1", "overworld", 0xb, "viridian_city",-5, "none",0, "none",0, "pallet_town",0);
	res.loadMap("route_21", "Route21", "overworld", 0x43, "pallet_town",0, "none",0, "none",0, "cinnabar_island",0);
	res.loadMap("route_22", "Route22", "overworld", 0x2c, "route_23", 0, "none", 0, "viridian_city", -4, "none", 0);
	res.loadMap("reds_house_1f", "RedsHouse1F", "reds_house", 0xa, "none", 0, "none", 0, "none", 0, "none", 0);

	res.loadTexture("flower1", "assets/gfx/tilesets/flower/flower1.png");
	res.loadTexture("flower2", "assets/gfx/tilesets/flower/flower2.png");
	res.loadTexture("flower3", "assets/gfx/tilesets/flower/flower3.png");

	res.loadTexture("water0", "assets/gfx/tilesets/water/water0.png");
	res.loadTexture("water1", "assets/gfx/tilesets/water/water1.png");
	res.loadTexture("water2", "assets/gfx/tilesets/water/water2.png");
	res.loadTexture("water3", "assets/gfx/tilesets/water/water3.png");
	res.loadTexture("water4", "assets/gfx/tilesets/water/water4.png");

	res.loadTexture("grass1", "assets/gfx/tilesets/grass/grass.png",true);

	res.loadSprite("red", "assets/gfx/sprites/red.png");
}
