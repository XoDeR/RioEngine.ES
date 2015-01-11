#include "IntervalEntitySystem.h"
#include "Aspect.h"
#include "World.h"

namespace ES
{
	IntervalEntitySystem::IntervalEntitySystem(unique_ptr<Aspect> aspect, float interval)
		: EntitySystem(std::move(aspect))
		, interval(interval)
	{
	}

	bool IntervalEntitySystem::checkProcessing()
	{
		acc += world->getDelta();
		if (acc >= interval)
		{
			acc -= interval;
			return true;
		}
		return false;
	}
}