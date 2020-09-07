#include "system.h"
#include <iostream>
#include <fstream>
#include <algorithm>

void ResourceManager::loadTileset(std::string textureName, const char *path, std::vector<Uint8>* collData, std::vector<Uint8>* warpData, Uint8 counterTile1, Uint8 counterTile2, Uint8 counterTile3, Uint8 grassTile, Permission permission)
{
	SDL_Surface *sur = IMG_Load(path);

	if (!sur) {
		sys.error(util::va("IMG_Load: %s\n", IMG_GetError()));
		// handle error
	}
	SDL_Surface* gsSurface = SDL_ConvertSurfaceFormat(sur,
		SDL_PIXELFORMAT_ARGB8888,
		0);

	Tileset *tileset = new Tileset();
	tileset->surface = gsSurface;
	tileset->format = gsSurface->format->format;
	tileset->collData = collData;
	tileset->warpData = warpData;
	tileset->w = gsSurface->w;
	tileset->h = gsSurface->h;
	tileset->counterTiles[0] = counterTile1;
	tileset->counterTiles[1] = counterTile2;
	tileset->counterTiles[2] = counterTile3;
	tileset->grassTile = grassTile;
	if (grassTile == 0x52)
	{
		tileset->grassName = "grass1";
	}
	tileset->permission = permission;

	tileset->texture = SDL_CreateTextureFromSurface(sys.getRenderer(), tileset->surface);
	
	tilesetMap[textureName] = tileset;
	SDL_FreeSurface(sur);
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
	SDL_FreeSurface(sur);
}

void ResourceManager::loadSprite(std::string spriteName, const char* path)
{
	SDL_Surface* sur = IMG_Load(path);

	if (!sur) {
		sys.error(util::va("IMG_Load: %s\n", IMG_GetError()));
		// handle error
	}
	//SDL_Surface* gsSurface = SDL_ConvertSurfaceFormat(sur,SDL_PIXELFORMAT_ARGB8888,0);
	SDL_Surface* gsSurface = sur;
	SDL_SetColorKey(gsSurface, SDL_TRUE, SDL_MapRGB(gsSurface->format, 0xff, 0xff, 0xff));
	Sprite* sprite = new Sprite();
	sprite->surface = gsSurface;
	sprite->format = gsSurface->format->format;
	sprite->w = gsSurface->w;
	sprite->h = gsSurface->h;
	sprite->size = sprite->h > 3 * 16 ? 6 : 3;
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
			//for carpet warp (is 0 2 8 A actually correct? assuming Red's House, but needs testing)
			if(tileset->permission == INDOOR)
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
	

	blocksetMap[blocksetName] = blockset;
}

void ResourceManager::loadMap(std::string mapName, std::string fileName, std::string blockset, int background, std::string north, int northOffset, std::string west, int westOffset, std::string east, int eastOffset, std::string south, int southOffset)
{
	int height = -1;
	int width = -1;
	char string[1024];
	FILE* fp = fopen("assets/data/constants/map_constants.asm", "r");
	if (!fp)
		sys.error("Cant find the map_constants.asm file");

	std::string uppercase = mapName + ",";
	std::transform(uppercase.begin(), uppercase.end(), uppercase.begin(), ::toupper);

	while (fgets(string, 1024, fp)) {
		char* substring = strstr(string, uppercase.c_str());
		if (substring != nullptr)
		{
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
						height = atoi(token);
					}
					else if (i == 2)
					{
						width = atoi(token);
					}

				}
				token = strtok(NULL, ",");
				i++;
			}
		}
	}
	fclose(fp);

	std::string pathData = "assets/data/maps/" + fileName + ".blk";
	std::string pathObjects = "assets/data/objects/" + fileName + ".asm";
	Map* map = new Map(height,width,getBlockset(blockset), background, north,northOffset, west, westOffset, east, eastOffset, south, southOffset);
	map->tileset = getBlockset(blockset)->tileset;
	map->name = mapName;
	//copy the bytes of map data to a vector
	std::ifstream file(pathData, std::ios::binary);
	file.unsetf(std::ios::skipws);
	std::streampos fileSize;

	file.seekg(0, std::ios::end);
	fileSize = file.tellg();
	file.seekg(0, std::ios::beg);

	map->blocks.reserve(fileSize);
	map->blocks.insert(map->blocks.begin(),
		std::istream_iterator<Uint8>(file),
		std::istream_iterator<Uint8>());

	printf("%s: (%i, %i)\n", mapName.c_str(), map->height, map->width);

	if (map->height == -1 || map->width == -1)
		sys.error("Corrupted map (bad width and height)");

	fp = fopen(pathObjects.c_str(), "r");
	if (!fp)
		sys.error("Error when reading objects file.");
	
	while (fgets(string, 1024, fp)) {
		//read warps
		char* substring = strstr(string, "warp");
		if (substring != nullptr && strchr(string,',') != nullptr)
		{
			substring += 4;
			if(*substring != '_')
			{ 
				Warp newwarp;
				newwarp.from = mapName;
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
	}

	fclose(fp);

	mapMap[mapName] = map;

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