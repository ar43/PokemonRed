#include "system.h"
#include <iostream>
#include <fstream>

void ResourceManager::loadTileset(std::string textureName, const char *path, std::vector<Uint8>* collData)
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

	tileset->texture = SDL_CreateTextureFromSurface(sys.getRenderer(), tileset->surface);
	
	tilesetMap[textureName] = tileset;
	SDL_FreeSurface(sur);
}

void ResourceManager::loadBlockset(std::string blocksetName, const char* path)
{
	Blockset* blockset = new Blockset();
	blockset->blocks = new Block[MAX_BLOCKS]();
	Tileset* tileset = getTileset(blocksetName);
	blockset->name = blocksetName;

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
		}
		SDL_SetRenderTarget(sys.getRenderer(), NULL);
		blockset->blocks[i].valid = true;
		i++;
	}
	

	blocksetMap[blocksetName] = blockset;
}

void ResourceManager::loadMap(std::string mapName, const char* path, std::string blockset, int height, int width, int background, std::string north, int northOffset, std::string west, int westOffset, std::string east, int eastOffset, std::string south, int southOffset)
{
	Map* map = new Map(height,width,getBlockset(blockset), background, north,northOffset, west, westOffset, east, eastOffset, south, southOffset);

	//copy the bytes of map data to a vector
	std::ifstream file(path, std::ios::binary);
	file.unsetf(std::ios::skipws);
	std::streampos fileSize;

	file.seekg(0, std::ios::end);
	fileSize = file.tellg();
	file.seekg(0, std::ios::beg);

	map->blocks.reserve(fileSize);
	map->blocks.insert(map->blocks.begin(),
		std::istream_iterator<Uint8>(file),
		std::istream_iterator<Uint8>());

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