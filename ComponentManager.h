#ifndef ComponentManager_h__
#define ComponentManager_h__

#include "Manager.h"
#include <bitset>
#include "Capacity.h"
#include "Bag.h"
#include "RefBag.h"

namespace ES
{
	class Component;
	class ComponentType;
	class Entity;

	class ComponentManager : public Manager
	{
	public:
		ComponentManager();
		~ComponentManager();
		unique_ptr<RefBag<Component>> getComponentsFor(Entity& e);
		void deleted(Entity& e);
		void addComponent(Entity& e, ComponentType& type, unique_ptr<Component> component);
		void removeComponent(Entity& e, ComponentType& type);
		Component* getComponent(Entity& e, ComponentType& type);
		void clean();
		unique_ptr<RefBag<Component>> getComponentsByType(ComponentType& type);
	protected:
		void initialize();
		
		// Override this to get notified if a component will be removed.
		void freeComponent(int typeId, Component* component);
	private:
		// owner
		Bag<Bag<Component>> componentsByType;
		// not owner
		RefBag<Entity> deletedEntities;
		void removeComponentsOfEntity(Entity& e);
		unique_ptr<RefBag<Component>> getComponentsByIndex(int index);
	};
}


#endif 