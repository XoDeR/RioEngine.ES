#ifndef IntervalEntitySystem_h__
#define IntervalEntitySystem_h__

#include "EntitySystem.h"
#include <memory>
using std::unique_ptr;

namespace ES
{
	class Aspect;

	// A system that processes entities at a interval in milliseconds.
	// A typical usage would be a collision system or physics system.
	class IntervalEntitySystem : public EntitySystem
	{
	public:
		IntervalEntitySystem(unique_ptr<Aspect> aspect, float interval);
	protected:
		bool checkProcessing();
	private:
		float acc;
		float interval;
	};
}

#endif 