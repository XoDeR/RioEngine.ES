#ifndef Manager_h__
#define Manager_h__

#include "EntityObserver.h"

namespace ES
{
	class Entity;
	class World;

	class Manager : public EntityObserver
	{
	public:
		void added(Entity& e);
		void changed(Entity& e);
		void deleted(Entity& e);
		void disabled(Entity& e);
		void enabled(Entity& e);
		virtual void initialize() = 0;
		void setWorld(World* world);
		World* getWorld();
	protected:
		World* world;
	};
}

#endif 