#pragma once
#include <map>
#include <unordered_map>
#include <string>
#include "../game/map.h"
#include "../game/trainer_data.h"
#include "../game/evolution_set.h"
#include "../game/learn_set.h"
#include "../game/move.h"

#define MAX_BLOCKS 256

class ResourceManager
{
public:
	void loadTileset(std::string textureName, const char *path,std::vector<Uint8>* collData, std::vector<Uint8>* warpData, Uint8 counterTile1, Uint8 counterTile2, Uint8 counterTile3, Uint8 grassTile, Permission permission);
	Tileset *getTileset(std::string textureName);

	void loadTexture(std::string textureName, const char* path, bool transparent = false);
	void loadTexture(std::string textureName, std::string path, bool transparent = false);
	void addTexture(std::string textureName, Texture* texture);
	Texture* getTexture(std::string textureName);

	void loadTexts(std::vector<Textset*> *textsetList, std::string path);
	Texture* createText(std::string text);
	void updateText(Texture* texture, std::string text);

	void loadSprite(std::string spriteName);
	Sprite* getSprite(std::string spriteName);

	void loadBlockset(std::string blocksetName, std::string tilesetName, const char* path);
	Blockset* getBlockset(std::string blocksetName);

	void loadMap(std::string fileName);
	Map* getMap(std::string mapName);

	void loadPokemonData(std::string pokemonName);
	PokemonData* getPokemonData(std::string pokemonName);

	void setObject(std::string name, Object* pointer);
	Object* getObject(std::string name);

	void addTextRedefinition(std::string in, std::string out);
	std::string getTextRedefinition(std::string in);

	void addTrainerConstant(std::string name, int id);
	int getTrainerConstant(std::string name);

	void addTrainerData(int id, TrainerData* trainerData);
	TrainerData* getTrainerData(int id);

	void loadEvolutionAndLearnSetData();
	EvolutionSet* getEvolutionInfo(std::string pokemonName);
	LearnSet* getLearnset(std::string pokemonName);

	void loadMoves(std::string path);
	
private:

	std::unordered_map<std::string, Tileset*> tilesetMap;
	std::unordered_map<std::string, Texture*> textureMap;
	std::unordered_map<std::string, Sprite*> spriteMap;
	std::unordered_map<std::string, Blockset*> blocksetMap;
	std::unordered_map<std::string, Map*> mapMap;
	std::unordered_map<std::string, PokemonData*> pokemonDataMap;
	std::unordered_map<std::string, std::string> rawPokemonNameToDexName;
	std::unordered_map<std::string, Object*> objectMap;
	std::unordered_map<std::string, std::string> textRedefinitionMap;
	std::unordered_map<std::string, int> trainerConstantMap;
	std::unordered_map<int, TrainerData*> trainerDataMap;
	std::unordered_map<std::string, EvolutionSet*> evolutionMap;
	std::unordered_map<std::string, LearnSet*> learnSetMap;
	std::unordered_map<std::string, Move*> moveMap;
};