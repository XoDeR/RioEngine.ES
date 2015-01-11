#include "Manager.h"
#include "World.h"
#include "Entity.h"

namespace ES
{
	void Manager::added(Entity& e)
	{
	}

	void Manager::changed(Entity& e)
	{
	}

	void Manager::deleted(Entity& e)
	{
	}

	void Manager::disabled(Entity& e)
	{
	}

	void Manager::enabled(Entity& e)
	{
	}

	void Manager::setWorld(World* world)
	{
		this->world = world;
	}

	World* Manager::getWorld()
	{
		return world;
	}
}