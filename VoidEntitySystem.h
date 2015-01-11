#ifndef VoidEntitySystem_h__
#define VoidEntitySystem_h__

#include "Aspect.h"
#include "Entity.h"
#include "EntitySystem.h"
#include "Bag.h"
#include <memory>
using std::unique_ptr;

namespace ES
{
	// This system has an empty aspect so it processes no entities, but it still gets invoked.
	// You can use this system if you need to execute some game logic and not have to concern
	// yourself about aspects or entities.
	class VoidEntitySystem : public EntitySystem
	{
	public:
		VoidEntitySystem();
	protected:
		void processEntities(RefBag<Entity>& entities);
		virtual void processSystem() = 0;
		bool checkProcessing();
	};
}

#endif 