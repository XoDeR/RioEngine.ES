#ifndef EntityManager_h__
#define EntityManager_h__

#include "Manager.h"
#include <bitset>
#include "Capacity.h"
#include "Bag.h"
#include "RefBag.h"
#include "IdentifierPool.h"

namespace ES
{
	class Entity;

	class EntityManager : public Manager
	{
	public:
		EntityManager();
		~EntityManager();
		void added(Entity& e);
		void enabled(Entity& e);
		void disabled(Entity& e);
		void deleted(Entity& e);
		bool isActive(int entityId);
		bool isEnabled(int entityId);
		int getActiveEntityCount();
		long getTotalCreated();
		long getTotalAdded();
		long getTotalDeleted();
		Entity* createEntityInstance();
		Entity* getEntity(int entityId);
	protected:
		void initialize();
	private:
		// owner
		Bag<Entity> createdEntities;
		RefBag<Entity> entities;
		std::bitset<CAPACITY> disabledEntities;

		int active;
		long addedCount;
		long createdCount;
		long deletedCount;

		IdentifierPool identifierPool;
	};
}

#endif 