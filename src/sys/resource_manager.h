#pragma once
#include <map>
#include <string>

class ResourceManager
{
public:
	void loadTileset(std::string textureName, const char *path);
	Tileset *getTileset(std::string textureName);

	void loadBlockset(std::string blocksetName, const char* path);
	Block* getBlockset(std::string blocksetName);
	
private:
	std::map<std::string, Tileset*> tilesetMap;
	std::map<std::string, Block*> blocksetMap;
};