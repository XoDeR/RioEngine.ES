#include "EntityManager.h"
#include "Entity.h"
using std::move;

namespace ES
{
	EntityManager::EntityManager()
	{
	}

	EntityManager::~EntityManager()
	{
		entities.clear();
		disabledEntities.reset();
	}

	void EntityManager::added(Entity& e)
	{
		active++;
		addedCount++;
		entities.set(e.getId(), &e);
	}

	void EntityManager::enabled(Entity& e)
	{
		disabledEntities.reset(e.getId());
	}

	void EntityManager::disabled(Entity& e)
	{
		disabledEntities.set(e.getId());
	}

	void EntityManager::deleted(Entity& e)
	{
		entities.set(e.getId(), nullptr);
		disabledEntities.reset(e.getId());
		identifierPool.checkIn(e.getId());
		createdEntities.remove(&e);

		active--;
		deletedCount++;
	}

	// Active means the entity is being actively processed.
	bool EntityManager::isActive(int entityId)
	{
		return entities.get(entityId) != nullptr;
	}

	bool EntityManager::isEnabled(int entityId)
	{
		return !disabledEntities.test(entityId);
	}

	// Get how many entities are active in this world.
	int EntityManager::getActiveEntityCount()
	{
		return active;
	}

	// Get how many entities have been created in the world since start.
	// Note: A created entity may not have been added to the world, thus
	// created count is always equal or larger than added count.
	long EntityManager::getTotalCreated()
	{
		return createdCount;
	}

	// Get how many entities have been added to the world since start.
	long EntityManager::getTotalAdded()
	{
		return addedCount;
	}

	// Get how many entities have been deleted from the world since start.
	long EntityManager::getTotalDeleted()
	{
		return deletedCount;
	}

	void EntityManager::initialize()
	{
	}

	Entity* EntityManager::createEntityInstance()
	{
		unique_ptr<Entity> e(new Entity(world, identifierPool.checkOut()));
		createdEntities.add(move(e));
		createdCount++;
		return e.get();
	}

	// Get a entity with this id.
	Entity* EntityManager::getEntity(int entityId)
	{
		return entities.get(entityId);
	}
}