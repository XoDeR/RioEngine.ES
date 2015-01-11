#ifndef ComponentMapper_h__
#define ComponentMapper_h__

#include "RefBag.h"
#include "Entity.h"
#include "ComponentType.h"

namespace ES
{
	class World;

	// High performance component retrieval from entities. Use this wherever you
	// need to retrieve components from entities often and fast.
	template<typename Com>
	class ComponentMapper
	{
	public:
		// Fast but unsafe retrieval of a component for this entity.
		// No bounding checks, so this could throw an ArrayIndexOutOfBoundsExeption,
		// however in most scenarios you already know the entity possesses this component.
		Com* get(Entity& e)
		{
			return static_cast<Com*>(components->get(e.getId()));
		}

		// Fast and safe retrieval of a component for this entity.
		// If the entity does not have this component then nullptr is returned.
		Com* getSafe(Entity& e)
		{
			if (components.isIndexWithinBounds(e.getId()))
			{
				return static_cast<Com*>(components.get(e.getId()));
			}
			return nullptr;
		}

		// Checks if the entity has this type of component.
		bool has(Entity& e)
		{
			return getSafe(e) != nullptr;
		}

		// Returns a component mapper for this type of components.
		static ComponentMapper<Com>* getFor(World* world);
	private:
		ComponentMapper(World* world);
		ComponentType* type;
		unique_ptr<RefBag<Component>> components;
	};
}

#include "World.h"

namespace ES
{
	template<typename Com>
	ComponentMapper<Com>* ComponentMapper<Com>::getFor(World* world)
	{
		return new ComponentMapper<Com>(world);
	}

	template<typename Com>
	ComponentMapper<Com>::ComponentMapper(World* world)
	{
		this->type = &(ComponentType::getTypeFor<Com>());
		components = std::move(world->getComponentManager()->getComponentsByType(*type));
	}
}

#endif 