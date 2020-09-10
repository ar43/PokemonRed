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
}