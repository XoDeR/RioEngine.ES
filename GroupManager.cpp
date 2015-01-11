#include "GroupManager.h"
#include "Entity.h"

namespace ES
{
	GroupManager::GroupManager()
	{

	}

	GroupManager::~GroupManager()
	{
		for (auto it = entitiesByGroup.begin(); it != entitiesByGroup.end(); ++it)
		{
			delete it->second;
			it->second = nullptr;
		}
		entitiesByGroup.clear();
	}

	void GroupManager::initialize()
	{

	}

	void GroupManager::add(Entity& e, std::string group)
	{
		RefBag<Entity>* entities = nullptr;
		{
			auto it = entitiesByGroup.find(group);
			if (it != entitiesByGroup.end())
			{
				entities = it->second;
			}
			else
			{
				entities = new RefBag<Entity>();
				entitiesByGroup[group] = entities;
			}
		}
		entities->add(&e);

		std::set<std::string> groups;
		{
			auto it = groupsByEntity.find(&e);
			if (it != groupsByEntity.end())
			{
				groups = it->second;
				groups.insert(group);
			} 
			else
			{
				groups.insert(group);
				groupsByEntity[&e] = groups;
			}
		}
	}

	void GroupManager::remove(Entity& e, std::string group)
	{
		RefBag<Entity>* entities = nullptr;
		{
			auto it = entitiesByGroup.find(group);
			if (it != entitiesByGroup.end())
			{
				entities = it->second;
				entities->remove(&e);
			}
		}
		
		std::set<std::string> groups;
		{
			auto it = groupsByEntity.find(&e);
			if (it != groupsByEntity.end())
			{
				groups = it->second;
				groups.erase(group);
			}
		}
	}

	void GroupManager::removeFromAllGroups(Entity& e)
	{
		std::set<std::string> groups;
		{
			auto it = groupsByEntity.find(&e);
			if (it != groupsByEntity.end())
			{
				groups = it->second;
				for (std::string group : groups)
				{
					RefBag<Entity>* entities = nullptr;
					{
						auto it = entitiesByGroup.find(group);
						if (it != entitiesByGroup.end())
						{
							entities = it->second;
							entities->remove(&e);
						}
					}
				}
				groups.clear();
			}
		}
	}

	vector<Entity*> GroupManager::getEntities(std::string group)
	{
		vector<Entity*> result;
		RefBag<Entity>* entities = nullptr;
		auto it = entitiesByGroup.find(group);
		if (it != entitiesByGroup.end())
		{
			entities = it->second;
		}
		else
		{
			entities = new RefBag<Entity>();
			entitiesByGroup[group] = entities;
		}

		if (entities != nullptr)
		{
			for (int i = 0; i < entities->size(); ++i)
			{
				Entity* e = entities->get(i);
				if (e != nullptr && e->isActive() == true && e->isEnabled() == true)
				{
					result.push_back(e);
				}
			}
		}
		return result;
	}

	std::set<std::string> GroupManager::getGroups(Entity& e)
	{
		std::set<std::string> result;
		auto it = groupsByEntity.find(&e);
		if (it != groupsByEntity.end())
		{
			result = it->second;
		}
		return result;
	}

	bool GroupManager::isInAnyGroup(Entity& e)
	{
		return getGroups(e).size() > 0;
	}

	bool GroupManager::isInGroup(Entity& e, std::string group)
	{
		if (group != "")
		{
			std::set<std::string> groups;
			auto it = groupsByEntity.find(&e);
			if (it != groupsByEntity.end())
			{
				groups = it->second;
				for (auto g : groups)
				{
					if (group == g)
					{
						return true;
					}
				}
			} 
			else
			{
				return false;
			}
		}
		return false;
	}

	void GroupManager::deleted(Entity& e)
	{
		removeFromAllGroups(e);
	}
}
