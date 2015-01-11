#include "World.h"
#include "ComponentType.h"
#include "SystemIndexManager.h"
#include "EntityObserver.h"
#include "Performer.h"
#include "Entity.h"
#include "EntityManager.h"
#include "ComponentManager.h"
#include "GroupManager.h"

namespace ES
{
	World::World()
		: addedPerformer(new AddedPerformer())
		, changedPerformer(new ChangedPerformer())
		, disablePerformer(new DisablePerformer())
		, enablePerformer(new EnablePerformer())
		, deletedPerformer(new DeletedPerformer())
	{
		unique_ptr<ComponentManager> componentManager(new ComponentManager());
		unique_ptr<EntityManager> entityManager(new EntityManager());
		
		this->componentManager = componentManager.get();
		setManager<ComponentManager>(move(componentManager));

		this->entityManager = entityManager.get();
		setManager<EntityManager>(move(entityManager));

		unique_ptr<GroupManager> groupManager(new GroupManager());
		setManager<GroupManager>(move(groupManager));
	}


	World::~World()
	{
		ComponentType::deleteComponentTypes();
		SystemIndexManager::deleteSystemIndices();
		
		systems.clear();
		systemsBag.clear();

		managers.clear();
		managersBag.clear();
	}

	void World::initialize()
	{
		for (int i = 0; i < managersBag.size(); i++)
		{
			managersBag.get(i)->initialize();
		}

		for (int i = 0; i < systemsBag.size(); i++)
		{
			systemsBag.get(i)->initialize();
		}
	}

	EntityManager* World::getEntityManager()
	{
		return entityManager;
	}

	ComponentManager* World::getComponentManager()
	{
		return componentManager;
	}

	void World::deleteManager(Manager* manager)
	{
		for (auto it = managers.begin(); it != managers.end(); ++it)
		{
			if (it->second == manager)
			{
				managers.erase(it);
			}
		}
		managersBag.remove(manager);
	}

	float World::getDelta()
	{
		return delta;
	}

	void World::setDelta(float delta)
	{
		this->delta = delta;
	}

	void World::addEntity(Entity* e)
	{
		addedList.add(e);
	}

	void World::changedEntity(Entity* e)
	{
		changedList.add(e);
	}

	void World::deleteEntity(Entity* e)
	{
		if (!deletedList.contains(e))
		{
			deletedList.add(e);
		}
	}

	void World::enable(Entity* e)
	{
		enabledList.add(e);
	}

	void World::disable(Entity* e)
	{
		disableList.add(e);
	}

	Entity* World::createEntity()
	{
		return entityManager->createEntityInstance();
	}

	Entity* World::createEntity(long int uuid)
	{
		Entity* e = entityManager->createEntityInstance();
		e->setUuid(uuid);
		return e;
	}

	Entity* World::getEntity(int entityId)
	{
		return entityManager->getEntity(entityId);
	}

	unique_ptr<RefBag<EntitySystem>> World::getSystems()
	{
		unique_ptr<RefBag<EntitySystem>> result(new RefBag<EntitySystem>());
		for (int i = 0; i < systemsBag.size(); ++i)
		{
			EntitySystem* entitySystem = systemsBag.get(i);
			if (entitySystem != nullptr)
			{
				result->add(entitySystem);
			}
		}
		return result;
	}

	void World::deleteSystem(EntitySystem* system)
	{
		systems.erase(std::type_index(typeid(system)));
		systemsBag.remove(system);
		delete system;
	}

	void World::process()
	{
		check(addedList, addedPerformer.get());

		check(changedList, changedPerformer.get());

		check(disableList, disablePerformer.get());

		check(enabledList, enablePerformer.get());

		check(deletedList, deletedPerformer.get());

		componentManager->clean();

		for (int i = 0; systemsBag.size() > i; i++)
		{
			EntitySystem* system = systemsBag.get(i);
			if (!system->isPassive())
			{
				system->process();
			}
		}
	}

	void World::shrink()
	{
		addedList.shrink();
		changedList.shrink();
		deletedList.shrink();
		enabledList.shrink();
		disableList.shrink();
	}

	void World::notifySystems(Performer* performer, Entity& e)
	{
		for (int i = 0, s = systemsBag.size(); s > i; i++)
		{
			performer->perform(systemsBag.get(i), e);
		}
	}

	void World::notifyManagers(Performer* performer, Entity& e)
	{
		for (int a = 0; managersBag.size() > a; a++)
		{
			performer->perform(managersBag.get(a), e);
		}
	}

	void World::check(RefBag<Entity>& entities, Performer* performer)
	{
		if (!entities.isEmpty())
		{
			for (int i = 0; entities.size() > i; i++)
			{
				Entity& e = *entities.get(i);
				notifyManagers(performer, e);
				notifySystems(performer, e);
			}
			entities.clear();
		}
	}
}

