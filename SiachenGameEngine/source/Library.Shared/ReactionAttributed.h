#pragma once

#include "Reaction.h"

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
		class ReactionAttributed : Reaction
		{
			RTTI_DECLARATIONS(ReactionAttributed, Reaction)
		private:

		public:
			virtual void Notify(const Events::EventPublisher& eventObject) override;
		};
	}
}

// TODO Implement an associated factory