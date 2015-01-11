#include "Aspect.h"
#include "Entity.h"
#include "ESUtil.h"

namespace ES
{
	Aspect::Aspect()
	{
	}

	Aspect::~Aspect()
	{
		allSet.reset();
		exclusionSet.reset();
		oneSet.reset();
	}

	unique_ptr<Aspect> Aspect::getEmpty()
	{
		unique_ptr<Aspect> result(new Aspect());
		return result;
	}

	bool Aspect::hasAspect(Entity& e)
	{
		std::bitset<CAPACITY> componentBits = e.getComponentBits();

		bool interested = true; // possibly interested, let's try to prove it wrong.

		// Check if the entity possesses ALL of the components defined in the aspect.
		if (allSet.any())
		{
			for (int i = findNextSetBit(allSet, 0); i >= 0; i = findNextSetBit(allSet, (i + 1)))
			{
				if (!componentBits.test(i))
				{
					interested = false;
					break;
				}
			}
		}
		// Check if the entity possesses ANY of the exclusion components, if it does then the system is not interested.
		if (!exclusionSet.none() && interested)
		{
			interested = (exclusionSet & componentBits).none();
		}

		// Check if the entity possesses ANY of the components in the oneSet. If so, the system is interested.
		if (!oneSet.none())
		{
			interested = (oneSet & componentBits).any();
		}

		return interested;
	}

	std::bitset<CAPACITY>& Aspect::getAllSet()
	{
		return allSet;
	}

	std::bitset<CAPACITY>& Aspect::getExclusionSet()
	{
		return exclusionSet;
	}

	std::bitset<CAPACITY>& Aspect::getOneSet()
	{
		return oneSet;
	}
}