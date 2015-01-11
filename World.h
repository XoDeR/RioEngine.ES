#ifndef World_h__
#define World_h__

#include "EntityManager.h"
#include "ComponentManager.h"
#include "Bag.h"
#include <typeinfo>
#include <typeindex>
#include <unordered_map>
#include <memory>
using std::unique_ptr;

namespace ES
{
	class EntityObserver;
	class Entity;
	class Manager;
	class EntityManager;
	class ComponentManager;
	class EntitySystem;
	template<typename Com>
	class ComponentMapper;
	class Performer;

	// The primary instance for the framework. It contains all the managers.
	// You must use this to create, delete and retrieve entities.
	// It is also important to set the delta each game loop iteration, and initialize before game loop.
	class World
	{
	public:
		float delta;
		World();
		~World();
		// Makes sure all managers systems are initialized in the order they were added.
		void initialize();
		EntityManager* getEntityManager();
		ComponentManager* getComponentManager();

		// Add a manager into this world. It can be retrieved later.
		// World will notify this manager of changes to entity.
		template<typename Man>
		Man* setManager(unique_ptr<Man> manager);
		// Returns a manager of the specified type.
		template<typename Man>
		Man* getManager();
		// Deletes the manager from this world.
		void deleteManager(Manager* manager);

		// Time since last game loop.
		float getDelta();
		// You must specify the delta for the game here.
		void setDelta(float delta);
		// Adds a entity to this world.
		void addEntity(Entity* e);

		// Ensure all systems are notified of changes to this entity.
		// If you're adding a component to an entity after it's been
		// added to the world, then you need to invoke this method.
		void changedEntity(Entity* e);

		// Delete the entity from the world.
		void deleteEntity(Entity* e);

		// (Re)enable the entity in the world, after it having being disabled.
		// Won't do anything unless it was already disabled.
		void enable(Entity* e);

		// Disable the entity from being processed. Won't delete it, it will
		// continue to exist but won't get processed.
		void disable(Entity* e);

		Entity* createEntity();
		Entity* createEntity(long int uuid);

		Entity* getEntity(int entityId);

		unique_ptr<RefBag<EntitySystem>> getSystems();

		template<typename Sys>
		Sys* setSystem(Sys* system);

		template<typename Sys>
		Sys* setSystem(Sys* system, bool passive);

		void deleteSystem(EntitySystem* system);

		template<typename Sys>
		Sys* getSystem(Sys* type);

		// Process all non-passive systems.
		void process();

		// Retrieves a ComponentMapper instance for fast retrieval of components from entities.
		template<typename Com>
		ComponentMapper<Com>* getMapper();

		// Reduces the sizes of the backing arrays.
		void shrink();
	private:
		EntityManager* entityManager;
		ComponentManager* componentManager;

		RefBag<Entity> addedList;
		RefBag<Entity> changedList;
		RefBag<Entity> deletedList;
		RefBag<Entity> enabledList;
		RefBag<Entity> disableList;

		unique_ptr<Performer> addedPerformer;
		unique_ptr<Performer> changedPerformer;
		unique_ptr<Performer> deletedPerformer;
		unique_ptr<Performer> enablePerformer;
		unique_ptr<Performer> disablePerformer;
		
		// owner
		Bag<Manager> managersBag;
		std::unordered_map<std::type_index, Manager*> managers;

		// owner
		Bag<EntitySystem> systemsBag;
		std::unordered_map<std::type_index, EntitySystem*> systems;

		void notifySystems(Performer* performer, Entity& e);
		void notifyManagers(Performer* performer, Entity& e);
		void check(RefBag<Entity>& entities, Performer* performer);
	};
}

#include "ComponentMapper.h"
#include "Manager.h"
#include "EntitySystem.h"

namespace ES
{
	template<typename Com>
	ComponentMapper<Com>* World::getMapper()
	{
		return ComponentMapper<Com>::getFor<Com>(this);
	}

	// Add a manager into this world. It can be retrieved later.
	// World will notify this manager of changes to entity.
	template<typename Man>
	Man* World::setManager(unique_ptr<Man> manager)
	{
		Man* result = nullptr;

		manager->setWorld(this);
		managers[std::type_index(typeid(Man))] = manager.get();
		result = manager.get();
		managersBag.add(move(manager));

		return result;
	}

	// Returns a manager of the specified type.
	template<typename Man>
	Man* World::getManager()
	{
		return static_cast<Man*>(managers[std::type_index(typeid(Man))]);
	}

	template<typename Sys>
	Sys* World::setSystem(Sys* system)
	{
		return static_cast<Sys*>(setSystem<Sys>(false));
	}

	template<typename Sys>
	Sys* World::setSystem(Sys* system, bool passive)
	{
		system->setWorld(this);
		system->setPassive(passive);

		systems[std::type_index(typeid(Sys))] = system;
		systemsBag.add(system);

		return system;
	}

	template<typename Sys>
	Sys* World::getSystem(Sys* type)
	{
		return static_cast<Sys*>(systems[std::type_index(typeid(Sys))]);
	}
}

#endif 