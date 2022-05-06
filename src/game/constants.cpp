#include "../sys/system.h"
/*
Underground_Coll::
	coll_tiles $0b, $0c, $13, $15, $18

Overworld_Coll::
	coll_tiles $00, $10, $1b, $20, $21, $23, $2c, $2d, $2e, $30, $31, $33, $39, $3c, $3e, $52, $54, $58, $5b

RedsHouse1_Coll::
RedsHouse2_Coll::
	coll_tiles $01, $02, $03, $11, $12, $13, $14, $1c, $1a

Mart_Coll::
Pokecenter_Coll::
	coll_tiles $11, $1a, $1c, $3c, $5e

Dojo_Coll::
Gym_Coll::
	coll_tiles $11, $16, $19, $2b, $3c, $3d, $3f, $4a, $4c, $4d, $03

Forest_Coll::
	coll_tiles $1e, $20, $2e, $30, $34, $37, $39, $3a, $40, $51, $52, $5a, $5c, $5e, $5f

House_Coll::
	coll_tiles $01, $12, $14, $28, $32, $37, $44, $54, $5c

ForestGate_Coll::
Museum_Coll::
Gate_Coll::
	coll_tiles $01, $12, $14, $1a, $1c, $37, $38, $3b, $3c, $5e

Ship_Coll::
	coll_tiles $04, $0d, $17, $1d, $1e, $23, $34, $37, $39, $4a

ShipPort_Coll::
	coll_tiles $0a, $1a, $32, $3b

Cemetery_Coll::
	coll_tiles $01, $10, $13, $1b, $22, $42, $52

Interior_Coll::
	coll_tiles $04, $0f, $15, $1f, $3b, $45, $47, $55, $56

Cavern_Coll::
	coll_tiles $05, $15, $18, $1a, $20, $21, $22, $2a, $2d, $30

	coll_tiles ; unused

Lobby_Coll::
	coll_tiles $14, $17, $1a, $1c, $20, $38, $45

Mansion_Coll::
	coll_tiles $01, $05, $11, $12, $14, $1a, $1c, $2c, $53

Lab_Coll::
	coll_tiles $0c, $26, $16, $1e, $34, $37

Club_Coll::
	coll_tiles $0f, $1a, $1f, $26, $28, $29, $2c, $2d, $2e, $2f, $41

Facility_Coll::
	coll_tiles $01, $10, $11, $13, $1b, $20, $21, $22, $30, $31, $32, $42, $43, $48, $52, $55, $58, $5e

Plateau_Coll::
	coll_tiles $1b, $23, $2c, $2d, $3b, $45
*/


/*
OverworldWarpTileIDs:
	warp_tiles $1B, $58

.ForestGateWarpTileIDs:
.MuseumWarpTileIDs:
.GateWarpTileIDs:
	db $3B
	; fallthrough
.RedsHouse1WarpTileIDs:
.RedsHouse2WarpTileIDs:
	warp_tiles $1A, $1C

.MartWarpTileIDs:
.PokecenterWarpTileIDs:
	warp_tiles $5E

.ForestWarpTileIDs:
	warp_tiles $5A, $5C, $3A

.DojoWarpTileIDs:
.GymWarpTileIDs:
	warp_tiles $4A

.HouseWarpTileIDs:
	warp_tiles $54, $5C, $32

.ShipWarpTileIDs:
	warp_tiles $37, $39, $1E, $4A

.InteriorWarpTileIDs:
	warp_tiles $15, $55, $04

.CavernWarpTileIDs:
	warp_tiles $18, $1A, $22

.LobbyWarpTileIDs:
	warp_tiles $1A, $1C, $38

.MansionWarpTileIDs:
	warp_tiles $1A, $1C, $53

.LabWarpTileIDs:
	warp_tiles $34

.FacilityWarpTileIDs:
	db $43, $58, $20
	; fallthrough
.CemeteryWarpTileIDs:
	db $1B
	; fallthrough
.UndergroundWarpTileIDs:
	warp_tiles $13

.PlateauWarpTileIDs:
	db $1B, $3B
	; fallthrough
.ShipPortWarpTileIDs:
.ClubWarpTileIDs:
	warp_tiles ; end
	*/



namespace Constants
{
	TTF_Font* font = nullptr;

	std::string blocksets[][3]{ {"overworld", "overworld", "assets/data/blocksets/overworld.bst"},
	{"reds_house_1", "reds_house", "assets/data/blocksets/reds_house.bst"},
	{"reds_house_2", "reds_house", "assets/data/blocksets/reds_house.bst"},
	{"mart", "mart", "assets/data/blocksets/pokecenter.bst"},
	{"forest", "forest", "assets/data/blocksets/forest.bst"},
	{"dojo", "dojo", "assets/data/blocksets/gym.bst"},
	{"pokecenter", "pokecenter", "assets/data/blocksets/pokecenter.bst"},
	{"gym", "gym", "assets/data/blocksets/gym.bst"},
	{"house", "house", "assets/data/blocksets/house.bst"},
	{"forest_gate", "forestgate", "assets/data/blocksets/gate.bst"},
	{"museum", "museum", "assets/data/blocksets/gate.bst"},
	{"underground", "underground", "assets/data/blocksets/underground.bst"},
	{"gate", "gate", "assets/data/blocksets/gate.bst"},
	{"ship", "ship", "assets/data/blocksets/ship.bst"},
	{"ship_port", "shipport", "assets/data/blocksets/ship_port.bst"},
	{"cemetery", "cemetery", "assets/data/blocksets/cemetery.bst"},
	{"interior", "interior", "assets/data/blocksets/interior.bst"},
	{"cavern", "cavern", "assets/data/blocksets/cavern.bst"},
	{"lobby", "lobby", "assets/data/blocksets/lobby.bst"},
	{"mansion", "mansion", "assets/data/blocksets/mansion.bst"},
	{"lab", "lab", "assets/data/blocksets/lab.bst"},
	{"club", "club", "assets/data/blocksets/club.bst"},
	{"facility", "facility", "assets/data/blocksets/facility.bst"},
	{"plateau", "plateau", "assets/data/blocksets/plateau.bst"} };

	int num_blocksets = 24;

	namespace Coll
	{
		std::vector<Uint8> overworld{ 0x00, 0x10, 0x1b, 0x20, 0x21, 0x23, 0x2c, 0x2d, 0x2e, 0x30, 0x31, 0x33, 0x39, 0x3c, 0x3e, 0x52, 0x54, 0x58, 0x5b };
		std::vector<Uint8> redshouse{ 0x01, 0x02, 0x03, 0x11, 0x12, 0x13, 0x14, 0x1c, 0x1a };
		std::vector<Uint8> underground{ 0x0b, 0x0c, 0x13, 0x15, 0x18 };
		std::vector<Uint8> mart{ 0x11, 0x1a, 0x1c, 0x3c, 0x5e };
		std::vector<Uint8> pokecenter{ 0x11, 0x1a, 0x1c, 0x3c, 0x5e };
		std::vector<Uint8> dojo{ 0x11, 0x16, 0x19, 0x2b, 0x3c, 0x3d, 0x3f, 0x4a, 0x4c, 0x4d, 0x03 };
		std::vector<Uint8> gym{ 0x11, 0x16, 0x19, 0x2b, 0x3c, 0x3d, 0x3f, 0x4a, 0x4c, 0x4d, 0x03 };
		std::vector<Uint8> forest{ 0x1e, 0x20, 0x2e, 0x30, 0x34, 0x37, 0x39, 0x3a, 0x40, 0x51, 0x52, 0x5a, 0x5c, 0x5e, 0x5f };
		std::vector<Uint8> house{ 0x01, 0x12, 0x14, 0x28, 0x32, 0x37, 0x44, 0x54, 0x5c };
		std::vector<Uint8> forestgate{ 0x01, 0x12, 0x14, 0x1a, 0x1c, 0x37, 0x38, 0x3b, 0x3c, 0x5e };
		std::vector<Uint8> museum{ 0x01, 0x12, 0x14, 0x1a, 0x1c, 0x37, 0x38, 0x3b, 0x3c, 0x5e };
		std::vector<Uint8> gate{ 0x01, 0x12, 0x14, 0x1a, 0x1c, 0x37, 0x38, 0x3b, 0x3c, 0x5e };
		std::vector<Uint8> ship{ 0x04, 0x0d, 0x17, 0x1d, 0x1e, 0x23, 0x34, 0x37, 0x39, 0x4a };
		std::vector<Uint8> shipport{ 0x0a, 0x1a, 0x32, 0x3b };
		std::vector<Uint8> cemetery{ 0x01, 0x10, 0x13, 0x1b, 0x22, 0x42, 0x52 };
		std::vector<Uint8> interior{ 0x04, 0x0f, 0x15, 0x1f, 0x3b, 0x45, 0x47, 0x55, 0x56 };
		std::vector<Uint8> cavern{ 0x05, 0x15, 0x18, 0x1a, 0x20, 0x21, 0x22, 0x2a, 0x2d, 0x30 };
		std::vector<Uint8> lobby{ 0x14, 0x17, 0x1a, 0x1c, 0x20, 0x38, 0x45 };
		std::vector<Uint8> mansion{ 0x01, 0x05, 0x11, 0x12, 0x14, 0x1a, 0x1c, 0x2c, 0x53 };
		std::vector<Uint8> lab{ 0x0c, 0x26, 0x16, 0x1e, 0x34, 0x37 };
		std::vector<Uint8> club{ 0x0f, 0x1a, 0x1f, 0x26, 0x28, 0x29, 0x2c, 0x2d, 0x2e, 0x2f, 0x41 };
		std::vector<Uint8> facility{ 0x01, 0x10, 0x11, 0x13, 0x1b, 0x20, 0x21, 0x22, 0x30, 0x31, 0x32, 0x42, 0x43, 0x48, 0x52, 0x55, 0x58, 0x5e };
		std::vector<Uint8> plateau{ 0x1b, 0x23, 0x2c, 0x2d, 0x3b, 0x45 };
	}
	namespace Warp
	{
		std::vector<Uint8> overworld{ 0x1B, 0x58 };
		std::vector<Uint8> reds_house{ 0x1A, 0x1C };

		std::vector<Uint8> underground{ 0x13 };
		std::vector<Uint8> mart{ 0x5E };
		std::vector<Uint8> pokecenter{ 0x5E };
		std::vector<Uint8> dojo{ 0x4A };
		std::vector<Uint8> gym{ 0x4A };
		std::vector<Uint8> forest{ 0x5A, 0x5C, 0x3A };
		std::vector<Uint8> house{ 0x54, 0x5C, 0x32 };
		std::vector<Uint8> forestgate{ 0x3B };
		std::vector<Uint8> museum{ 0x3B };
		std::vector<Uint8> gate{ 0x3B };
		std::vector<Uint8> ship{ 0x37, 0x39, 0x1E, 0x4A };
		std::vector<Uint8> shipport{};
		std::vector<Uint8> cemetery{ 0x1B };
		std::vector<Uint8> interior{ 0x15, 0x55, 0x04 };
		std::vector<Uint8> cavern{ 0x18, 0x1A, 0x22 };
		std::vector<Uint8> lobby{ 0x1A, 0x1C, 0x38 };
		std::vector<Uint8> mansion{ 0x1A, 0x1C, 0x53 };
		std::vector<Uint8> lab{ 0x34 };
		std::vector<Uint8> club{};
		std::vector<Uint8> facility{ 0x43, 0x58, 0x20 };
		std::vector<Uint8> plateau{ 0x1B, 0x3B };

		std::vector<Uint8> down{ 0x01, 0x12, 0x17, 0x3D, 0x04, 0x18, 0x33 };
		std::vector<Uint8> up{ 0x01, 0x5C };
		std::vector<Uint8> left{ 0x1A, 0x4B };
		std::vector<Uint8> right{ 0x0F, 0x4E };
	}

	namespace HS
	{
		std::string table[] = {
			"HS_PALLET_TOWN_OAK",
			"HS_LYING_OLD_MAN",
			"HS_OLD_MAN",
			"HS_MUSEUM_GUY",
			"HS_GYM_GUY",
			"HS_CERULEAN_RIVAL",
			"HS_CERULEAN_ROCKET",
			"HS_CERULEAN_GUARD_1",
			"HS_CERULEAN_CAVE_GUY",
			"HS_CERULEAN_GUARD_2",
			"HS_SAFFRON_CITY_1",
			"HS_SAFFRON_CITY_2",
			"HS_SAFFRON_CITY_3",
			"HS_SAFFRON_CITY_4",
			"HS_SAFFRON_CITY_5",
			"HS_SAFFRON_CITY_6",
			"HS_SAFFRON_CITY_7",
			"HS_SAFFRON_CITY_8",
			"HS_SAFFRON_CITY_9",
			"HS_SAFFRON_CITY_A",
			"HS_SAFFRON_CITY_B",
			"HS_SAFFRON_CITY_C",
			"HS_SAFFRON_CITY_D",
			"HS_SAFFRON_CITY_E",
			"HS_SAFFRON_CITY_F",
			"HS_ROUTE_2_ITEM_1",
			"HS_ROUTE_2_ITEM_2",
			"HS_ROUTE_4_ITEM",
			"HS_ROUTE_9_ITEM",
			"HS_ROUTE_12_SNORLAX",
			"HS_ROUTE_12_ITEM_1",
			"HS_ROUTE_12_ITEM_2",
			"HS_ROUTE_15_ITEM",
			"HS_ROUTE_16_SNORLAX",
			"HS_ROUTE_22_RIVAL_1",
			"HS_ROUTE_22_RIVAL_2",
			"HS_NUGGET_BRIDGE_GUY",
			"HS_ROUTE_24_ITEM",
			"HS_ROUTE_25_ITEM",
			"HS_DAISY_SITTING",
			"HS_DAISY_WALKING",
			"HS_TOWN_MAP",
			"HS_OAKS_LAB_RIVAL",
			"HS_STARTER_BALL_1",
			"HS_STARTER_BALL_2",
			"HS_STARTER_BALL_3",
			"HS_OAKS_LAB_OAK_1",
			"HS_POKEDEX_1",
			"HS_POKEDEX_2",
			"HS_OAKS_LAB_OAK_2",
			"HS_VIRIDIAN_GYM_GIOVANNI",
			"HS_VIRIDIAN_GYM_ITEM",
			"HS_OLD_AMBER",
			"HS_CERULEAN_CAVE_1F_ITEM_1",
			"HS_CERULEAN_CAVE_1F_ITEM_2",
			"HS_CERULEAN_CAVE_1F_ITEM_3",
			"HS_POKEMON_TOWER_2F_RIVAL",
			"HS_POKEMON_TOWER_3F_ITEM",
			"HS_POKEMON_TOWER_4F_ITEM_1",
			"HS_POKEMON_TOWER_4F_ITEM_2",
			"HS_POKEMON_TOWER_4F_ITEM_3",
			"HS_POKEMON_TOWER_5F_ITEM",
			"HS_POKEMON_TOWER_6F_ITEM_1",
			"HS_POKEMON_TOWER_6F_ITEM_2",
			"HS_POKEMON_TOWER_7F_ROCKET_1",
			"HS_POKEMON_TOWER_7F_ROCKET_2",
			"HS_POKEMON_TOWER_7F_ROCKET_3",
			"HS_POKEMON_TOWER_7F_MR_FUJI",
			"HS_MR_FUJIS_HOUSE_MR_FUJI",
			"HS_CELADON_MANSION_EEVEE_GIFT",
			"HS_GAME_CORNER_ROCKET",
			"HS_WARDENS_HOUSE_ITEM",
			"HS_POKEMON_MANSION_1F_ITEM_1",
			"HS_POKEMON_MANSION_1F_ITEM_2",
			"HS_FIGHTING_DOJO_GIFT_1",
			"HS_FIGHTING_DOJO_GIFT_2",
			"HS_SILPH_CO_1F_RECEPTIONIST",
			"HS_VOLTORB_1",
			"HS_VOLTORB_2",
			"HS_VOLTORB_3",
			"HS_ELECTRODE_1",
			"HS_VOLTORB_4",
			"HS_VOLTORB_5",
			"HS_ELECTRODE_2",
			"HS_VOLTORB_6",
			"HS_ZAPDOS",
			"HS_POWER_PLANT_ITEM_1",
			"HS_POWER_PLANT_ITEM_2",
			"HS_POWER_PLANT_ITEM_3",
			"HS_POWER_PLANT_ITEM_4",
			"HS_POWER_PLANT_ITEM_5",
			"HS_MOLTRES",
			"HS_VICTORY_ROAD_2F_ITEM_1",
			"HS_VICTORY_ROAD_2F_ITEM_2",
			"HS_VICTORY_ROAD_2F_ITEM_3",
			"HS_VICTORY_ROAD_2F_ITEM_4",
			"HS_VICTORY_ROAD_2F_BOULDER",
			"HS_BILL_POKEMON",
			"HS_BILL_1",
			"HS_BILL_2",
			"HS_VIRIDIAN_FOREST_ITEM_1",
			"HS_VIRIDIAN_FOREST_ITEM_2",
			"HS_VIRIDIAN_FOREST_ITEM_3",
			"HS_MT_MOON_1F_ITEM_1",
			"HS_MT_MOON_1F_ITEM_2",
			"HS_MT_MOON_1F_ITEM_3",
			"HS_MT_MOON_1F_ITEM_4",
			"HS_MT_MOON_1F_ITEM_5",
			"HS_MT_MOON_1F_ITEM_6",
			"HS_MT_MOON_B2F_FOSSIL_1",
			"HS_MT_MOON_B2F_FOSSIL_2",
			"HS_MT_MOON_B2F_ITEM_1",
			"HS_MT_MOON_B2F_ITEM_2",
			"HS_SS_ANNE_2F_RIVAL",
			"HS_SS_ANNE_1F_ROOMS_ITEM",
			"HS_SS_ANNE_2F_ROOMS_ITEM_1",
			"HS_SS_ANNE_2F_ROOMS_ITEM_2",
			"HS_SS_ANNE_B1F_ROOMS_ITEM_1",
			"HS_SS_ANNE_B1F_ROOMS_ITEM_2",
			"HS_SS_ANNE_B1F_ROOMS_ITEM_3",
			"HS_VICTORY_ROAD_3F_ITEM_1",
			"HS_VICTORY_ROAD_3F_ITEM_2",
			"HS_VICTORY_ROAD_3F_BOULDER",
			"HS_ROCKET_HIDEOUT_B1F_ITEM_1",
			"HS_ROCKET_HIDEOUT_B1F_ITEM_2",
			"HS_ROCKET_HIDEOUT_B2F_ITEM_1",
			"HS_ROCKET_HIDEOUT_B2F_ITEM_2",
			"HS_ROCKET_HIDEOUT_B2F_ITEM_3",
			"HS_ROCKET_HIDEOUT_B2F_ITEM_4",
			"HS_ROCKET_HIDEOUT_B3F_ITEM_1",
			"HS_ROCKET_HIDEOUT_B3F_ITEM_2",
			"HS_ROCKET_HIDEOUT_B4F_GIOVANNI",
			"HS_ROCKET_HIDEOUT_B4F_ITEM_1",
			"HS_ROCKET_HIDEOUT_B4F_ITEM_2",
			"HS_ROCKET_HIDEOUT_B4F_ITEM_3",
			"HS_ROCKET_HIDEOUT_B4F_ITEM_4",
			"HS_ROCKET_HIDEOUT_B4F_ITEM_5",
			"HS_SILPH_CO_2F_1",
			"HS_SILPH_CO_2F_2",
			"HS_SILPH_CO_2F_3",
			"HS_SILPH_CO_2F_4",
			"HS_SILPH_CO_2F_5",
			"HS_SILPH_CO_3F_1",
			"HS_SILPH_CO_3F_2",
			"HS_SILPH_CO_3F_ITEM",
			"HS_SILPH_CO_4F_1",
			"HS_SILPH_CO_4F_2",
			"HS_SILPH_CO_4F_3",
			"HS_SILPH_CO_4F_ITEM_1",
			"HS_SILPH_CO_4F_ITEM_2",
			"HS_SILPH_CO_4F_ITEM_3",
			"HS_SILPH_CO_5F_1",
			"HS_SILPH_CO_5F_2",
			"HS_SILPH_CO_5F_3",
			"HS_SILPH_CO_5F_4",
			"HS_SILPH_CO_5F_ITEM_1",
			"HS_SILPH_CO_5F_ITEM_2",
			"HS_SILPH_CO_5F_ITEM_3",
			"HS_SILPH_CO_6F_1",
			"HS_SILPH_CO_6F_2",
			"HS_SILPH_CO_6F_3",
			"HS_SILPH_CO_6F_ITEM_1",
			"HS_SILPH_CO_6F_ITEM_2",
			"HS_SILPH_CO_7F_1",
			"HS_SILPH_CO_7F_2",
			"HS_SILPH_CO_7F_3",
			"HS_SILPH_CO_7F_4",
			"HS_SILPH_CO_7F_RIVAL",
			"HS_SILPH_CO_7F_ITEM_1",
			"HS_SILPH_CO_7F_ITEM_2",
			"HS_SILPH_CO_7F_8",
			"HS_SILPH_CO_8F_1",
			"HS_SILPH_CO_8F_2",
			"HS_SILPH_CO_8F_3",
			"HS_SILPH_CO_9F_1",
			"HS_SILPH_CO_9F_2",
			"HS_SILPH_CO_9F_3",
			"HS_SILPH_CO_10F_1",
			"HS_SILPH_CO_10F_2",
			"HS_SILPH_CO_10F_3",
			"HS_SILPH_CO_10F_ITEM_1",
			"HS_SILPH_CO_10F_ITEM_2",
			"HS_SILPH_CO_10F_ITEM_3",
			"HS_SILPH_CO_11F_1",
			"HS_SILPH_CO_11F_2",
			"HS_SILPH_CO_11F_3",
			"HS_UNUSED_MAP_F4_1",
			"HS_POKEMON_MANSION_2F_ITEM",
			"HS_POKEMON_MANSION_3F_ITEM_1",
			"HS_POKEMON_MANSION_3F_ITEM_2",
			"HS_POKEMON_MANSION_B1F_ITEM_1",
			"HS_POKEMON_MANSION_B1F_ITEM_2",
			"HS_POKEMON_MANSION_B1F_ITEM_3",
			"HS_POKEMON_MANSION_B1F_ITEM_4",
			"HS_POKEMON_MANSION_B1F_ITEM_5",
			"HS_SAFARI_ZONE_EAST_ITEM_1",
			"HS_SAFARI_ZONE_EAST_ITEM_2",
			"HS_SAFARI_ZONE_EAST_ITEM_3",
			"HS_SAFARI_ZONE_EAST_ITEM_4",
			"HS_SAFARI_ZONE_NORTH_ITEM_1",
			"HS_SAFARI_ZONE_NORTH_ITEM_2",
			"HS_SAFARI_ZONE_WEST_ITEM_1",
			"HS_SAFARI_ZONE_WEST_ITEM_2",
			"HS_SAFARI_ZONE_WEST_ITEM_3",
			"HS_SAFARI_ZONE_WEST_ITEM_4",
			"HS_SAFARI_ZONE_CENTER_ITEM",
			"HS_CERULEAN_CAVE_2F_ITEM_1",
			"HS_CERULEAN_CAVE_2F_ITEM_2",
			"HS_CERULEAN_CAVE_2F_ITEM_3",
			"HS_MEWTWO",
			"HS_CERULEAN_CAVE_B1F_ITEM_1",
			"HS_CERULEAN_CAVE_B1F_ITEM_2",
			"HS_VICTORY_ROAD_1F_ITEM_1",
			"HS_VICTORY_ROAD_1F_ITEM_2",
			"HS_CHAMPIONS_ROOM_OAK",
			"HS_SEAFOAM_ISLANDS_1F_BOULDER_1",
			"HS_SEAFOAM_ISLANDS_1F_BOULDER_2",
			"HS_SEAFOAM_ISLANDS_B1F_BOULDER_1",
			"HS_SEAFOAM_ISLANDS_B1F_BOULDER_2",
			"HS_SEAFOAM_ISLANDS_B2F_BOULDER_1",
			"HS_SEAFOAM_ISLANDS_B2F_BOULDER_2",
			"HS_SEAFOAM_ISLANDS_B3F_BOULDER_1",
			"HS_SEAFOAM_ISLANDS_B3F_BOULDER_2",
			"HS_SEAFOAM_ISLANDS_B3F_BOULDER_3",
			"HS_SEAFOAM_ISLANDS_B3F_BOULDER_4",
			"HS_SEAFOAM_ISLANDS_B4F_BOULDER_1",
			"HS_SEAFOAM_ISLANDS_B4F_BOULDER_2",
			"HS_ARTICUNO"

		};
	}

	namespace Pokemon
	{
		std::vector<std::string> physical{  "NORMAL",
											"FIGHTING",
											"FLYING",
											"POISON",
											"GROUND",
											"ROCK",
											"BIRD",
											"BUG",
											"GHOST" };

		std::vector<std::string> special{   "FIRE",
											"WATER",
											"GRASS",
											"ELECTRIC",
											"PSYCHIC_TYPE",
											"ICE",
											"DRAGON" };
	}
}