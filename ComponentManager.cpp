#include "ComponentManager.h"
#include "Component.h"
#include "ComponentType.h"
#include "Entity.h"
#include "ESUtil.h"
using std::move;

namespace ES
{
	ComponentManager::ComponentManager()
	{
	}

	ComponentManager::~ComponentManager()
	{
		for (int i = 0; i < componentsByType.size(); ++i)
		{
			Bag<Component>* components = componentsByType.get(i);
			components->clear();
		}
		componentsByType.clear();
		deletedEntities.clear();
	}

	unique_ptr<RefBag<Component>> ComponentManager::getComponentsFor(Entity& e)
	{
		unique_ptr<RefBag<Component>> result(new RefBag<Component>());

		std::bitset<CAPACITY>& componentBits = e.getComponentBits();

		for (int i = findNextSetBit(componentBits, 0); i >= 0; i = findNextSetBit(componentBits, (i + 1)))
		{
			result->add(componentsByType.get(i)->get(e.getId()));
		}

		return move(result);
	}

	void ComponentManager::deleted(Entity& e)
	{
		deletedEntities.add(&e);
	}

	void ComponentManager::initialize()
	{
	}

	void ComponentManager::addComponent(Entity& e, ComponentType& type, unique_ptr<Component> component)
	{
		componentsByType.ensureCapacity(type.getIndex());

		Bag<Component>* components = componentsByType.get(type.getIndex());
		if (components == nullptr)
		{
			unique_ptr<Bag<Component>> componentsBagToAdd(new Bag<Component>());
			components = componentsBagToAdd.get();
			componentsByType.set(type.getIndex(), move(componentsBagToAdd));
		}

		components->set(e.getId(), move(component));

		e.getComponentBits().set(type.getIndex());
	}

	void ComponentManager::removeComponent(Entity& e, ComponentType& type)
	{
		if (e.getComponentBits().test(type.getIndex())) 
		{
			Bag<Component>* components = componentsByType.get(type.getIndex());
			freeComponent(type.getIndex(), components->get(e.getId()));
			components->set(e.getId(), nullptr);
			e.getComponentBits().reset(type.getIndex());
		}
	}

	unique_ptr<RefBag<Component>> ComponentManager::getComponentsByType(ComponentType& type)
	{
		unique_ptr<RefBag<Component>> result(new RefBag<Component>());

		Bag<Component>* components = componentsByType.get(type.getIndex());
		if (components == nullptr) 
		{
			unique_ptr<Bag<Component>> componentsBagToAdd(new Bag<Component>());
			components = componentsBagToAdd.get();
			componentsByType.set(type.getIndex(), move(componentsBagToAdd));
		}

		for (int i = 0; i < components->size(); ++i)
		{
			Component* com = components->get(i);
			if (com != nullptr)
			{
				result->add(com);
			}
		}

		return result;
	}

	Component* ComponentManager::getComponent(Entity& e, ComponentType& type)
	{
		Bag<Component>* components = componentsByType.get(type.getIndex());
		if (components != nullptr) 
		{
			return components->get(e.getId());
		}
		return nullptr;
	}

	// Override this to get notified if a component will be removed.
	void ComponentManager::freeComponent(int typeId, Component* component) 
	{
	
	}

	void ComponentManager::clean()
	{
		if (deletedEntities.size() > 0)
		{
			for (int i = 0; deletedEntities.size() > i; i++)
			{
				removeComponentsOfEntity(*deletedEntities.get(i));
			}
			deletedEntities.clear();
		}
	}

	void ComponentManager::removeComponentsOfEntity(Entity& e)
	{
		std::bitset<CAPACITY>& componentBits = e.getComponentBits();
		for (int i = findNextSetBit(componentBits, 0); i >= 0; i = findNextSetBit(componentBits, (i + 1)))
		{
			Bag<Component>* components = componentsByType.get(i);
			freeComponent(i, components->get(e.getId()));
			components->set(e.getId(), nullptr);
		}
		componentBits.reset();
	}

	unique_ptr<RefBag<Component>> ComponentManager::getComponentsByIndex(int index)
	{
		unique_ptr<RefBag<Component>> result(new RefBag<Component>());
		Bag<Component>* components = componentsByType.get(index);
		for (int i = 0; i < components->size(); ++i)
		{
			result->add(components->get(i));
		}
		return result;
	}

}