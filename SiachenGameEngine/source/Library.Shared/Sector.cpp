#include "pch.h"
#include "Sector.h"
#include "Datum.h"
#include "Factory.h"
#include "World.h"
#include "Action.h"

using namespace SiachenGameEngine::Containers;

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
		const std::string Sector::sActions = "actions";

		RTTI_DEFINITIONS(Sector)

		Sector::Sector() : mEntityDatum(nullptr)
		{
			Populate();
			UpdatePrescribedAttributeInfo();
		}

		void Sector::Populate()
		{
			AddExternalAttribute("name", &mSectorName, 1U);
			mEntityDatum = &AddInternalAttribute("entities", DatumType::TableType);
			assert(mEntityDatum != nullptr);
			mActionDatum = &AddInternalAttribute(sActions, DatumType::TableType);
			assert(mActionDatum != nullptr);
		}

		const std::string& Sector::Name() const
		{
			return mSectorName;
		}

		void Sector::SetName(const std::string& sectorName)
		{
			mSectorName = sectorName;
		}

		Datum& Sector::Entities()
		{
			assert(mEntityDatum == Find("entities"));
			return *mEntityDatum;
		}

		Entity* Sector::CreateEntity(const std::string& className, const std::string& instanceName)
		{
			Entity* entityCreated = Factory<Entity>::Create(className);

			if (entityCreated)
			{
				entityCreated->SetName(instanceName);
				AdoptEntity(*entityCreated);
			}
			return entityCreated;
		}

		World* Sector::GetWorld() const
		{
			assert(GetParent()->Is(World::TypeIdClass()));
			return static_cast<World*>(GetParent());
		}

		void Sector::AdoptEntity(Entity& entity)
		{
			Adopt(entity, "entities");
		}

		void Sector::Update(WorldState& worldState)
		{
			worldState.mSector = this;

			// Call update on contained actions
			Datum& actionDatum = *mActionDatum;
			std::uint32_t size = actionDatum.Size();
			for (std::uint32_t it = 0; it < size; ++it)
			{
				assert(actionDatum.Get<Scope*>(it)->Is(Action::TypeIdClass()));
				static_cast<Action*>(actionDatum.Get<Scope*>(it))->Update(worldState);
			}
			// Call update on contained entities
			size = mEntityDatum->Size();
			for (std::uint32_t it = 0; it < size; ++it)
			{
				assert(mEntityDatum->Get<Scope*>(it)->Is(Entity::TypeIdClass()));
				static_cast<Entity*>(mEntityDatum->Get<Scope*>(it))->Update(worldState);
			}

			worldState.mSector = nullptr;
		}
		
		Containers::Datum& Sector::Actions()
		{
			assert(Find(sActions) == mActionDatum);
			return *mActionDatum;
		}

		Action* Sector::CreateAction(const std::string& className, const std::string& instanceName)
		{
			Action* actionCreated = Factory<Action>::Create(className);

			if (actionCreated)
			{
				actionCreated->SetName(instanceName);
				AdoptAction(*actionCreated);
			}
			return actionCreated;
		}

		void Sector::AdoptAction(Action& action)
		{
			Adopt(action, sActions);
		}
	}
}