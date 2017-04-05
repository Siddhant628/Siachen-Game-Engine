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
			std::uint32_t size;
			// In case, parent is a ActionList
			if (parent->Is(ActionList::TypeIdClass()))
			{
				datum = &static_cast<ActionList*>(parent)->Actions();
			}
			// In case, parent is a Entity
			else if (parent->Is(Entity::TypeIdClass()))
			{
				datum = &static_cast<Entity*>(parent)->Actions();
			}
			// In case, parent is a sector
			else if (parent->Is(Sector::TypeIdClass()))
			{
				datum = &static_cast<Sector*>(parent)->Actions();
			}
			// In case, parent is world
			else if (parent->Is(World::TypeIdClass()))
			{
				datum = &static_cast<World*>(parent)->Actions();
			}
			assert(datum != nullptr);
			// Remove the action from the datum and destroy it.
			size = datum->Size();
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