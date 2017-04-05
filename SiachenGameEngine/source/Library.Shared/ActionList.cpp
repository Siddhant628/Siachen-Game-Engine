#include "pch.h"
#include "ActionList.h"

using namespace SiachenGameEngine::Containers;

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
		const std::string sActionList = "actions";

		RTTI_DEFINITIONS(ActionList)

		void ActionList::Populate()
		{
			mActionDatum = &AddInternalAttribute(sActionList, DatumType::TableType);
		}

		ActionList::ActionList()
		{
			Populate();
			UpdatePrescribedAttributeInfo();
		}

		void ActionList::Update(WorldState& worldState)
		{
			worldState.mAction = this;

			Datum& actionList = Append(sActionList);
			std::uint32_t listSize = actionList.Size();
			for (std::uint32_t it = 0; it < listSize; ++it)
			{
				Action* action = static_cast<Action*>(actionList.Get<Scope*>(it));
				assert(action->Is(Action::TypeIdClass()));
				action->Update(worldState);
			}

			worldState.mAction = GetParent()->As<Action>();
		}

		Datum& ActionList::Actions() const
		{
			assert(mActionDatum == Find(sActionList));
			return *mActionDatum;
		}

		void ActionList::AdoptAction(Action& action)
		{
			Adopt(action, sActionList);
		}
		
		Action* ActionList::CreateAction(const std::string& className, const std::string& instanceName)
		{
			Action* actionCreated = Factory<Action>::Create(className);

			if (actionCreated)
			{
				actionCreated->SetName(instanceName);
				AdoptAction(*actionCreated);
			}
			return actionCreated;
		}
	}
}