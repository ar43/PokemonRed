#include "../sys/system.h"


void World::set_active(std::string HSid, bool flag)
{
	Object *obj = res.getObject(HSid);
	obj->active = flag;
}