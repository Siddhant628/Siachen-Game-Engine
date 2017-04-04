#include "pch.h"
#include "World.h"
#include "Sector.h"
#include "Factory.h"

using namespace SiachenGameEngine::Containers;

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
		const std::string World::sActions = "actions";

		RTTI_DEFINITIONS(World)

		World::World(const std::string& worldName) : mSectorDatum(nullptr), mWorldName(worldName)
		{
			if (worldName == "")
			{
				throw std::runtime_error("The world must have a name.");
			}
			Populate();
			UpdatePrescribedAttributeInfo();

		}

		void World::Populate()
		{
			AddExternalAttribute("name", &mWorldName, 1U);
			mSectorDatum = &AddInternalAttribute("sectors", DatumType::TableType);
			assert(mSectorDatum != nullptr);
			mActionDatum = &AddInternalAttribute(sActions, DatumType::TableType);
			assert(mActionDatum != nullptr);
		}

		const std::string& World::Name() const
		{
			return mWorldName;
		}

		void World::SetName(const std::string& worldName)
		{
			mWorldName = worldName;
		}
		
		void World::AdoptSector(Sector& sector)
		{
			Adopt(sector, "sectors");
		}

		Datum& World::Sectors()
		{
			assert(mSectorDatum == Find("sectors"));
			return *mSectorDatum;
		}

		Sector* World::CreateSector(const std::string& sectorName)
		{
			Sector* sectorCreated = new Sector();
			sectorCreated->SetName(sectorName);
			AdoptSector(*sectorCreated);
			return sectorCreated;
		}

		void World::Update(WorldState& worldState)
		{
			worldState.mWorld = this;
			// Call update on contained actions
			Datum& actionDatum = *mActionDatum;
			std::uint32_t size = actionDatum.Size();
			for (std::uint32_t it = 0; it < size; ++it)
			{
				assert(actionDatum.Get<Scope*>(it)->Is(Action::TypeIdClass()));
				static_cast<Action*>(actionDatum.Get<Scope*>(it))->Update(worldState);
			}
			// Call update on contained sectors
			size = mSectorDatum->Size();
			for (std::uint32_t it = 0; it < size; ++it)
			{
				assert(mSectorDatum->Get<Scope*>(it)->Is(Sector::TypeIdClass()));
				static_cast<Sector*>(mSectorDatum->Get<Scope*>(it))->Update(worldState);
			}

			worldState.mWorld = nullptr;
		}
		
		Containers::Datum& World::Actions()
		{
			assert(Find(sActions) == mActionDatum);
			return *mActionDatum;
		}
		
		Action* World::CreateAction(const std::string& className, const std::string& instanceName)
		{
			Action* actionCreated = Factory<Action>::Create(className);

			if (actionCreated)
			{
				actionCreated->SetName(instanceName);
				AdoptAction(*actionCreated);
			}
			return actionCreated;
		}
		
		void World::AdoptAction(Action& action)
		{
			Adopt(action, sActions);
		}
	}
}