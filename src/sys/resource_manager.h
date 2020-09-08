#pragma once
#include <map>
#include <string>
#include "../game/map.h"

#define MAX_BLOCKS 256

class ResourceManager
{
public:
	void loadTileset(std::string textureName, const char *path,std::vector<Uint8>* collData, std::vector<Uint8>* warpData, Uint8 counterTile1, Uint8 counterTile2, Uint8 counterTile3, Uint8 grassTile, Permission permission);
	Tileset *getTileset(std::string textureName);

	void loadTexture(std::string textureName, const char* path, bool transparent = false);
	Texture* getTexture(std::string textureName);

	void loadSprite(std::string textureName, const char* path);
	Sprite* getSprite(std::string textureName);

	void loadBlockset(std::string blocksetName, std::string tilesetName, const char* path);
	Blockset* getBlockset(std::string blocksetName);

	void loadMap(std::string fileName);
	Map* getMap(std::string mapName);
	
private:
	std::map<std::string, Tileset*> tilesetMap;
	std::map<std::string, Texture*> textureMap;
	std::map<std::string, Sprite*> spriteMap;
	std::map<std::string, Blockset*> blocksetMap;
	std::map<std::string, Map*> mapMap;
};