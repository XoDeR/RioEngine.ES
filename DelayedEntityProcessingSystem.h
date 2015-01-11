#ifndef DelayedEntityProcessingSystem_h__
#define DelayedEntityProcessingSystem_h__

#include "Aspect.h"
#include "Entity.h"
#include "EntitySystem.h"
#include "Bag.h"
#include <memory>
using std::unique_ptr;

namespace ES
{
	// The purpose of this class is to allow systems to execute at varying intervals.
	// An example system would be an ExpirationSystem, that deletes entities after a certain
	// lifetime. Instead of running a system that decrements a timeLeft value for each
	// entity, you can simply use this system to execute in a future at a time of the shortest
	// lived entity, and then reset the system to run at a time in a future at a time of the
	// shortest lived entity, etc.
	// Another example system would be an AnimationSystem. You know when you have to animate
	// a certain entity, e.g. in 300 milliseconds. So you can set the system to run in 300 ms.
	// to perform the animation.
	// This will save CPU cycles in some scenarios.
	// Implementation notes:
	// In order to start the system you need to override the inserted(Entity e) method,
	// look up the delay time from that entity and offer it to the system by using the 
	// offerDelay(float delay) method.
	// Also, when processing the entities you must also call offerDelay(float delay)
	// for all valid entities.
	class DelayedEntityProcessingSystem : public EntitySystem
	{
	public:
		explicit DelayedEntityProcessingSystem(unique_ptr<Aspect> aspect);
		// Start processing of entities after a certain amount of delta time.
		// Cancels current delayed run and starts a new one.
		void restart(float delay);
		// Restarts the system only if the delay offered is shorter than the
		// time that the system is currently scheduled to execute at.
		//
		// If the system is already stopped (not running) then the offered
		// delay will be used to restart the system with no matter its value.
		//
		// If the system is already counting down, and the offered delay is
		// larger than the time remaining, the system will ignore it. If the
		// offered delay is shorter than the time remaining, the system will
		// restart itself to run at the offered delay.
		void offerDelay(float delay);
		// Get the initial delay that the system was ordered to process entities after.
		// return the originally set delay.
		float getInitialTimeDelay();
		// Get the time until the system is scheduled to run at.
		// Returns zero (0) if the system is not running.
		// Use isRunning() before checking this value.
		// returns time when system will run at.
		float getRemainingTimeUntilProcessing();
		// Check if the system is counting down towards processing.
		// returns true if it's counting down, false if it's not running.
		bool isRunning();
		// Stops the system from running, aborts current countdown.
		// Call offerDelay or restart to run it again.
		void stop();
	protected:
		void processEntities(RefBag<Entity>& entities);
		void inserted(Entity& e);
		// Return the delay until this entity should be processed.
		virtual float getRemainingDelay(Entity& e) = 0;
		bool checkProcessing();
		// Process a entity this system is interested in. Substract the accumulatedDelta
		// from the entities defined delay.
		virtual void processDelta(Entity& e, float accumulatedDelta) = 0;
		virtual void processExpired(Entity& e) = 0;
	private:
		float delay;
		bool running;
		float acc;
	};
}

#endif 