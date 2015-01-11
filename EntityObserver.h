#ifndef EntityObserver_h__
#define EntityObserver_h__

namespace ES
{
	class Entity;

	class EntityObserver
	{
	public:
		virtual ~EntityObserver() {}
		virtual void added(Entity& e) = 0;
		virtual void changed(Entity& e) = 0;
		virtual void deleted(Entity& e) = 0;
		virtual void enabled(Entity& e) = 0;
		virtual void disabled(Entity& e) = 0;
	};
}

#endif 