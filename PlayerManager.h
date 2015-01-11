#ifndef PlayerManager_h__
#define PlayerManager_h__

#include "Manager.h"
#include "RefBag.h"
#include <string>
#include <unordered_map>

namespace ES
{
	// You may sometimes want to specify to which player an entity belongs to.
	// An entity can only belong to a single player at a time.
	class PlayerManager : public Manager
	{
	public:
		PlayerManager();
		~PlayerManager();
		void setPlayer(Entity& e, std::string player);
		RefBag<Entity>* getEntitiesOfPlayer(std::string player);
		void removeFromPlayer(Entity& e);
		std::string getPlayer(Entity& e);
		void initialize();
		void deleted(Entity& e);
	private:
		std::unordered_map<Entity*, std::string> playerByEntity;
		std::unordered_map<std::string, RefBag<Entity>*> entitiesByPlayer;
	};
}

#endif 