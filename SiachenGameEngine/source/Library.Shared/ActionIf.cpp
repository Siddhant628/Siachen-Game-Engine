#include "pch.h"
#include "ActionIf.h"

using namespace SiachenGameEngine::Containers;

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
		const std::string ActionIf::sCondition = "condition";

		RTTI_DEFINITIONS(ActionIf)

		void ActionIf::Populate()
		{
			AddExternalAttribute(sCondition, &mCondition, 1U);
		}

		ActionIf::ActionIf()
		{
			Populate();
			UpdatePrescribedAttributeInfo();
		}

		void ActionIf::Update(WorldState& worldState)
		{
			worldState.mAction = this;

			if (mCondition)
			{
				assert(Actions().Get<Scope*>()->Is(Action::TypeIdClass()));
				static_cast<Action*>(Actions().Get<Scope*>())->Update(worldState);
			}
			else
			{
				if (Actions().Size() > 1U)
				{
					assert(Actions().Get<Scope*>(1)->Is(Action::TypeIdClass()));
					static_cast<Action*>(Actions().Get<Scope*>(1))->Update(worldState);
				}
			}

			worldState.mAction = GetParent()->As<Action>();
		}
	}
}