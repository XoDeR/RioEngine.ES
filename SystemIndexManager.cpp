#include "SystemIndexManager.h"
#include <typeinfo>
#include <typeindex>

namespace ES
{
	std::unordered_map<std::type_index, int> SystemIndexManager::indices;

	int SystemIndexManager::INDEX = 0;

	void SystemIndexManager::deleteSystemIndices()
	{
		indices.clear();
	}

	int SystemIndexManager::getIndexFor(std::type_index type)
	{
		int result = -1; // -1 is invalid index
		auto got = indices.find(type);
		if (got == indices.end())
		{
			result = INDEX++;
			indices[type] = result;
		}
		else
		{
			result = got->second;
		}
		return result;
	}
}