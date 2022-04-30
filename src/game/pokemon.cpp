#include "../sys/system.h"

Pokemon::Pokemon(PokemonData* p_data, int p_level)
{
	data = p_data;
	level = p_level;
	trainerId = game.player.trainerId;
	nickname = "";
	util::clearStats(&ev);
	generateIV();
	calculateStats();
	hp = maxHp();
	status = PokemonStatus::NONE;
	exp = calculateEXP(level);
}

int Pokemon::maxHp()
{
	return stats.hp;
}

void Pokemon::calculateStats()
{
	stats.hp = (((data->baseStats.hp + iv.hp) * 2 + int(ceil(sqrt(ev.hp))) / 4) * level) / 100 + level + 10;
	stats.attack = (((data->baseStats.attack + iv.attack) * 2 + int(ceil(sqrt(ev.attack))) / 4) * level) / 100 + 5;
	stats.defense = (((data->baseStats.defense + iv.defense) * 2 + int(ceil(sqrt(ev.defense))) / 4) * level) / 100 + 5;
	stats.speed = (((data->baseStats.speed + iv.speed) * 2 + int(ceil(sqrt(ev.speed))) / 4) * level) / 100 + 5;
	stats.special = (((data->baseStats.special + iv.special) * 2 + int(ceil(sqrt(ev.special))) / 4) * level) / 100 + 5;
}

void Pokemon::generateIV()
{
	iv.attack = util::random(0, 15);
	iv.defense = util::random(0, 15);
	iv.speed = util::random(0, 15);
	iv.special = util::random(0, 15);
	iv.hp = ((iv.attack & 1) << 3) | ((iv.defense & 1) << 2) | ((iv.speed & 1) << 1) | (iv.special & 1);
}

int Pokemon::calculateEXP(int level)
{
	int xp = 0;
	switch (data->growthRate)
	{
		case GrowthRate::GROWTH_FAST:
		{
			xp = (4 / 5) * util::ipow(level,3);
			break;
		}
		case GrowthRate::GROWTH_SLOW:
		{
			xp = (5 / 4) * util::ipow(level, 3);
			break;
		}
		case GrowthRate::GROWTH_MEDIUM_SLOW:
		{
			xp = (6 / 5) * util::ipow(level, 3) - 15*util::ipow(level, 2) + 100*level-140;
			break;
		}
		case GrowthRate::GROWTH_MEDIUM_FAST:
		{
			xp = util::ipow(level, 3);
			break;
		}
		case GrowthRate::GROWTH_SLIGHTLY_FAST:
		{
			xp = (3/4)*util::ipow(level, 3)+10 * util::ipow(level, 2)-30;
			break;
		}
		case GrowthRate::GROWTH_SLIGHTLY_SLOW:
		{
			xp = (3 / 4) * util::ipow(level, 3) + 20 * util::ipow(level, 2) - 70;
			break;
		}
		default:
		{
			sys.error("Invalid growthRate at Pokemon::calculateEXP");
			break;
		}
	}
	if (xp < 0)
		xp = 0;
	return xp;

}

