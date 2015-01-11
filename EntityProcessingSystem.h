#ifndef EntityProcessingSystem_h__
#define EntityProcessingSystem_h__

#include "Aspect.h"
#include "Entity.h"
#include "EntitySystem.h"
#include "Bag.h"
#include "RefBag.h"
#include <memory>
using std::unique_ptr;

namespace ES
{
	// A typical entity system. Use this when you need to process entities possessing the
	// provided component types.
	class EntityProcessingSystem : public EntitySystem
	{
	public:
		explicit EntityProcessingSystem(unique_ptr<Aspect> aspect);
	protected:
		virtual void process(Entity& e) = 0;
		void processEntities(RefBag<Entity>& entities);
		bool checkProcessing();
	};
}

#endif 