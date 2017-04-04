#pragma once
#include "Action.h"

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
		class ActionCreateAction : public Action
		{
			RTTI_DECLARATIONS(ActionCreateAction, Action)
		protected:
			virtual void Populate() override;
		public:
			ActionCreateAction();

			~ActionCreateAction() = default;

			virtual void Update(WorldState& worldState) override;
		};
	}
}