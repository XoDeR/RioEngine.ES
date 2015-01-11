#ifndef TeamManager_h__
#define TeamManager_h__

#include "Manager.h"
#include "Bag.h"
#include <string>
#include <unordered_map>
#include <set>

namespace ES
{
	// Use this class together with PlayerManager.
	// You may sometimes want to create teams in your game, so that
	// some players are team mates.
	// A player can only belong to a single team.
	class TeamManager : public Manager
	{
	public:
		TeamManager();
		void initialize();
		std::string getTeam(std::string player);
		void setTeam(std::string player, std::string team);
		std::set<std::string> getPlayers(std::string team);
		void removeFromTeam(std::string player);
	private:
		std::unordered_map<std::string, std::set<std::string>> playersByTeam;
		std::unordered_map<std::string, std::string> teamByPlayer;
	};
}

#endif 