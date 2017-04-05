#include "ActionDestroyAction.h"
#include "ActionList.h"
#include "Entity.h"
#include "Sector.h"
#include "World.h"

using namespace SiachenGameEngine::Containers;

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
		const std::string sActionName = "actionName";
		const std::string sActions = "actions";

		RTTI_DEFINITIONS(ActionDestroyAction)

		void ActionDestroyAction::Populate()
		{
			AddExternalAttribute(sActionName, &mActionName, 1U);
		}

		ActionDestroyAction::ActionDestroyAction()
		{
			Populate();
			UpdatePrescribedAttributeInfo();
		}

		void ActionDestroyAction::Update(WorldState& worldState)
		{
			worldState.mAction = this;

			Scope* parent = GetParent();
			Datum* datum = nullptr;
			datum = &parent->Append(sActions);
			assert(datum != nullptr);
			// Remove the action from the datum and destroy it.
			std::uint32_t size = datum->Size();
			for (std::uint32_t it = 0; it < size; ++it)
			{
				if (static_cast<Action*>(datum->Get<Scope*>(it))->Name() == mActionName)
				{
					Scope* removedAction = datum->Get<Scope*>(it);
					datum->Remove(removedAction);
					delete removedAction;
				}
			}

			worldState.mAction = GetParent()->As<Action>();
		}
	}
}