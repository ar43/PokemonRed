#include "../sys/system.h"


Npc::Npc()
{
	init();
}


void Npc::init()
{
	waiting = true;
	displacement.x = 0;
	displacement.y = 0;
}