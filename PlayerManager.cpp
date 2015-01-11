#include "PlayerManager.h"

namespace ES
{
	PlayerManager::PlayerManager()
	{
	}

	PlayerManager::~PlayerManager()
	{
		for (auto& kv : entitiesByPlayer)
		{
			RefBag<Entity>* bag = kv.second;
			delete bag;
		}
	}

	void PlayerManager::setPlayer(Entity& e, std::string player)
	{
		playerByEntity[&e] = player;
		RefBag<Entity>* entities = nullptr;
		auto it = entitiesByPlayer.find(player);
		if (it != entitiesByPlayer.end())
		{
			entities = it->second;
		}
		else
		{
			entities = new RefBag<Entity>();
			entitiesByPlayer[player] = entities;
		}

		entities->add(&e);
	}

	RefBag<Entity>* PlayerManager::getEntitiesOfPlayer(std::string player)
	{
		RefBag<Entity>* entities = nullptr;
		auto it = entitiesByPlayer.find(player);
		if (it != entitiesByPlayer.end())
		{
			entities = it->second;
		}
		else
		{
			entities = new RefBag<Entity>();
			entitiesByPlayer[player] = entities;
		}
		return entities;
	}

	void PlayerManager::removeFromPlayer(Entity& e)
	{
		std::string player;
		auto it = playerByEntity.find(&e);
		if (it != playerByEntity.end())
		{
			RefBag<Entity>* entities = nullptr;
			auto entIt = entitiesByPlayer.find(player);
			if (entIt != entitiesByPlayer.end())
			{
				entities = entIt->second;
				entities->remove(&e);
			}
		}
	}

	std::string PlayerManager::getPlayer(Entity& e)
	{
		std::string player;
		auto it = playerByEntity.find(&e);
		if (it != playerByEntity.end())
		{
			player = it->second;
		}
		return player;
	}

	void PlayerManager::initialize()
	{
	}

	void PlayerManager::deleted(Entity& e)
	{
		removeFromPlayer(e);
	}
}