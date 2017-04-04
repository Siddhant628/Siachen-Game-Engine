#include "pch.h"
#include "ActionCreateAction.h"

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
		RTTI_DEFINITIONS(ActionCreateAction)

		ActionCreateAction::ActionCreateAction()
		{
			Populate();
			UpdatePrescribedAttributeInfo();
		}

		void ActionCreateAction::Populate()
		{

		}

		void ActionCreateAction::Update(WorldState& worldState)
		{
			worldState;
		}
	}
}