#pragma once
#include <map>
#include <string>
#include "../game/map.h"

#define MAX_BLOCKS 256

class ResourceManager
{
public:
	void loadTileset(std::string textureName, const char *path);
	Tileset *getTileset(std::string textureName);

	void loadBlockset(std::string blocksetName, const char* path);
	Blockset* getBlockset(std::string blocksetName);

	void loadMap(std::string mapName, const char* path, std::string blockset, int height, int width);
	Map* getMap(std::string mapName);
	
private:
	std::map<std::string, Tileset*> tilesetMap;
	std::map<std::string, Blockset*> blocksetMap;
	std::map<std::string, Map*> mapMap;
};