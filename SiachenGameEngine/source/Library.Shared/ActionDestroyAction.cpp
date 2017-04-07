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
		const std::string ActionDestroyAction::sActionName = "actionName";
		const std::string ActionDestroyAction::sActions = "actions";

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

			while (parent != nullptr)
			{
				assert(parent->Find(sActions) != nullptr);
				datum = &parent->Append(sActions);
				std::uint32_t size = datum->Size();
				for (std::uint32_t it = 0; it < size; ++it)
				{
					if (static_cast<Action*>(datum->Get<Scope*>(it))->Name() == mActionName)
					{
						Action* removedAction = static_cast<Action*>(datum->Get<Scope*>(it));
						worldState.mWorld->AddToActionDestroyQueue(*removedAction);
					}
				}
				parent = parent->GetParent();
			}

			worldState.mAction = GetParent()->As<Action>();
		}
	}
}