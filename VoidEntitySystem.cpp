#include "VoidEntitySystem.h"

namespace ES
{
	VoidEntitySystem::VoidEntitySystem() : EntitySystem(std::move(Aspect::getEmpty()))
	{

	}

	void VoidEntitySystem::processEntities(RefBag<Entity>& entities)
	{
		processSystem();
	}

	bool VoidEntitySystem::checkProcessing()
	{
		return true;
	}
}