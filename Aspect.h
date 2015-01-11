#ifndef Aspect_h__
#define Aspect_h__

#include <bitset>
#include "Capacity.h"
#include "ComponentType.h"
#include <memory>
using std::unique_ptr;

namespace ES
{
	class Entity;

	// An Aspect is used by systems as a matcher against entities, to check if a system is
	// interested in an entity. Aspects define what sort of component types an entity must
	// possess, or not possess.

	// This creates an aspect where an entity must possess A and B and C:
	// Aspect.getAspectForAll(A.class, B.class, C.class)

	// This creates an aspect where an entity must possess A and B and C, but must not possess U or V.
	// Aspect.getAspectForAll(A.class, B.class, C.class).exclude(U.class, V.class)
	// This creates an aspect where an entity must possess A and B and C, but must not possess U or V, but must possess one of X or Y or Z.
	// Aspect.getAspectForAll(A.class, B.class, C.class).exclude(U.class, V.class).one(X.class, Y.class, Z.class)

	// You can create and compose aspects in many ways:
	// Aspect.getEmpty().one(X.class, Y.class, Z.class).all(A.class, B.class, C.class).exclude(U.class, V.class)
	// is the same as:
	// Aspect.getAspectForAll(A.class, B.class, C.class).exclude(U.class, V.class).one(X.class, Y.class, Z.class)

	class Aspect
	{
	private:
		template<typename...>
		struct typelist {};
	public:
		template<typename...components>
		Aspect* all()
		{
			return allAux(typelist<components...>());
		}

		template<typename...components>
		Aspect* all(typelist<components...>)
		{
			return allAux(typelist<components...>());
		}

		template<typename...components>
		Aspect* exclude()
		{
			return excludeAux(typelist<components...>());
		}

		template<typename...components>
		Aspect* one()
		{
			return oneAux(typelist<components...>());
		}

		// Creates an aspect where an entity must possess all of the specified component types.
		template<typename...components>
		static unique_ptr<Aspect> getAspectFor()
		{
			return getAspectForAll(typelist<components...>());
		}

		//Creates an aspect where an entity must possess all of the specified component types.
		template<typename...components>
		static unique_ptr<Aspect> getAspectForAll(typelist<components...>)
		{
			unique_ptr<Aspect> aspect(new Aspect());
			aspect->all(typelist<components...>());
			return aspect;
		}

		// Creates an aspect where an entity must possess one of the specified component types.
		template<typename...components>
		static unique_ptr<Aspect> getAspectForOne()
		{
			unique_ptr<Aspect> aspect(new Aspect());
			aspect->one<typename...components>();
			return aspect;
		}

		// Creates and returns an empty aspect. This can be used if you want a system that processes no entities, but
		// still gets invoked. Typical usages is when you need to create special purpose systems for debug rendering,
		// like rendering FPS, how many entities are active in the world, etc.
		//
		// You can also use the all, one and exclude methods on this aspect, so if you wanted to create a system that
		// processes only entities possessing just one of the components A or B or C, then you can do:
		// Aspect.getEmpty().one(A,B,C);
		static unique_ptr<Aspect> getEmpty();
		// Checks if an entity has this aspect.
		bool hasAspect(Entity& e);
		std::bitset<CAPACITY>& getAllSet();
		std::bitset<CAPACITY>& getExclusionSet();
		std::bitset<CAPACITY>& getOneSet();
		~Aspect();
	private:
		// Returns an aspect where an entity must possess all of the specified component types.
		template<typename component, typename ... Rest>
		Aspect* allAux(typelist<component, Rest...>)
		{
			allSet.set(ComponentType::getIndexFor<component>());
			return all(typelist<Rest...>());
		}

		Aspect* allAux(typelist<>)
		{
			return this;
		}

		// Excludes all of the specified component types from the aspect. A system will not be
		// interested in an entity that possesses one of the specified exclusion component types.
		template<typename component, typename ... Rest>
		Aspect* excludeAux(typelist<component, Rest...>)
		{
			exclusionSet.set(ComponentType::getIndexFor(component));
			return exclude(typelist<Rest...>());
		}

		Aspect* excludeAux(typelist<>)
		{
			return this;
		}

		// Returns an aspect where an entity must possess one of the specified component types.
		template<typename component, typename ... Rest>
		Aspect* oneAux(typelist<component, Rest...>)
		{
			oneSet.set(ComponentType::getIndexFor(component));
			return one(typelist<Rest...>());
		}

		Aspect* oneAux(typelist<>)
		{
			return this;
		}

		std::bitset<CAPACITY> allSet;
		std::bitset<CAPACITY> exclusionSet;
		std::bitset<CAPACITY> oneSet;

		Aspect();
		
	};
}

#endif 