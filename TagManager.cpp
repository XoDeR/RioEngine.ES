#include "TagManager.h"

namespace ES
{
	TagManager::TagManager()
	{
	}

	void TagManager::registerTag(std::string tag, Entity& e)
	{
		entitiesByTag[tag] = &e;
		tagsByEntity[&e] = tag;
	}

	void TagManager::unregisterTag(std::string tag)
	{
		Entity* e = nullptr;
		auto it = entitiesByTag.find(tag);
		if (it != entitiesByTag.end())
		{
			e = it->second;
			entitiesByTag.erase(tag);
			tagsByEntity.erase(e);
		}
	}

	bool TagManager::isRegistered(std::string tag)
	{
		bool result = false;
		auto it = entitiesByTag.find(tag);
		if (it != entitiesByTag.end())
		{
			result = true;
		}
		return result;
	}

	Entity* TagManager::getEntity(std::string tag)
	{
		Entity* result = nullptr;
		auto it = entitiesByTag.find(tag);
		if (it != entitiesByTag.end())
		{
			result = it->second;
		}
		return result;
	}

	std::set<std::string> TagManager::getRegisteredTags()
	{
		std::set<std::string> vals;

		for (auto& kv : tagsByEntity) 
		{
			vals.insert(kv.second);
		}

		return vals;
	}

	void TagManager::deleted(Entity& e)
	{
		std::string removedTag;
		auto it = tagsByEntity.find(&e);
		if (it != tagsByEntity.end())
		{
			removedTag = it->second;
			entitiesByTag.erase(removedTag);
		}
		tagsByEntity.erase(&e);
	}

	void TagManager::initialize()
	{
	}
}