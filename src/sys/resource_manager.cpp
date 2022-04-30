#include "system.h"
#include <iostream>
#include <fstream>
#include <algorithm>

void ResourceManager::loadTileset(std::string textureName, const char *path, std::vector<Uint8>* collData, std::vector<Uint8>* warpData, Uint8 counterTile1, Uint8 counterTile2, Uint8 counterTile3, Uint8 grassTile, Permission permission)
{
	SDL_Surface *sur = IMG_Load(path);

	//0x00 0x55 0xaa 0xff

	if (!sur) {
		sys.error(util::va("IMG_Load: %s\n", IMG_GetError()));
		// handle error
	}
	SDL_Surface* gsSurface = SDL_ConvertSurfaceFormat(sur,
		SDL_PIXELFORMAT_ARGB8888,
		0);

	Tileset *tileset = new Tileset();
	tileset->surface = gsSurface;
	//darken:
	//for (int i = 0; i < gsSurface->w*gsSurface->h; i++)
	//{
	//	Uint32* pixels = (Uint32*)gsSurface->pixels;
	//	pixels[i] -= 0x555555;
	//
	//	if (pixels[i] < 0xff000000)
	//		pixels[i] = 0xff000000;
	//	//printf("%x: %x\n", i, pixels[i]);
	//}

	tileset->format = gsSurface->format->format;
	tileset->collData = collData;
	tileset->warpData = warpData;
	tileset->w = gsSurface->w;
	tileset->h = gsSurface->h;
	tileset->counterTiles[0] = counterTile1;
	tileset->counterTiles[1] = counterTile2;
	tileset->counterTiles[2] = counterTile3;
	tileset->grassTile = grassTile;
	if (grassTile != 0xFF) //TODO: grass for every type of grass
	{
		tileset->grassName = "grass1";
	}
	tileset->permission = permission;

	tileset->texture = SDL_CreateTextureFromSurface(sys.getRenderer(), tileset->surface);
	
	tilesetMap[textureName] = tileset;
	SDL_FreeSurface(sur);
}

void ResourceManager::setObject(std::string name, Object* pointer)
{
	if (!(objectMap.find(name) == objectMap.end()))
	{ 
		sys.error("setObject: object is already in the map");
	}
	else
	{
		objectMap[name] = pointer;
	}
}

Object* ResourceManager::getObject(std::string name)
{
	if (!(objectMap.find(name) == objectMap.end()))
	{
		return objectMap[name];
	}
	else
	{
		sys.error(util::va("can not find object in the object map: %s", name.c_str()));
		return nullptr;
	}
}

void ResourceManager::addTextRedefinition(std::string in, std::string out)
{
	if (!(textRedefinitionMap.find(in) == textRedefinitionMap.end()))
	{
		printf("Something went wrong in redefinitions file\n");
		return;
	}
	else
	{
		textRedefinitionMap[in] = out;
	}
}

std::string ResourceManager::getTextRedefinition(std::string in)
{
	if (!(textRedefinitionMap.find(in) == textRedefinitionMap.end()))
	{
		return textRedefinitionMap[in];
	}
	else
	{
		return in;
	}
}

void ResourceManager::loadTexture(std::string textureName, std::string path, bool transparent)
{
	loadTexture(textureName, path.c_str(), transparent);
}

void ResourceManager::loadTexture(std::string textureName, const char* path, bool transparent)
{
	SDL_Surface* sur = IMG_Load(path);

	if (!sur) {
		sys.error(util::va("IMG_Load: %s\n", IMG_GetError()));
		// handle error
	}
	SDL_Surface* gsSurface;
	if(!transparent)
	{ 
		gsSurface = SDL_ConvertSurfaceFormat(sur,SDL_PIXELFORMAT_ARGB8888,0);
	}
	else
	{
		gsSurface = sur;
		SDL_SetColorKey(gsSurface, SDL_TRUE, SDL_MapRGB(gsSurface->format, 0xff, 0xff, 0xff));
	}
	Texture* texture = new Texture();
	texture->surface = gsSurface;
	texture->format = gsSurface->format->format;
	texture->w = gsSurface->w;
	texture->h = gsSurface->h;

	texture->texture = SDL_CreateTextureFromSurface(sys.getRenderer(), texture->surface);

	textureMap[textureName] = texture;

	gsSurface = SDL_ConvertSurfaceFormat(sur,SDL_PIXELFORMAT_ARGB8888,0);
	//lighten by one level:
	for (int i = 0; i < gsSurface->w*gsSurface->h; i++)
	{
		Uint32* pixels = (Uint32*)gsSurface->pixels;
		if (pixels[i] > 0xff000000)
			pixels[i] += 0x555555;

		//printf("%x: %x\n", i, pixels[i]);
	}
	SDL_SetColorKey(gsSurface, SDL_TRUE, SDL_MapRGB(gsSurface->format, 0xff, 0xff, 0xff));

	Texture* textureLight = new Texture();
	textureLight->surface = gsSurface;
	textureLight->format = gsSurface->format->format;
	textureLight->w = gsSurface->w;
	textureLight->h = gsSurface->h;

	textureLight->texture = SDL_CreateTextureFromSurface(sys.getRenderer(), textureLight->surface);

	textureMap[textureName + "Light"] = textureLight;

	SDL_FreeSurface(sur);
}

void ResourceManager::loadSprite(std::string spriteName)
{
	std::string path = "./assets/gfx/sprites/" + spriteName + ".png";
	SDL_Surface* sur = IMG_Load(path.c_str());

	if (!sur) {
		printf("Failed to load sprite \"%s\"\n", spriteName.c_str());
		return;
		// handle error
	}
	//SDL_Surface* gsSurface = SDL_ConvertSurfaceFormat(sur,SDL_PIXELFORMAT_ARGB8888,0);
	SDL_Surface* gsSurface = SDL_ConvertSurfaceFormat(sur,
		SDL_PIXELFORMAT_ARGB8888,
		0);
	

	
	//lighten by one level:
	for (int i = 0; i < gsSurface->w*gsSurface->h; i++)
	{
		Uint32* pixels = (Uint32*)gsSurface->pixels;
		if (pixels[i] > 0xff000000)
			pixels[i] += 0x555555;

		//printf("%x: %x\n", i, pixels[i]);
	}
	SDL_SetColorKey(gsSurface, SDL_TRUE, SDL_MapRGB(gsSurface->format, 0xff, 0xff, 0xff));
	Sprite* sprite = new Sprite();
	sprite->surface = gsSurface;
	sprite->format = gsSurface->format->format;
	sprite->w = gsSurface->w;
	sprite->h = gsSurface->h;
	sprite->size = sprite->h / 16;
	sprite->animIndex = 0;

	sprite->texture = SDL_CreateTextureFromSurface(sys.getRenderer(), sprite->surface);
	spriteMap[spriteName] = sprite;
	SDL_FreeSurface(sur);
}

void ResourceManager::loadBlockset(std::string blocksetName, std::string tilesetName, const char* path)
{
	Blockset* blockset = new Blockset();
	blockset->blocks = new Block[MAX_BLOCKS]();
	Tileset* tileset = getTileset(tilesetName);
	blockset->name = blocksetName;
	blockset->tileset = tileset;

	int i = 0;

	std::ifstream ifs(path, std::ifstream::in | std::ifstream::binary);

	while(!ifs.eof())
	{ 
		char buffer[16];
		ifs.read(buffer, 16);
		blockset->blocks[i].texture = SDL_CreateTexture(sys.getRenderer(), tileset->format, SDL_TEXTUREACCESS_TARGET, 32, 32);
		if (!blockset->blocks[i].texture)
		{
			sys.error(util::va("SDL_CreateTexture failed: %s\n", SDL_GetError()));
			break;
		}
		SDL_SetRenderTarget(sys.getRenderer(), blockset->blocks[i].texture);
		SDL_RenderClear(sys.getRenderer());
		for (int j = 0; j < 16; j++)
		{
			SDL_Rect src = { ((Uint8)buffer[j] % 16) * 8,((Uint8)buffer[j] / 16) * 8,8,8 };
			SDL_Rect dest = { (j % 4) * 8,(j / 4) * 8,8,8 };
			SDL_RenderCopy(sys.getRenderer(), tileset->texture, &src, &dest);
			if (std::find(tileset->collData->begin(), tileset->collData->end(), buffer[j]) != tileset->collData->end())
			{
				switch(j)
				{
					case 0:
						blockset->blocks[i].solid[0][0] = false;
						break;
					case 1:
						blockset->blocks[i].solid[0][1] = false;
						break;
					case 2:
						blockset->blocks[i].solid[1][0] = false;
						break;
					case 3:
						blockset->blocks[i].solid[1][1] = false;
						break;
					case 4:
						blockset->blocks[i].solid[0][2] = false;
						break;
					case 5:
						blockset->blocks[i].solid[0][3] = false;
						break;
					case 6:
						blockset->blocks[i].solid[1][2] = false;
						break;
					case 7:
						blockset->blocks[i].solid[1][3] = false;
						break;
					case 8:
						blockset->blocks[i].solid[2][0] = false;
						break;
					case 9:
						blockset->blocks[i].solid[2][1] = false;
						break;
					case 10:
						blockset->blocks[i].solid[3][0] = false;
						break;
					case 11:
						blockset->blocks[i].solid[3][1] = false;
						break;
					case 12:
						blockset->blocks[i].solid[2][2] = false;
						break;
					case 13:
						blockset->blocks[i].solid[2][3] = false;
						break;
					case 14:
						blockset->blocks[i].solid[3][2] = false;
						break;
					case 15:
						blockset->blocks[i].solid[3][3] = false;
						break;
				}
				
			}
			//for warp
			if (std::find(tileset->warpData->begin(), tileset->warpData->end(), buffer[j]) != tileset->warpData->end())
			{
				switch (j)
				{
				case 4:
					blockset->blocks[i].warp[0] = true;
					break;
				case 6:
					blockset->blocks[i].warp[1] = true;
					break;
				case 0xC:
					blockset->blocks[i].warp[2] = true;
					break;
				case 0xE:
					blockset->blocks[i].warp[3] = true;
					break;
				}

			}
			//for ledges
			switch (j)
			{
			case 4:
				blockset->blocks[i].tile[0] = buffer[j];
				break;
			case 6:
				blockset->blocks[i].tile[1] = buffer[j];
				break;
			case 0xC:
				blockset->blocks[i].tile[2] = buffer[j];
				break;
			case 0xE:
				blockset->blocks[i].tile[3] = buffer[j];
				break;
			}
			//for carpet warp (is 0 2 8 A actually correct? assuming Red's House, but needs testing)
			if(tileset->permission == Permission::INDOOR)
			{ 
				if (std::find(Constants::Warp::up.begin(), Constants::Warp::up.end(), buffer[j]) != Constants::Warp::up.end())
				{
					switch (j)
					{
					case 0:
						blockset->blocks[i].warp_up[0] = true;
						break;
					case 2:
						blockset->blocks[i].warp_up[1] = true;
						break;
					case 8:
						blockset->blocks[i].warp_up[2] = true;
						break;
					case 0xA:
						blockset->blocks[i].warp_up[3] = true;
						break;
					}

				}
				if (std::find(Constants::Warp::down.begin(), Constants::Warp::down.end(), buffer[j]) != Constants::Warp::down.end())
				{
					switch (j)
					{
					case 0:
						blockset->blocks[i].warp_down[0] = true;
						break;
					case 2:
						blockset->blocks[i].warp_down[1] = true;
						break;
					case 8:
						blockset->blocks[i].warp_down[2] = true;
						break;
					case 0xA:
						blockset->blocks[i].warp_down[3] = true;
						break;
					}

				}
				if (std::find(Constants::Warp::left.begin(), Constants::Warp::left.end(), buffer[j]) != Constants::Warp::left.end())
				{
					switch (j)
					{
					case 0:
						blockset->blocks[i].warp_left[0] = true;
						break;
					case 2:
						blockset->blocks[i].warp_left[1] = true;
						break;
					case 8:
						blockset->blocks[i].warp_left[2] = true;
						break;
					case 0xA:
						blockset->blocks[i].warp_left[3] = true;
						break;
					}

				}
				if (std::find(Constants::Warp::right.begin(), Constants::Warp::right.end(), buffer[j]) != Constants::Warp::right.end())
				{
					switch (j)
					{
					case 0:
						blockset->blocks[i].warp_right[0] = true;
						break;
					case 2:
						blockset->blocks[i].warp_right[1] = true;
						break;
					case 8:
						blockset->blocks[i].warp_right[2] = true;
						break;
					case 0xA:
						blockset->blocks[i].warp_right[3] = true;
						break;
					}

				}
			}

			//for animation
			if (blocksetName == "overworld")
			{
				if (buffer[j] == 0x03)
					blockset->blocks[i].animation[j] = ANIMATION_FLOWER;
				else if (buffer[j] == 0x14)
					blockset->blocks[i].animation[j] = ANIMATION_WATER;
			}
			if (buffer[j] == tileset->grassTile)
			{ 
				blockset->blocks[i].grassTile[j] = true;
			}

		}
		SDL_SetRenderTarget(sys.getRenderer(), NULL);
		blockset->blocks[i].valid = true;
		i++;
	}
	ifs.close();

	blocksetMap[blocksetName] = blockset;
}

PokemonData* ResourceManager::getPokemonData(std::string pokemonName)
{
	if (!(pokemonDataMap.find(pokemonName) == pokemonDataMap.end()))
	{
		return pokemonDataMap[pokemonName];
	}
	else
	{
		sys.error(util::va("can not find pokemonData in the storage: %s", pokemonName.c_str()));
		return nullptr;
	}
}

void ResourceManager::loadPokemonData(std::string pokemonName)
{
	std::string path = "assets/data/pokemon/base_stats/" + pokemonName + ".asm";
	PokemonData *data = new PokemonData();

	bool tmhm = false;
	char string[1024];

	FILE* fp = fopen(path.c_str(), "r");
	if (!fp)
		sys.error("Cant find the pokemon data file");
	int l = 0;
	while (fgets(string, 1024, fp)) {
		if (l == 0) //DEX entry name
		{
			char* substring = SDL_strstr(string, "db ");
			if (substring)
			{
				substring += 3;
				for (auto i = 0; substring[i]; i++)
				{
					if(substring[i] == ' ')
					{ 
						substring[i] = 0;
						break;
					}
				}
				data->dexId = std::string(substring);
			}
			else
			{
				sys.error("pkm data: error at line 1");
			}
		}
		else if (l == 2) //pokemon stats
		{
			char* substring = SDL_strstr(string, "db ");
			if (substring)
			{
				substring += 3;
				char* token;
				token = strtok(substring, ",");
				int i = 0;
				/* walk through other tokens */
				while (token != NULL) 
				{
					int num = atoi(token);
					if (i == 0)
					{
						data->baseStats.hp = num;
					}
					else if (i == 1)
					{
						data->baseStats.attack = num;
					}
					else if(i == 2)
					{
						data->baseStats.defense = num;
					}
					else if (i == 3)
					{
						data->baseStats.speed = num;
					}
					else if (i == 4)
					{
						data->baseStats.special = num;
					}
					token = strtok(NULL, ",");
					i++;
				}
				
			}
			else
			{
				sys.error("pkm data: error at line 3");
			}
		}
		else if (l == 5) //pokemon type
		{
			char* substring = SDL_strstr(string, "db ");
			if (substring)
			{
				substring += 3;
				char* token;
				token = strtok(substring, ",");
				int i = 0;
				/* walk through other tokens */
				while (token != NULL) 
				{
					util::remove_spaces(token);
					for (auto j = 0; token[j]; j++)
					{
						if (token[j] == ';')
						{
							token[j] = 0;
							break;
						}
					}

					if (i <= 1)
					{
						data->type[i] = token;
						
					}
					token = strtok(NULL, ",");
					i++;
				}

			}
			else
			{
				sys.error("pkm data: error at line 6");
			}
		}
		else if (l == 6) //catchrate
		{
			char* substring = SDL_strstr(string, "db ");
			if (substring)
			{
				substring += 3;
				for (auto i = 0; substring[i]; i++)
				{
					if (substring[i] == ' ')
					{
						substring[i] = 0;
						break;
					}
				}
				data->catchRate = atoi(substring);
			}
			else
			{
				sys.error("pkm data: error at line 7");
			}
		}
		else if (l == 7) //basexp
		{
			char* substring = SDL_strstr(string, "db ");
			if (substring)
			{
				substring += 3;
				for (auto i = 0; substring[i]; i++)
				{
					if (substring[i] == ' ')
					{
						substring[i] = 0;
						break;
					}
				}
				data->baseEXP = atoi(substring);
			}
			else
			{
				sys.error("pkm data: error at line 8");
			}
		}
		else if (l == 12) //pokemon learnset
		{
			char* substring = SDL_strstr(string, "db ");
			if (substring)
			{
				substring += 3;
				char* token;
				token = strtok(substring, ",");
				int i = 0;
				/* walk through other tokens */
				while (token != NULL) 
				{
					if (i <= 3)
					{
						util::remove_spaces(token);
						for (auto j = 0; token[j]; j++)
						{
							if (token[j] == ';')
							{
								token[j] = 0;
								break;
							}
						}
						data->baseLearnset[i] = token;
						
					}
					token = strtok(NULL, ",");
					i++;
				}

			}
			else
			{
				sys.error("pkm data: error at line 13");
			}
		}
		if (l == 13) //catchrate
		{
			char* substring = SDL_strstr(string, "db ");
			if (substring)
			{
				substring += 3;
				for (auto i = 0; substring[i]; i++)
				{
					if (substring[i] == ' ')
					{
						substring[i] = 0;
						break;
					}
				}
				/*GROWTH_MEDIUM_FAST,
				GROWTH_SLIGHTLY_FAST,
				GROWTH_SLIGHTLY_SLOW,
				GROWTH_MEDIUM_SLOW,
				GROWTH_FAST,
				GROWTH_SLOW*/
				if (SDL_strstr(substring, "GROWTH_MEDIUM_FAST"))
				{
					data->growthRate = GrowthRate::GROWTH_MEDIUM_FAST;
				}
				else if (SDL_strstr(substring, "GROWTH_MEDIUM_SLOW"))
				{
					data->growthRate = GrowthRate::GROWTH_MEDIUM_SLOW;
				}
				else if (SDL_strstr(substring, "GROWTH_SLIGHTLY_FAST"))
				{
					data->growthRate = GrowthRate::GROWTH_SLIGHTLY_FAST;
				}
				else if (SDL_strstr(substring, "GROWTH_SLIGHTLY_SLOW"))
				{
					data->growthRate = GrowthRate::GROWTH_SLIGHTLY_SLOW;
				}
				else if (SDL_strstr(substring, "GROWTH_SLOW"))
				{
					data->growthRate = GrowthRate::GROWTH_SLOW;
				}
				else if (SDL_strstr(substring, "GROWTH_FAST"))
				{
					data->growthRate = GrowthRate::GROWTH_FAST;
				}
				else
				{
					sys.error("error parsing growth");
				}
			}
			else
			{
				sys.error("pkm data: error at line 14");
			}
		}
		else if(l > 13)
		{
			char* substring = SDL_strstr(string, "tmhm ");
			if (SDL_strstr(string, "; end"))
			{
				break;
			}
			else if (substring)
			{
				substring += 5;
				char* token;
				token = strtok(substring, ",");
				int i = 0;
				/* walk through other tokens */
				while (token != NULL)
				{
					
					util::remove_spaces(util::cleanStr(token));
					if (isalpha(token[0]))
					{
						data->learnset.push_back(std::string(token));
					}
					token = strtok(NULL, ",");
					i++;
				}
			}
			else if(SDL_strstr(string,","))
			{
				char* token;
				token = strtok(string, ",");
				int i = 0;
				/* walk through other tokens */
				while (token != NULL)
				{

					util::remove_spaces(util::cleanStr(token));
					if (isalpha(token[0]))
					{
						data->learnset.push_back(std::string(token));
					}
					token = strtok(NULL, ",");
					i++;
				}
			}
		}

		l++;
	}
	std::string name = data->getId();
	data->front = res.getTexture(pokemonName);
	data->back = res.getTexture(pokemonName+"b");
	pokemonDataMap[name] = data;
}

void ResourceManager::loadMap(std::string fileName)
{
	std::string pathData = "assets/data/map_data/" + fileName + ".blk";
	std::string pathObjects = "assets/data/map_objects/" + fileName + ".asm";
	std::string pathHeaders = "assets/data/map_headers/" + fileName + ".asm";
	std::string pathTexts = "assets/data/map_texts/" + fileName + ".asm";
	Map* map = new Map(-1,-1,nullptr, 0, "none",0, "none", 0, "none", 0, "none", 0);
	map->tileset = nullptr;
	map->name = "error";
	map->fileName = fileName;
	//copy the bytes of map data to a vector
	std::ifstream file(pathData, std::ios::binary);
	if (file.fail())
	{
		delete map;
		printf("%s does not exist.\n", pathData.c_str());
		return;
	}
	file.unsetf(std::ios::skipws);
	std::streampos fileSize;

	file.seekg(0, std::ios::end);
	fileSize = file.tellg();
	file.seekg(0, std::ios::beg);

	map->blocks.reserve((unsigned int)fileSize);
	map->blocks.insert(map->blocks.begin(),
		std::istream_iterator<Uint8>(file),
		std::istream_iterator<Uint8>());

	char string[1024];

	FILE *fp = fopen(pathHeaders.c_str(), "r");
	if (!fp)
		sys.error("Cant find the map header file");
	int l = 0;
	while (fgets(string, 1024, fp)) {
		//read blockset & mapName
		if (l == 1)
		{
			char* token;
			token = strtok(string, ",");
			int i = 0;
			/* walk through other tokens */
			while (token != NULL) {
				if (i == 1)
				{
					util::remove_spaces(token);
					for (int k = 0; token[k]; k++) {
						token[k] = tolower(token[k]);
						if (token[k] == '\n')
							token[k] = 0;
						if (token[k] == ';')
						{
							token[k] = 0;
							break;
						}
					}
					map->name = token;
					//printf("%s\n", token);
				}
				if (i == 2)
				{
					util::remove_spaces(token);
					for (int k = 0; token[k]; k++) {
						token[k] = tolower(token[k]);
						if (token[k] == '\n')
							token[k] = 0;
						if (token[k] == ';')
						{
							token[k] = 0;
							break;
						}
					}
					map->blockset = getBlockset(token);
					map->tileset = map->blockset->tileset;
					//printf("%s\n", token);
				}
				token = strtok(NULL, ",");
				i++;
			}
		}
		//read connections
		char* substring = strstr(string, "connection");
		if (substring != nullptr)
		{
			char location[128] = { 0 };
			char map_name[128] = { 0 };
			int offset = 0;
			substring += 11;
			//printf("%s", substring);
			char* token;
			token = strtok(substring, ",");
			int i = 0;
			/* walk through other tokens */
			while (token != NULL) {
				if (i == 0)
				{
					SDL_strlcpy(location, token, 128);
				}
				if (i == 2)
				{
					util::remove_spaces(token);
					for (int k = 0; token[k]; k++) {
						token[k] = tolower(token[k]);
						if (token[k] == '\n')
							token[k] = 0;
						if (token[k] == ';')
						{
							token[k] = 0;
							break;
						}
					}
					SDL_strlcpy(map_name, token, 128);
					//printf("%s\n", mapName);
				}
				if (i == 3)
				{
					token = util::cleanStr(token);
					offset = atoi(token);
					//printf("offset: %d\n", offset);
				}
				token = strtok(NULL, ",");
				i++;
			}
			if (strcmp(location, "north") == 0)
			{
				map->connection.north = map_name;
				map->connection.northOffset = offset;
				//printf("%s - %d\n", map->connection.north.c_str(), offset);
			}
			else if (strcmp(location, "south") == 0)
			{
				map->connection.south = map_name;
				map->connection.southOffset = offset;
				//printf("%s - %d\n", map->connection.south.c_str(), offset);
			}
			else if (strcmp(location, "east") == 0)
			{
				map->connection.east = map_name;
				map->connection.eastOffset = offset;
				//printf("%s - %d\n", map->connection.east.c_str(), offset);
			}
			else if (strcmp(location, "west") == 0)
			{
				map->connection.west = map_name;
				map->connection.westOffset = offset;
				//printf("%s - %d\n", map->connection.west.c_str(), offset);
			}
		}
		l++;
	}
	fclose(fp);

	
	fp = fopen("assets/data/constants/map_constants.asm", "r");
	if (!fp)
		sys.error("Cant find the map_constants.asm file");

	std::string uppercase = map->name + ",";
	std::transform(uppercase.begin(), uppercase.end(), uppercase.begin(), ::toupper);
	std::string search = "mapconst " + uppercase;

	while (fgets(string, 1024, fp)) {
		char* substring = strstr(string, search.c_str());
		if (substring != nullptr)
		{
			substring += 9;
			char* token;
			token = strtok(substring, ",");
			int i = 0;
			/* walk through other tokens */
			while (token != NULL) {
				if (i == 1 || i == 2)
				{
					util::remove_spaces(token);
					for (int k = 0; token[k]; k++) {
						if (token[k] == '\n')
							token[k] = 0;
						if (token[k] == ';')
						{
							token[k] = 0;
							break;
						}
					}
					if (i == 1)
					{
						map->height = atoi(token);
					}
					else if (i == 2)
					{
						map->width = atoi(token);
					}

				}
				token = strtok(NULL, ",");
				i++;
			}
		}
	}
	fclose(fp);

	fp = fopen(pathObjects.c_str(), "r");
	if (!fp)
		sys.error("Error when reading objects file.");
	l = 0;
	while (fgets(string, 1024, fp)) {
		//read background
		if (l == 1) // second line, background info
		{
			char string_c[1024];
			SDL_strlcpy(string_c, string, 1024);
			char* str = &string_c[0];
			str += 5;
			str[2] = 0;
			int bkg = strtol(str, NULL, 16);
			map->background = bkg;
			//printf("Background: %i (%s)\n", bkg,str);
		}
		//read warps
		char* substring = strstr(string, "warp");
		if (substring != nullptr && strchr(string,',') != nullptr)
		{
			substring += 4;
			if(*substring != '_')
			{ 
				Warp newwarp;
				newwarp.from = map->name;
				char* token;
				token = strtok(substring, ",");
				int i = 0;
				/* walk through other tokens */
				while (token != NULL) {
					if (i < 3)
					{
						int num = atoi(token);
						if (i == 0)
						{
							newwarp.at.x = num;
						}
						else if (i == 1)
						{
							newwarp.at.y = num;
						}
						else
						{
							newwarp.warpIn = num;
						}
						//printf("%d\n", num);
					}
					else
					{ 
						util::remove_spaces(token);
						for (int k = 0; token[k]; k++) {
							token[k] = tolower(token[k]);
							if (token[k] == '\n')
								token[k] = 0;
							if (token[k] == ';')
							{ 
								token[k] = 0;
								break;
							}
						}
						newwarp.to = token;
						//printf("%s\n", token);
					}

					token = strtok(NULL, ",");
					i++;
				}
				map->warps.push_back(newwarp);
			}
		}
		//signs
		substring = strstr(string, "sign");
		if (substring != nullptr && strchr(string, ',') != nullptr)
		{
			substring += 4;
			if (*substring != '_')
			{
				Sign newsign;
				char* token;
				token = strtok(substring, ",");
				int i = 0;
				/* walk through other tokens */
				while (token != NULL) {
					if (i < 3)
					{
						int num = atoi(token);
						if (i == 0)
						{
							newsign.pos.x = num;
						}
						else if (i == 1)
						{
							newsign.pos.y = num;
						}
						else
						{
							newsign.textID = num;
						}
						//printf("%d\n", num);
					}

					token = strtok(NULL, ",");
					i++;
				}
				map->signs.push_back(newsign);
			}
		}
		//npcs & trainers & pickups
		substring = strstr(string, "object");
		if (substring != nullptr && strchr(string, ',') != nullptr)
		{
			substring += 7;
			int type = 0; //0 - npc, 1 - pickup, 2 - trainer
			int count = 0;

			//determine the type
			for (size_t i = 0; i < strlen(substring); i++)
			{
				if (substring[i] == ';')
					break;
				if (substring[i] == ',')
					count++;
			}
			if (count == 5)
				type = 0;
			else if (count == 6)
				type = 1;
			else if (count == 7)
				type = 2;
			else
				sys.error("unknown object error");
			
			if (type == 0)
			{
				Npc *newNPC = new Npc();
				char* token;
				token = strtok(substring, ",");
				int i = 0;
				/* walk through other tokens */
				while (token != NULL) {
					if (i <= 5)
					{
						//int num = atoi(token);
						if (i == 0)
						{
							size_t k = 0;
							for (k = 0; token[k]; k++)
							{
								if (token[k] == '_')
									break;
							}
							token += k + 1;
							util::to_lower(token);
							newNPC->spriteName = token;
							newNPC->sprite = getSprite(newNPC->spriteName);
						}
						else if (i == 1)
						{
							int num = atoi(token);
							newNPC->pos.x = num;
						}
						else if(i == 2)
						{
							int num = atoi(token);
							newNPC->pos.y = num;
						}
						else if (i == 3)
						{
							if (SDL_strstr(token, "WALK"))
								newNPC->movMode = NpcMovementMode::WALK;
							else if (SDL_strstr(token, "STAY"))
								newNPC->movMode = NpcMovementMode::STAY;
							else
								sys.error("bad movMove on parse");
						}
						else if (i == 4)
						{
							if (SDL_strstr(token, "ANY_DIR"))
								newNPC->movDir = NpcMovementDir::ANY_DIR;
							else if (SDL_strstr(token, "UP_DOWN"))
								newNPC->movDir = NpcMovementDir::UP_DOWN;
							else if (SDL_strstr(token, "LEFT_RIGHT"))
								newNPC->movDir = NpcMovementDir::LEFT_RIGHT;
							else if (SDL_strstr(token, "DOWN"))
								newNPC->movDir = NpcMovementDir::DOWN;
							else if (SDL_strstr(token, "UP"))
								newNPC->movDir = NpcMovementDir::UP;
							else if (SDL_strstr(token, "LEFT"))
								newNPC->movDir = NpcMovementDir::LEFT;
							else if (SDL_strstr(token, "RIGHT"))
								newNPC->movDir = NpcMovementDir::RIGHT;
							else if (SDL_strstr(token, "NONE"))
								newNPC->movDir = NpcMovementDir::NONE;
							else if (SDL_strstr(token, "BOULDER_MOVEMENT_BYTE_2"))
								newNPC->movDir = NpcMovementDir::BOULDER_MOVEMENT_BYTE_2;
							else
								sys.error("bad movDir on parse");
						}
						else if (i == 5)
						{
							int num = atoi(token);
							newNPC->textID = num;
						}
						//printf("%d\n", num);
					}

					token = strtok(NULL, ",");
					i++;
				}
				map->objects.push_back(newNPC);
				newNPC->init();
			}
			else if (type == 1)
			{
				Item* newItem = new Item();
				char* token;
				token = strtok(substring, ",");
				int i = 0;
				/* walk through other tokens */
				while (token != NULL) {
					if (i <= 6)
					{
						//int num = atoi(token);
						if (i == 0)
						{
							size_t k = 0;
							for (k = 0; token[k]; k++)
							{
								if (token[k] == '_')
									break;
							}
							token += k + 1;
							util::to_lower(token);
							newItem->spriteName = token;
							newItem->sprite = getSprite(newItem->spriteName);
						}
						else if (i == 1)
						{
							int num = atoi(token);
							newItem->pos.x = num;
						}
						else if (i == 2)
						{
							int num = atoi(token);
							newItem->pos.y = num;
						}
						else if (i == 3)
						{
							if (SDL_strstr(token, "WALK"))
								newItem->movMode = NpcMovementMode::WALK;
							else if (SDL_strstr(token, "STAY"))
								newItem->movMode = NpcMovementMode::STAY;
							else
								sys.error("bad movMove on parse");
						}
						else if (i == 4)
						{
							if (SDL_strstr(token, "ANY_DIR"))
								newItem->movDir = NpcMovementDir::ANY_DIR;
							else if (SDL_strstr(token, "UP_DOWN"))
								newItem->movDir = NpcMovementDir::UP_DOWN;
							else if (SDL_strstr(token, "LEFT_RIGHT"))
								newItem->movDir = NpcMovementDir::LEFT_RIGHT;
							else if (SDL_strstr(token, "DOWN"))
								newItem->movDir = NpcMovementDir::DOWN;
							else if (SDL_strstr(token, "UP"))
								newItem->movDir = NpcMovementDir::UP;
							else if (SDL_strstr(token, "LEFT"))
								newItem->movDir = NpcMovementDir::LEFT;
							else if (SDL_strstr(token, "RIGHT"))
								newItem->movDir = NpcMovementDir::RIGHT;
							else if (SDL_strstr(token, "NONE"))
								newItem->movDir = NpcMovementDir::NONE;
							else if (SDL_strstr(token, "BOULDER_MOVEMENT_BYTE_2"))
								newItem->movDir = NpcMovementDir::BOULDER_MOVEMENT_BYTE_2;
							else
								sys.error("bad movDir on parse");
						}
						else if (i == 5)
						{
							int num = atoi(token);
							newItem->textID = num;
						}
						else if (i == 6)
						{
							size_t k = 0;
							for (k = 0; token[k]; k++)
							{
								if (token[k] == '\n')
								{
									token[k] = 0;
									break;
								}
							}
							newItem->itemID = token;
						}
						//printf("%d\n", num);
					}

					token = strtok(NULL, ",");
					i++;
				}
				map->objects.push_back(newItem);
				newItem->init();
			}
			else if (type == 2)
			{
				Trainer* newNPC = new Trainer();
				char* token;
				token = strtok(substring, ",");
				int i = 0;
				/* walk through other tokens */
				while (token != NULL) {
					if (i <= 7)
					{
						//int num = atoi(token);
						if (i == 0)
						{
							size_t k = 0;
							for (k = 0; token[k]; k++)
							{
								if (token[k] == '_')
									break;
							}
							token += k + 1;
							util::to_lower(token);
							newNPC->spriteName = token;
							newNPC->sprite = getSprite(newNPC->spriteName);
						}
						else if (i == 1)
						{
							int num = atoi(token);
							newNPC->pos.x = num;
						}
						else if (i == 2)
						{
							int num = atoi(token);
							newNPC->pos.y = num;
						}
						else if (i == 3)
						{
							if (SDL_strstr(token, "WALK"))
								newNPC->movMode = NpcMovementMode::WALK;
							else if (SDL_strstr(token, "STAY"))
								newNPC->movMode = NpcMovementMode::STAY;
							else
								sys.error("bad movMove on parse");
						}
						else if (i == 4)
						{
							if (SDL_strstr(token, "ANY_DIR"))
								newNPC->movDir = NpcMovementDir::ANY_DIR;
							else if (SDL_strstr(token, "UP_DOWN"))
								newNPC->movDir = NpcMovementDir::UP_DOWN;
							else if (SDL_strstr(token, "LEFT_RIGHT"))
								newNPC->movDir = NpcMovementDir::LEFT_RIGHT;
							else if (SDL_strstr(token, "DOWN"))
								newNPC->movDir = NpcMovementDir::DOWN;
							else if (SDL_strstr(token, "UP"))
								newNPC->movDir = NpcMovementDir::UP;
							else if (SDL_strstr(token, "LEFT"))
								newNPC->movDir = NpcMovementDir::LEFT;
							else if (SDL_strstr(token, "RIGHT"))
								newNPC->movDir = NpcMovementDir::RIGHT;
							else if (SDL_strstr(token, "NONE"))
								newNPC->movDir = NpcMovementDir::NONE;
							else if (SDL_strstr(token, "BOULDER_MOVEMENT_BYTE_2"))
								newNPC->movDir = NpcMovementDir::BOULDER_MOVEMENT_BYTE_2;
							else
								sys.error("bad movDir on parse");
						}
						else if (i == 5)
						{
							int num = atoi(token);
							newNPC->textID = num;
						}
						else if (i == 6)
						{
							util::remove_spaces(token);
							newNPC->trainerClass = util::cleanStr(token); //needs testing
						}
						else if (i == 7)
						{
							int num = atoi(token);
							newNPC->rosterID = num;
						}
						//printf("%d\n", num);
					}

					token = strtok(NULL, ",");
					i++;
				}
				map->objects.push_back(newNPC);
				newNPC->init();
			}
		}
		l++;
	}

	fclose(fp);

	fp = fopen(pathTexts.c_str(), "r");
	if (!fp)
		printf("%s has no texts\n", map->name.c_str());
	l = 0;
	static const char words[][16] = {
					"text ",
					"next ",
					"line ",
					"para ",
					"cont ",
					"done",
					"prompt",
					"page ",
					"dex ",
					"text_end",
					"text_start",
					"text_ram ",
					"text_decimal ",
					"text_bcd "
	};
	while (fp && fgets(string, 1024, fp)) {
		char* substring = strstr(string, "_");
		if (substring != nullptr)
		{
			substring++;
			for (int i = 0; substring[i]; i++) //find ":"
			{
				if (substring[i] == ':')
				{ 
					substring[i] = 0;
					break;
				}
			}
			Textset textset;
			textset.name = substring;
			bool foundEnd = false;
			Text* firstLine = nullptr;
			Text* prevLine = nullptr;
			int z = 0;
			while (true)
			{
				Text* line = nullptr;
				boolean foundsth = false;
				fgets(string, 1024, fp);
				l++;
				for(int i = 0; i < (int)TextType::NUM_TEXT_TYPE;i++)
				{ 
					substring = strstr(string, words[i]);
					if (substring != nullptr)
					{
						foundsth = true;
						line = new Text();
						line->type = (TextType)i;
						if (prevLine != nullptr)
							prevLine->next = line;
						if (z == 0)
							firstLine = line;
						z++;

						if (line->type == TextType::TYPE_TEXT_DECIMAL || line->type == TextType::TYPE_TEXT_RAM || line->type == TextType::TYPE_TEXT_BCD)
						{
							break;
						}
						else if (line->type == TextType::TYPE_TEXT_START)
						{
							SDL_strlcpy(line->text, " ", sizeof(line->text));
							break;
						}
						else if(line->type != TextType::TYPE_DONE && line->type != TextType::TYPE_TEXT_END && line->type != TextType::TYPE_PROMPT)
						{ 
							substring += strlen(words[i])+1;
							for (int i = 0; substring[i]; i++) //find and remove "
							{
								if (substring[i] == '\"')
								{
									substring[i] = 0;
									break;
								}
							}
							SDL_strlcpy(line->text, substring, sizeof(line->text));
							break;
						}
						else
						{
							foundEnd = true;
							break;
						}
					}
				}
				if (foundsth)
					prevLine = line;
				else if(strlen(string) > 1)
					printf("TEXT PARSER: invalid line %s\n", string);
				if (foundEnd)
					break;

			}
			if (z == 0)
				printf("Text parsing failed for %s\n", map->name.c_str());
			textset.start = firstLine;
			map->texts.push_back(textset);

		}
		l++;
	}
	if(fp)
		fclose(fp);

	//printf("%s: (%i, %i)\n", map->name.c_str(), map->height, map->width);
	mapMap[map->name] = map;

}

Tileset* ResourceManager::getTileset(std::string textureName)
{
	std::map<std::string, Tileset*>::iterator it = tilesetMap.find(textureName);

	if (it == tilesetMap.end())
	{
		sys.error("Trying to look for a tileset that doesn't exist");
		return nullptr;
	}
	else
	{
		return it->second;
	}
}

Texture* ResourceManager::getTexture(std::string textureName)
{
	std::map<std::string, Texture*>::iterator it = textureMap.find(textureName);

	if (it == textureMap.end())
	{
		//sys.error("Trying to look for a texture that doesn't exist");
		return nullptr;
	}
	else
	{
		return it->second;
	}
}

Sprite* ResourceManager::getSprite(std::string spriteName)
{
	std::map<std::string, Sprite*>::iterator it = spriteMap.find(spriteName);

	if (it == spriteMap.end())
	{
		sys.error("Trying to look for a texture that doesn't exist");
		return nullptr;
	}
	else
	{
		return it->second;
	}
}

Blockset* ResourceManager::getBlockset(std::string blocksetName)
{
	std::map<std::string, Blockset*>::iterator it = blocksetMap.find(blocksetName);

	if (it == blocksetMap.end())
	{
		sys.error("Trying to look for a blockset that doesn't exist");
		return nullptr;
	}
	else
	{
		return it->second;
	}
}

Map* ResourceManager::getMap(std::string mapName)
{
	if (mapName == "none")
		return nullptr;

	std::map<std::string, Map*>::iterator it = mapMap.find(mapName);

	if (it == mapMap.end())
	{
		//printf("Warning: Trying to look for a map that doesn't exist");
		return nullptr;
	}
	else
	{
		return it->second;
	}
}