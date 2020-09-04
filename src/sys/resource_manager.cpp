#include "system.h"
#include <iostream>
#include <fstream>

void ResourceManager::loadTileset(std::string textureName, const char *path)
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

	tileset->texture = SDL_CreateTextureFromSurface(sys.getRenderer(), tileset->surface);
	
	tilesetMap[textureName] = tileset;
	SDL_FreeSurface(sur);
}

void ResourceManager::loadBlockset(std::string blocksetName, const char* path)
{
	Blockset* blockset = new Blockset();
	blockset->blocks = new Block[MAX_BLOCKS]();
	Tileset* tileset = getTileset(blocksetName);

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
		printf("Warning: Trying to look for a map that doesn't exist");
		return nullptr;
	}
	else
	{
		return it->second;
	}
}