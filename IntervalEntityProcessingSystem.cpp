#include "IntervalEntityProcessingSystem.h"
#include "Aspect.h"
#include "Entity.h"

namespace ES
{
	IntervalEntityProcessingSystem::IntervalEntityProcessingSystem(unique_ptr<Aspect> aspect, float interval)
		: IntervalEntitySystem(std::move(aspect), interval)
	{

	}

	void IntervalEntityProcessingSystem::processEntities(RefBag<Entity>& entities)
	{
		for (int i = 0, s = entities.size(); s > i; i++)
		{
			process(*entities.get(i));
		}
	}

}