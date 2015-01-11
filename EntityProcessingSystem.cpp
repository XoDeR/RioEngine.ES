#include "EntityProcessingSystem.h"

namespace ES
{
	EntityProcessingSystem::EntityProcessingSystem(unique_ptr<Aspect> aspect)
		: EntitySystem(std::move(aspect))
	{
	}

	void EntityProcessingSystem::processEntities(RefBag<Entity>& entities)
	{
		for (int i = 0, s = entities.size(); s > i; i++)
		{
			process(*entities.get(i));
		}
	}

	bool EntityProcessingSystem::checkProcessing()
	{
		return true;
	}
}