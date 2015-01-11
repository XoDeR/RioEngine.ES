#include "ComponentType.h"

namespace ES
{
	std::unordered_map<std::type_index, ComponentType*> ComponentType::componentTypes;

	int ComponentType::INDEX = 0;

	ComponentType::ComponentType(std::type_index type)
		: type(type)
	{
		index = INDEX++;
	}

	int ComponentType::getIndex()
	{
		return index;
	}

	std::string ComponentType::toString()
	{
		return std::string("ComponentType[") + type.name() + "] (" + std::to_string(index) + ")";
	}

	void ComponentType::deleteComponentTypes()
	{
		for (auto it = componentTypes.begin(); it != componentTypes.end(); it++)
		{
			delete it->second;
		}
		componentTypes.clear();
	}

	ComponentType& ComponentType::getTypeFor(std::type_index t)
	{
		ComponentType* type = nullptr;
		auto got = componentTypes.find(t);
		if (got == componentTypes.end())
		{
			type = new ComponentType(t);
			componentTypes[t] = type;
		}
		else
		{
			type = got->second;
		}

		return *type;
	}
}