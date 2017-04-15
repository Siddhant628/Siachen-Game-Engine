#pragma once

#include "EventSubscriber.h"
#include "ActionList.h"

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
		/**
		* An abstract class which ties the event system with the rest of the game engine.
		*/
		class Reaction : public ActionList, public Events::EventSubscriber
		{
			RTTI_DECLARATIONS(Reaction, ActionList)
		private:

		public:

		};
	}
}

// TODO Write associated factory group