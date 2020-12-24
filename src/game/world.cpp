#include "../sys/system.h"


void World::set_active(std::string HSid, bool flag)
{
	Object *obj = res.getObject(HSid);
	obj->active = flag;
}

void World::on_map_change()
{
	for (auto it : game.world.currentMap->objects)
	{
		it->init();
	}
}