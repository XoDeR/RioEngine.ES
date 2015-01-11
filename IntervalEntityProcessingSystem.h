#ifndef IntervalEntityProcessingSystem_h__
#define IntervalEntityProcessingSystem_h__

#include "IntervalEntitySystem.h"
#include "Bag.h"

namespace ES
{
	class Aspect;
	class Entity;

	// If you need to process entities at a certain interval then use this.
	// A typical usage would be to regenerate ammo or health at certain intervals, no need
	// to do that every game loop, but perhaps every 100 ms. or every second.
	class IntervalEntityProcessingSystem : public IntervalEntitySystem
	{
	public:
		IntervalEntityProcessingSystem(unique_ptr<Aspect> aspect, float interval);
	protected:
		virtual void process(Entity& e) = 0;
		void processEntities(RefBag<Entity>& entities);
	};
}

#endif 