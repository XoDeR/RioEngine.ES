#ifndef EntitySystem_h__
#define EntitySystem_h__

#include "EntityObserver.h"
#include "RefBag.h"
#include <bitset>
#include "Capacity.h"
#include <memory>
using std::unique_ptr;

namespace ES
{
	class Aspect;
	class World;

	// The most raw entity system. It should not typically be used, but you can create your own
	// entity system handling by extending this. It is recommended that you use the other provided
	// entity system implementations.
	class EntitySystem : public EntityObserver
	{
	public:
		// Creates an entity system that uses the specified aspect as a matcher against entities.
		explicit EntitySystem(unique_ptr<Aspect> aspect);
		virtual ~EntitySystem();
		void process();
		void added(Entity& e);
		void changed(Entity& e);
		void deleted(Entity& e);
		void disabled(Entity& e);
		void enabled(Entity& e);
		RefBag<Entity>* getActives();
		// Get the index of this system.
		// The index is determined by the class of an EntitySystem.
		int getSystemId();
		// Override to implement code that gets executed when systems are initialized.
		void initialize();
		bool isPassive();
	protected:
		// Called before processing of entities begins.
		void begin();
		// Called after the processing of entities ends.
		void end();
		void setWorld(World* world);
		void setPassive(bool passive);
		// Any implementing entity system must implement this method and the logic
		// to process the given entities of the system.
		virtual void processEntities(RefBag<Entity>& entities) = 0;

		// return true if the system should be processed, false if not.
		virtual bool checkProcessing() = 0;

		// Called if the system has received a entity it is interested in, e.g. created or a component was added to it.
		void inserted(Entity& e);

		// Called if a entity was removed from this system, e.g. deleted or had one of it's components removed.
		void removed(Entity& e);

		// Will check if the entity is of interest to this system.
		void check(Entity& e);

		World* world;
		RefBag<Entity> actives;
	private:
		void removeFromSystem(Entity& e);
		void insertToSystem(Entity& e);

		int systemIndex;
		unique_ptr<Aspect> aspect;
		bool passive;
		bool dummy;
	};
}

#endif 