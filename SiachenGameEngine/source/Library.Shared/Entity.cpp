#include "pch.h"
#include "Entity.h"
#include "Sector.h"
#include "Factory.h"

using namespace SiachenGameEngine::Containers;

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
		const std::string Entity::sActions = "actions";

		RTTI_DEFINITIONS(Entity)

		Entity::Entity() : mActionDatum(nullptr)
		{
			Populate();
			UpdatePrescribedAttributeInfo();
		}

		void Entity::Populate()
		{
			AddExternalAttribute("name", &mEntityName, 1U);
			mActionDatum = &AddInternalAttribute(sActions, DatumType::TableType);
			assert(mActionDatum != nullptr);
		}

		const std::string& Entity::Name() const
		{
			return mEntityName;
		}

		void Entity::SetName(const std::string& entityName)
		{
			mEntityName = entityName;
		}

		Sector* Entity::GetSector() const
		{
			assert(GetParent()->Is(Sector::TypeIdClass()));
			return static_cast<Sector*>(GetParent());
		}

		void Entity::Update(WorldState& worldState)
		{
			worldState.mEntity = this;
			
			Datum& actionDatum = *mActionDatum;
			std::uint32_t size = actionDatum.Size();
			for (std::uint32_t it = 0; it < size; ++it)
			{
				assert(actionDatum.Get<Scope*>(it)->Is(Action::TypeIdClass()));
				static_cast<Action*>(actionDatum.Get<Scope*>(it))->Update(worldState);
			}

			worldState.mEntity = nullptr;
		}

		Containers::Datum& Entity::Actions()
		{
			assert(Find(sActions) == mActionDatum);
			return *mActionDatum;
		}
		
		Action* Entity::CreateAction(const std::string& className, const std::string& instanceName)
		{
			Action* actionCreated = Factory<Action>::Create(className);

			if (actionCreated)
			{
				actionCreated->SetName(instanceName);
				AdoptAction(*actionCreated);
			}
			return actionCreated;
		}

		void Entity::AdoptAction(Action& action)
		{
			Adopt(action, sActions);
		}
	}
}
