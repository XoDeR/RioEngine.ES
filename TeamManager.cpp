#include "TeamManager.h"

namespace ES
{
	TeamManager::TeamManager()
	{
	}

	void TeamManager::initialize()
	{
	}

	std::string TeamManager::getTeam(std::string player)
	{
		std::string result;
		auto it = teamByPlayer.find(player);
		if (it != teamByPlayer.end())
		{
			result = it->second;
		}
		return result;
	}

	void TeamManager::setTeam(std::string player, std::string team)
	{
		removeFromTeam(player);

		teamByPlayer[player] = team;

		std::set<std::string> players = getPlayers(team);
		if (players.size() == 0) 
		{
			players.insert(player);
			playersByTeam[team] = players;
		}
		else
		{
			players.insert(player);
		}
	}

	std::set<std::string> TeamManager::getPlayers(std::string team)
	{
		std::set<std::string> players;
		auto playersIt = playersByTeam.find(team);
		if (playersIt != playersByTeam.end())
		{
			players = playersIt->second;
		}
		return players;
	}

	void TeamManager::removeFromTeam(std::string player)
	{
		std::string team;
		auto it = teamByPlayer.find(player);
		if (it != teamByPlayer.end())
		{
			team = it->second;
			teamByPlayer.erase(player);
		}
		if (team != "")
		{
			std::set<std::string> players;
			auto playersIt = playersByTeam.find(team);
			if (playersIt != playersByTeam.end())
			{
				players = playersIt->second;
				players.erase(player);
			}
		}
	}
}