#ifndef GroupManager_h__
#define GroupManager_h__

#include "Manager.h"
#include "RefBag.h"
#include <string>
#include <unordered_map>
#include <set>
#include <vector>
using std::vector;

namespace ES
{
	// If you need to group your entities together, e.g. tanks going into "units" group or explosions into "effects",
	// then use this manager. You must retrieve it using world instance.
	// A entity can be assigned to more than one group.
	class GroupManager : public Manager
	{
	public:
		GroupManager();
		~GroupManager();
		void initialize();
		void add(Entity& e, std::string group);
		void remove(Entity& e, std::string group);
		void removeFromAllGroups(Entity& e);
		vector<Entity*> getEntities(std::string group);
		std::set<std::string> getGroups(Entity& e);
		bool isInAnyGroup(Entity& e);
		bool isInGroup(Entity& e, std::string group);
		void deleted(Entity& e);
	private:
		std::unordered_map<std::string, RefBag<Entity>*> entitiesByGroup;
		std::unordered_map<Entity*, std::set<std::string>> groupsByEntity;
	};
}

#endif 