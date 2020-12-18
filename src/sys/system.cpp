#include "system.h"
#include "dirent.h"

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

#ifdef _DEBUG
	__asm
	{
		int 3
	}
#endif

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

void System::load_sprites()
{
	//todo
}

void System::load_maps()
{
	printf("Loading maps...\n");
	DIR* dir;
	struct dirent* ent;
	if ((dir = opendir(".\\assets\\data\\map_headers\\")) != NULL) {
		/* print all the files and directories within directory */
		while ((ent = readdir(dir)) != NULL) {
			char name[261];
			SDL_strlcpy(name, ent->d_name, 261);
			if (name[0] == '.')
				continue;
			for (size_t i = 0; i < strlen(name); i++)
			{
				if (name[i] == '.')
				{
					name[i] = 0;
					break;
				}
			}
			//printf("%s\n", name);
			res.loadMap(name);
		}
		closedir(dir);
	}
	else {
		/* could not open directory */
		perror("");
		return;
	}
}

void System::load_tilesets()
{
	/*
	tileset Overworld_Block,   Overworld_GFX,   Overworld_Coll,   0xFF,0xFF,0xFF, 0x52, OUTDOOR
	tileset RedsHouse1_Block,  RedsHouse1_GFX,  RedsHouse1_Coll,  0xFF,0xFF,0xFF, 0xFF, INDOOR
	tileset Mart_Block,        Mart_GFX,        Mart_Coll,        0x18,0x19,0x1E, 0xFF, INDOOR
	tileset Forest_Block,      Forest_GFX,      Forest_Coll,      0xFF,0xFF,0xFF, 0x20, CAVE
	tileset RedsHouse2_Block,  RedsHouse2_GFX,  RedsHouse2_Coll,  0xFF,0xFF,0xFF, 0xFF, INDOOR
	tileset Dojo_Block,        Dojo_GFX,        Dojo_Coll,        0x3A,0xFF,0xFF, 0xFF, OUTDOOR
	tileset Pokecenter_Block,  Pokecenter_GFX,  Pokecenter_Coll,  0x18,0x19,0x1E, 0xFF, INDOOR
	tileset Gym_Block,         Gym_GFX,         Gym_Coll,         0x3A,0xFF,0xFF, 0xFF, OUTDOOR
	tileset House_Block,       House_GFX,       House_Coll,       0xFF,0xFF,0xFF, 0xFF, INDOOR
	tileset ForestGate_Block,  ForestGate_GFX,  ForestGate_Coll,  0x17,0x32,0xFF, 0xFF, INDOOR
	tileset Museum_Block,      Museum_GFX,      Museum_Coll,      0x17,0x32,0xFF, 0xFF, INDOOR
	tileset Underground_Block, Underground_GFX, Underground_Coll, 0xFF,0xFF,0xFF, 0xFF, INDOOR
	tileset Gate_Block,        Gate_GFX,        Gate_Coll,        0x17,0x32,0xFF, 0xFF, INDOOR
	tileset Ship_Block,        Ship_GFX,        Ship_Coll,        0xFF,0xFF,0xFF, 0xFF, CAVE
	tileset ShipPort_Block,    ShipPort_GFX,    ShipPort_Coll,    0xFF,0xFF,0xFF, 0xFF, CAVE
	tileset Cemetery_Block,    Cemetery_GFX,    Cemetery_Coll,    0x12,0xFF,0xFF, 0xFF, INDOOR
	tileset Interior_Block,    Interior_GFX,    Interior_Coll,    0xFF,0xFF,0xFF, 0xFF, INDOOR
	tileset Cavern_Block,      Cavern_GFX,      Cavern_Coll,      0xFF,0xFF,0xFF, 0xFF, CAVE
	tileset Lobby_Block,       Lobby_GFX,       Lobby_Coll,       0x15,0x36,0xFF, 0xFF, INDOOR
	tileset Mansion_Block,     Mansion_GFX,     Mansion_Coll,     0xFF,0xFF,0xFF, 0xFF, INDOOR
	tileset Lab_Block,         Lab_GFX,         Lab_Coll,         0xFF,0xFF,0xFF, 0xFF, INDOOR
	tileset Club_Block,        Club_GFX,        Club_Coll,        0x07,0x17,0xFF, 0xFF, INDOOR
	tileset Facility_Block,    Facility_GFX,    Facility_Coll,    0x12,0xFF,0xFF, 0xFF, CAVE
	tileset Plateau_Block,     Plateau_GFX,     Plateau_Coll,     0xFF,0xFF,0xFF, 0x45, CAVE
*/
	printf("Loading tilesets\n");
	res.loadTileset("overworld", "assets/gfx/tilesets/overworld.png", &Constants::Coll::overworld, &Constants::Warp::overworld, 0xFF, 0xFF, 0xFF, 0x52, Permission::OUTDOOR);
	res.loadTileset("reds_house", "assets/gfx/tilesets/reds_house.png", &Constants::Coll::redshouse, &Constants::Warp::reds_house, 0xFF, 0xFF, 0xFF, 0xFF, Permission::INDOOR);
	res.loadTileset("mart", "assets/gfx/tilesets/pokecenter.png", &Constants::Coll::mart, &Constants::Warp::mart, 0x18, 0x19, 0x1E, 0xFF, Permission::INDOOR);
	res.loadTileset("forest", "assets/gfx/tilesets/forest.png", &Constants::Coll::forest, &Constants::Warp::forest, 0xFF, 0xFF, 0xFF, 0x20, Permission::CAVE);
	res.loadTileset("dojo", "assets/gfx/tilesets/gym.png", &Constants::Coll::dojo, &Constants::Warp::dojo, 0x3A, 0xFF, 0xFF, 0xFF, Permission::INDOOR);//ORIGINAL: OUTDOOR why????
	res.loadTileset("pokecenter", "assets/gfx/tilesets/pokecenter.png", &Constants::Coll::pokecenter, &Constants::Warp::pokecenter, 0x18, 0x19, 0x1E, 0xFF, Permission::INDOOR);
	res.loadTileset("gym", "assets/gfx/tilesets/gym.png", &Constants::Coll::gym, &Constants::Warp::gym, 0x3A, 0xFF, 0xFF, 0xFF, Permission::INDOOR); //ORIGINAL: OUTDOOR why????
	res.loadTileset("house", "assets/gfx/tilesets/house.png", &Constants::Coll::house, &Constants::Warp::house, 0xFF, 0xFF, 0xFF, 0xFF, Permission::INDOOR);
	res.loadTileset("forestgate", "assets/gfx/tilesets/gate.png", &Constants::Coll::forestgate, &Constants::Warp::forestgate, 0x17, 0x32, 0xFF, 0xFF, Permission::INDOOR);
	res.loadTileset("museum", "assets/gfx/tilesets/gate.png", &Constants::Coll::museum, &Constants::Warp::museum, 0x17, 0x32, 0xFF, 0xFF, Permission::INDOOR);
	res.loadTileset("underground", "assets/gfx/tilesets/underground.png", &Constants::Coll::underground, &Constants::Warp::underground, 0xFF, 0xFF, 0xFF, 0xFF, Permission::INDOOR);
	res.loadTileset("gate", "assets/gfx/tilesets/gate.png", &Constants::Coll::gate, &Constants::Warp::gate, 0x17, 0x32, 0xFF, 0xFF, Permission::INDOOR);
	res.loadTileset("ship", "assets/gfx/tilesets/ship.png", &Constants::Coll::ship, &Constants::Warp::ship, 0xFF, 0xFF, 0xFF, 0xFF, Permission::CAVE);
	res.loadTileset("shipport", "assets/gfx/tilesets/ship_port.png", &Constants::Coll::shipport, &Constants::Warp::shipport, 0xFF, 0xFF, 0xFF, 0xFF, Permission::CAVE);
	res.loadTileset("cemetery", "assets/gfx/tilesets/cemetery.png", &Constants::Coll::cemetery, &Constants::Warp::cemetery, 0x12, 0xFF, 0xFF, 0xFF, Permission::INDOOR);
	res.loadTileset("interior", "assets/gfx/tilesets/interior.png", &Constants::Coll::interior, &Constants::Warp::interior, 0xFF, 0xFF, 0xFF, 0xFF, Permission::INDOOR);
	res.loadTileset("cavern", "assets/gfx/tilesets/cavern.png", &Constants::Coll::cavern, &Constants::Warp::cavern, 0xFF, 0xFF, 0xFF, 0xFF, Permission::CAVE);
	res.loadTileset("lobby", "assets/gfx/tilesets/lobby.png", &Constants::Coll::lobby, &Constants::Warp::lobby, 0x15, 0x36, 0xFF, 0xFF, Permission::INDOOR);
	res.loadTileset("mansion", "assets/gfx/tilesets/mansion.png", &Constants::Coll::mansion, &Constants::Warp::mansion, 0xFF, 0xFF, 0xFF, 0xFF, Permission::INDOOR);
	res.loadTileset("lab", "assets/gfx/tilesets/lab.png", &Constants::Coll::lab, &Constants::Warp::lab, 0xFF, 0xFF, 0xFF, 0xFF, Permission::INDOOR);
	res.loadTileset("club", "assets/gfx/tilesets/club.png", &Constants::Coll::club, &Constants::Warp::club, 0x07, 0x17, 0xFF, 0xFF, Permission::INDOOR);
	res.loadTileset("facility", "assets/gfx/tilesets/facility.png", &Constants::Coll::facility, &Constants::Warp::facility, 0x12, 0xFF, 0xFF, 0xFF, Permission::CAVE);
	res.loadTileset("plateau", "assets/gfx/tilesets/plateau.png", &Constants::Coll::plateau, &Constants::Warp::plateau, 0xFF, 0xFF, 0xFF, 0x45, Permission::CAVE);
}

void System::load_blocksets()
{
	printf("Loading blocksets\n");
	res.loadBlockset("overworld", "overworld", "assets/data/blocksets/overworld.bst");
	res.loadBlockset("reds_house_1", "reds_house", "assets/data/blocksets/reds_house.bst");
	res.loadBlockset("reds_house_2", "reds_house", "assets/data/blocksets/reds_house.bst");
	res.loadBlockset("mart", "mart", "assets/data/blocksets/pokecenter.bst");
	res.loadBlockset("forest", "forest", "assets/data/blocksets/forest.bst");
	res.loadBlockset("dojo", "dojo", "assets/data/blocksets/gym.bst");
	res.loadBlockset("pokecenter", "pokecenter", "assets/data/blocksets/pokecenter.bst");
	res.loadBlockset("gym", "gym", "assets/data/blocksets/gym.bst");
	res.loadBlockset("house", "house", "assets/data/blocksets/house.bst");
	res.loadBlockset("forest_gate", "forestgate", "assets/data/blocksets/gate.bst");
	res.loadBlockset("museum", "museum", "assets/data/blocksets/gate.bst");
	res.loadBlockset("underground", "underground", "assets/data/blocksets/underground.bst");
	res.loadBlockset("gate", "gate", "assets/data/blocksets/gate.bst");
	res.loadBlockset("ship", "ship", "assets/data/blocksets/ship.bst");
	res.loadBlockset("ship_port", "shipport", "assets/data/blocksets/ship_port.bst");
	res.loadBlockset("cemetery", "cemetery", "assets/data/blocksets/cemetery.bst");
	res.loadBlockset("interior", "interior", "assets/data/blocksets/interior.bst");
	res.loadBlockset("cavern", "cavern", "assets/data/blocksets/cavern.bst");
	res.loadBlockset("lobby", "lobby", "assets/data/blocksets/lobby.bst");
	res.loadBlockset("mansion", "mansion", "assets/data/blocksets/mansion.bst");
	res.loadBlockset("lab", "lab", "assets/data/blocksets/lab.bst");
	res.loadBlockset("club", "club", "assets/data/blocksets/club.bst");
	res.loadBlockset("facility", "facility", "assets/data/blocksets/facility.bst");
	res.loadBlockset("plateau", "plateau", "assets/data/blocksets/plateau.bst");
}

void System::load_media()
{
	
	load_tilesets();
	load_blocksets();
	load_maps();

	res.loadTexture("flower1", "assets/gfx/tilesets/flower/flower1.png");
	res.loadTexture("flower2", "assets/gfx/tilesets/flower/flower2.png");
	res.loadTexture("flower3", "assets/gfx/tilesets/flower/flower3.png");

	res.loadTexture("water0", "assets/gfx/tilesets/water/water0.png");
	res.loadTexture("water1", "assets/gfx/tilesets/water/water1.png");
	res.loadTexture("water2", "assets/gfx/tilesets/water/water2.png");
	res.loadTexture("water3", "assets/gfx/tilesets/water/water3.png");
	res.loadTexture("water4", "assets/gfx/tilesets/water/water4.png");

	res.loadTexture("grass1", "assets/gfx/tilesets/grass/grass.png",true);
	res.loadTexture("shadow", "assets/gfx/overworld/shadow.png", true);

	res.loadTexture("tb1", "assets/gfx/font/textbox/tb1.png");
	res.loadTexture("tb2", "assets/gfx/font/textbox/tb2.png");
	res.loadTexture("tb3", "assets/gfx/font/textbox/tb3.png");
	res.loadTexture("tb4", "assets/gfx/font/textbox/tb4.png");
	res.loadTexture("tb5", "assets/gfx/font/textbox/tb5.png");
	res.loadTexture("tb6", "assets/gfx/font/textbox/tb6.png");
	res.loadTexture("tinput", "assets/gfx/font/textbox/input.png");

	res.loadSprite("red", "assets/gfx/sprites/red.png");
	load_sprites();
	Constants::font = TTF_OpenFont("assets/gfx/font/pokemon-final.otf", 8);
}
