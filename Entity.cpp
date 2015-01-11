#include "Entity.h"
#include "World.h"
#include "EntitySystem.h"
#include "EntityManager.h"
#include "ComponentManager.h"
using std::move;

namespace ES
{
	int Entity::getId()
	{
		return id;
	}

	std::string Entity::toString()
	{
		return "Entity[" + std::to_string(id) + "]";
	}

	bool Entity::isInSystem(EntitySystem* system)
	{
		return isInSystem(system->getSystemId());
	}

	bool Entity::isInSystem(int systemId)
	{
		return systemBits.test(systemId);
	}

	bool Entity::hasComponent(ComponentType& type)
	{
		return componentBits.test(type.getIndex());
	}

	Entity* Entity::addComponent(unique_ptr<Component> component)
	{
		addComponent(move(component), ComponentType::getTypeFor<Component>());
		return this;
	}

	Entity* Entity::addComponent(unique_ptr<Component> component, ComponentType& type)
	{
		componentManager->addComponent(*this, type, move(component));
		return this;
	}

	Entity* Entity::removeComponent(Component* component)
	{
		removeComponent(ComponentType::getTypeFor<Component>());
		return this;
	}

	Entity* Entity::removeComponent(ComponentType& type)
	{
		componentManager->removeComponent(*this, type);
		return this;
	}

	bool Entity::isActive()
	{
		return entityManager->isActive(id);
	}

	bool Entity::isEnabled()
	{
		return entityManager->isEnabled(id);
	}

	Component* Entity::getComponent(ComponentType& type)
	{
		return componentManager->getComponent(*this, type);
	}

	unique_ptr<RefBag<Component>> Entity::getComponents()
	{
		return componentManager->getComponentsFor(*this);
	}

	void Entity::addToWorld()
	{
		world->addEntity(this);
	}

	void Entity::changedInWorld()
	{
		world->changedEntity(this);
	}

	void Entity::deleteFromWorld()
	{
		world->deleteEntity(this);
	}

	void Entity::enable()
	{
		world->enable(this);
	}

	void Entity::disable()
	{
		world->disable(this);
	}

	long int Entity::getUuid()
	{
		return uuid;
	}

	void Entity::setUuid(long int uuid)
	{
		if (uuid == -1)
		{
			return;
		}
		this->uuid = uuid;
	}

	World* Entity::getWorld()
	{
		return world;
	}

	std::bitset<CAPACITY>& Entity::getComponentBits()
	{
		return componentBits;
	}

	std::bitset<CAPACITY>& Entity::getSystemBits()
	{
		return systemBits;
	}

	Entity::Entity(World* world, int id)
	{
		this->world = world;
		this->id = id;
		this->entityManager = world->getEntityManager();
		this->componentManager = world->getComponentManager();
		systemBits.reset();
		componentBits.reset();

		reset();
	}

	void Entity::reset()
	{
		systemBits.reset();
		componentBits.reset();

		static int UUID = 0;
		uuid = UUID++;
	}

}