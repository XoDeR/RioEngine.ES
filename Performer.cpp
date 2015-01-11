#include "Performer.h"
#include "Entity.h"
#include "EntityObserver.h"

namespace ES
{


	void AddedPerformer::perform(EntityObserver* observer, Entity& e)
	{
		observer->added(e);
	}


	void ChangedPerformer::perform(EntityObserver* observer, Entity& e)
	{
		observer->changed(e);
	}


	void DisablePerformer::perform(EntityObserver* observer, Entity& e)
	{
		observer->disabled(e);
	}


	void EnablePerformer::perform(EntityObserver* observer, Entity& e)
	{
		observer->enabled(e);
	}


	void DeletedPerformer::perform(EntityObserver* observer, Entity& e)
	{
		observer->deleted(e);
	}

}
