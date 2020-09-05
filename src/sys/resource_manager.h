#pragma once
#include <map>
#include <string>
#include "../game/map.h"

#define MAX_BLOCKS 256

class ResourceManager
{
public:
	void loadTileset(std::string textureName, const char *path,std::vector<Uint8>* collData);
	Tileset *getTileset(std::string textureName);

	void loadTexture(std::string textureName, const char* path);
	Texture* getTexture(std::string textureName);

	void loadBlockset(std::string blocksetName, const char* path);
	Blockset* getBlockset(std::string blocksetName);

	void loadMap(std::string mapName, const char* path, std::string blockset, int height, int width, int background, std::string north, int northOffset, std::string west, int westOffset, std::string east, int eastOffset, std::string south, int southOffset);
	Map* getMap(std::string mapName);
	
private:
	std::map<std::string, Tileset*> tilesetMap;
	std::map<std::string, Texture*> textureMap;
	std::map<std::string, Blockset*> blocksetMap;
	std::map<std::string, Map*> mapMap;
};