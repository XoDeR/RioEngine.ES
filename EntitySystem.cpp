#include "EntitySystem.h"
#include "Aspect.h"
#include "Entity.h"
#include "SystemIndexManager.h"
#include "World.h"
#include <typeinfo>
#include <typeindex>

namespace ES
{
	EntitySystem::EntitySystem(unique_ptr<Aspect> aspect)
		: aspect(std::move(aspect))
	{
		std::bitset<CAPACITY> allSet = aspect->getAllSet();
		std::bitset<CAPACITY> oneSet = aspect->getOneSet();
		systemIndex = SystemIndexManager::getIndexFor(std::type_index(typeid(this)));
		dummy = allSet.none() && oneSet.none(); // This system can't possibly be interested in any entity, so it must be "dummy"
	}

	EntitySystem::~EntitySystem()
	{

	}

	void EntitySystem::process()
	{
		if (checkProcessing())
		{
			begin();
			processEntities(actives);
			end();
		}
	}

	void EntitySystem::added(Entity& e)
	{
		check(e);
	}

	void EntitySystem::changed(Entity& e)
	{
		check(e);
	}

	void EntitySystem::deleted(Entity& e)
	{
		if (e.getSystemBits().test(systemIndex))
		{
			removeFromSystem(e);
		}
	}

	void EntitySystem::disabled(Entity& e)
	{
		if (e.getSystemBits().test(systemIndex))
		{
			removeFromSystem(e);
		}
	}

	void EntitySystem::enabled(Entity& e)
	{
		check(e);
	}

	RefBag<Entity>* EntitySystem::getActives()
	{
		return &actives;
	}

	int EntitySystem::getSystemId()
	{
		return systemIndex;
	}

	void EntitySystem::begin()
	{
	}


	void EntitySystem::setWorld(World* world)
	{
		this->world = world;
	}

	bool EntitySystem::isPassive()
	{
		return passive;
	}

	void EntitySystem::setPassive(bool passive)
	{
		this->passive = passive;
	}

	// Called after the processing of entities ends.
	void EntitySystem::end()
	{
	}

	void EntitySystem::initialize() {};

	// Called if the system has received a entity it is interested in, e.g. created or a component was added to it.
	void EntitySystem::inserted(Entity& e) {};

	// Called if a entity was removed from this system, e.g. deleted or had one of it's components removed.
	void EntitySystem::removed(Entity& e) {};

	// Will check if the entity is of interest to this system.
	void EntitySystem::check(Entity& e)
	{
		if (dummy)
		{
			return;
		}

		bool contains = e.getSystemBits().test(systemIndex);
		bool interested = aspect->hasAspect(e);

		if (interested && !contains)
		{
			insertToSystem(e);
		}
		else if (!interested && contains)
		{
			removeFromSystem(e);
		}
	}

	void EntitySystem::removeFromSystem(Entity& e)
	{
		actives.remove(&e);
		e.getSystemBits().reset(systemIndex);
		removed(e);
	}

	void EntitySystem::insertToSystem(Entity& e)
	{
		actives.add(&e);
		e.getSystemBits().set(systemIndex);
		inserted(e);
	}
}