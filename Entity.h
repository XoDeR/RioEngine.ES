#ifndef Entity_h__
#define Entity_h__

#include <bitset>
#include <string>
#include "Capacity.h"
#include "Component.h"
#include "ComponentType.h"
#include "Bag.h"
#include "RefBag.h"

namespace ES
{
	class World;
	class EntitySystem;
	class EntityManager;
	class ComponentManager;

	// The entity class. Cannot be instantiated outside the framework.
	// New entities should be created using World.
	class Entity
	{
	public:
		Entity(World* world, int id);
		// The internal id for this entity within the framework. No other entity
		// will have the same ID, but ID's are however reused so another entity may
		// acquire this ID if the previous entity was deleted.
		int getId();
		std::string toString();
		bool isInSystem(EntitySystem* system);
		// Checks if the entity is processed by a specific entity-system.
		bool isInSystem(int systemId);

		template<typename Com>
		bool hasComponent() 
		{
			return hasComponent(ComponentTypeManager::getTypeFor<Com>());
		}

		bool hasComponent(ComponentType& type);
		Entity* addComponent(unique_ptr<Component> component);

		// Faster adding of components into the entity. Not necessary to use this, but
		// in some cases you might need the extra performance.
		Entity* addComponent(unique_ptr<Component> component, ComponentType& type);

		Entity* removeComponent(Component* component);

		// Faster removal of components from a entity.
		Entity* removeComponent(ComponentType& type);

		// Remove component by its type.
		template<typename Com>
		Entity* removeComponent() 
		{
			removeComponent(ComponentType::getTypeFor<Com>());
			return this;
		}

		// Checks if the entity has been added to the world and has not been deleted from it.
		// If the entity has been disabled this will still return true.
		bool isActive();

		// Will check if the entity is enabled in the world.
		// By default all entities that are added to world are enabled,
		// this will only return false if an entity has been explicitly disabled.
		bool isEnabled();

		// This is the preferred method to use when retrieving a component from a
		// entity. It will provide good performance.
		// But the recommended way to retrieve components from an entity is using
		// the ComponentMapper.
		Component* getComponent(ComponentType& type);

		// Slower retrieval of components from this entity. Minimize usage of this,
		// but is fine to use e.g. when creating new entities and setting data in
		// components.
		template<typename Com>
		Com* getComponent()
		{
			return static_cast<Com*>(getComponent(ComponentType::getTypeFor<c>()));
		}

		// Returns a bag of all components this entity has.
		// You need to reset the bag yourself if you intend to fill it more than once.
		unique_ptr<RefBag<Component>> getComponents();

		// Refresh all changes to components for this entity. After adding or
		// removing components, you must call this method. It will update all
		// relevant systems. It is typical to call this after adding components to a
		// newly created entity.
		void addToWorld();

		// This entity has changed, a component added or deleted.
		void changedInWorld();

		void deleteFromWorld();

		// (Re)enable the entity in the world, after it having being disabled.
		// Won't do anything unless it was already disabled.
		void enable();

		// Disable the entity from being processed. Won't delete it, it will
		// continue to exist but won't get processed.
		void disable();

		// Get the UUID for this entity.
		// This UUID is unique per entity (re-used entities get a new UUID).
		long int getUuid();

		// Set the UUID for this entity.
		void setUuid(long int uuid);

		World* getWorld();

		std::bitset<CAPACITY>& getComponentBits();

		std::bitset<CAPACITY>& getSystemBits();

	protected:
		

		// Make entity ready for re-use.
		// Will generate a new uuid for the entity.
		void reset();
	private:
		long int uuid;

		int id;
		std::bitset<CAPACITY> componentBits;
		std::bitset<CAPACITY> systemBits;

		World* world;
		EntityManager* entityManager;
		ComponentManager* componentManager;
	};

}


#endif 