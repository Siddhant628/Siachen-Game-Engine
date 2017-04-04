#include "pch.h"
#include "ActionCreateAction.h"
#include "Factory.h"

#include "ActionList.h"
#include "Entity.h"
#include "Sector.h"
#include "World.h"

using namespace SiachenGameEngine::Containers;

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
		const std::string sClassName = "className";
		const std::string sInstanceName = "instanceName";

		RTTI_DEFINITIONS(ActionCreateAction)

		void ActionCreateAction::Populate()
		{
			mClassDatum = &AddInternalAttribute(sClassName, DatumType::StringType);
			mNameDatum = &AddInternalAttribute(sInstanceName, DatumType::StringType);
		}

		ActionCreateAction::ActionCreateAction()
		{
			Populate();
			UpdatePrescribedAttributeInfo();
		}

		Action* ActionCreateAction::CreateAction()
		{
			// Create the action
			std::string className = mClassDatum->Get<std::string>();
			std::string instanceName = mNameDatum->Get<std::string>();
			Action* createdAction = Factory<Action>::Create(className);
			// Set the name of instance
			createdAction->SetName(instanceName);
			// Adopt action under the appropriate parent
			if (GetParent()->Is(ActionList::TypeIdClass()))
			{
				static_cast<ActionList*>(GetParent())->GetActionList().PushBack(createdAction);
			}
			else if(GetParent()->Is(Entity::TypeIdClass()))
			{
				static_cast<Entity*>(GetParent())->AdoptAction(*createdAction);
			}
			else if (GetParent()->Is(Sector::TypeIdClass()))
			{
				static_cast<Sector*>(GetParent())->AdoptAction(*createdAction);
			}
			else if (GetParent()->Is(World::TypeIdClass()))
			{
				static_cast<World*>(GetParent())->AdoptAction(*createdAction);
			}
			return createdAction;
		}

		void ActionCreateAction::Update(WorldState& worldState)
		{
			worldState.mAction = this;
			CreateAction();
			worldState.mAction = GetParent()->As<Action>();
		}
	}
}