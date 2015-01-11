#ifndef TagManager_h__
#define TagManager_h__

#include "Manager.h"
#include "Bag.h"
#include <string>
#include <unordered_map>
#include <set>

namespace ES
{
	// If you need to tag any entity, use this. A typical usage would be to tag
	// entities such as "PLAYER", "BOSS" or something that is very unique.
	class TagManager : public Manager
	{
	public:
		TagManager();
		void registerTag(std::string tag, Entity& e);
		void unregisterTag(std::string tag);
		bool isRegistered(std::string tag);
		Entity* getEntity(std::string tag);
		std::set<std::string> getRegisteredTags();
		void deleted(Entity& e);
		void initialize();
	private:
		std::unordered_map<std::string, Entity*> entitiesByTag;
		std::unordered_map<Entity*, std::string> tagsByEntity;
	};
}

#endif 