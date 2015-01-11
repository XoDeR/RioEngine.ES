#ifndef Performer_h__
#define Performer_h__

namespace ES
{
	class EntityObserver;
	class Entity;

	// Only used internally to maintain clean code.
	class Performer
	{
	public:
		virtual void perform(EntityObserver* observer, Entity& e) = 0;
	};

	class AddedPerformer : public Performer
	{
	public:
		virtual void perform(EntityObserver* observer, Entity& e);
	};

	class ChangedPerformer : public Performer
	{
	public:
		virtual void perform(EntityObserver* observer, Entity& e);
	};

	class DisablePerformer : public Performer
	{
	public:
		virtual void perform(EntityObserver* observer, Entity& e);
	};

	class EnablePerformer : public Performer
	{
	public:
		virtual void perform(EntityObserver* observer, Entity& e);
	};

	class DeletedPerformer : public Performer
	{
	public:
		virtual void perform(EntityObserver* observer, Entity& e);
	};
}
#endif // Performer_h__