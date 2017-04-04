#include "ActionList.h"

using namespace SiachenGameEngine::Containers;

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
		RTTI_DEFINITIONS(ActionList)

		void ActionList::Populate()
		{
			AddInternalAttribute("actionList", DatumType::TableType);
		}

		ActionList::ActionList()
		{
			Populate();
			UpdatePrescribedAttributeInfo();
		}

		void ActionList::Update(WorldState& worldState)
		{
			worldState.mAction = this;

			Datum& actionList = Append("actionList");
			std::uint32_t listSize = actionList.Size();
			for (std::uint32_t it = 0; it < listSize; ++it)
			{
				Action* action = static_cast<Action*>(actionList.Get<Scope*>(it));
				assert(action->Is(Action::TypeIdClass()));
				action->Update(worldState);
			}

			worldState.mAction = nullptr;
		}
	}
}