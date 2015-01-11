#include "DelayedEntityProcessingSystem.h"
#include "Aspect.h"
#include "World.h"

namespace ES
{
	DelayedEntityProcessingSystem::DelayedEntityProcessingSystem(unique_ptr<Aspect> aspect)
		: EntitySystem(std::move(aspect))
	{
	}

	void DelayedEntityProcessingSystem::restart(float delay)
	{
		this->delay = delay;
		this->acc = 0;
		running = true;
	}

	void DelayedEntityProcessingSystem::offerDelay(float delay)
	{
		if (!running || delay < getRemainingTimeUntilProcessing())
		{
			restart(delay);
		}
	}

	float DelayedEntityProcessingSystem::getInitialTimeDelay()
	{
		return delay;
	}

	float DelayedEntityProcessingSystem::getRemainingTimeUntilProcessing()
	{
		if (running)
		{
			return delay - acc;
		}
		return 0;
	}

	bool DelayedEntityProcessingSystem::isRunning()
	{
		return running;
	}

	void DelayedEntityProcessingSystem::stop()
	{
		this->running = false;
		this->acc = 0;
	}

	void DelayedEntityProcessingSystem::processEntities(RefBag<Entity>& entities)
	{
		for (int i = 0, s = entities.size(); s > i; i++)
		{
			Entity* entity = entities.get(i);
			processDelta(*entity, acc);
			float remaining = getRemainingDelay(*entity);
			if (remaining <= 0) 
			{
				processExpired(*entity);
			}
			else 
			{
				offerDelay(remaining);
			}
		}
		stop();
	}

	void DelayedEntityProcessingSystem::inserted(Entity& e)
	{
		float delay = getRemainingDelay(e);
		if (delay > 0)
		{
			offerDelay(delay);
		}
	}

	bool DelayedEntityProcessingSystem::checkProcessing()
	{
		if (running)
		{
			acc += world->getDelta();

			if (acc >= delay)
			{
				return true;
			}
		}
		return false;
	}
}