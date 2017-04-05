#pragma once
#include "Action.h"
#include "WorldState.h"
#include "Factory.h"

namespace SiachenGameEngine
{
	namespace HelperClasses
	{
		class ActionFoo : public GameplayFramework::Action
		{
			RTTI_DECLARATIONS(ActionFoo, Action)
		protected:
			virtual void Populate() override;
		public:
			ActionFoo();
			~ActionFoo() = default;
			virtual void Update(GameplayFramework::WorldState& worldState) override;
		public:
			std::string mString;
		};
		ConcreteFactory(SiachenGameEngine::GameplayFramework::Action, ActionFoo)
	}
}