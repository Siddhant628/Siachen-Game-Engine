#include "pch.h"
#include "World.h"
#include "Sector.h"

using namespace SiachenGameEngine::Containers;

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
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

			std::uint32_t size = mSectorDatum->Size();
			for (std::uint32_t it = 0; it < size; ++it)
			{
				static_cast<Sector*>(mSectorDatum->Get<Scope*>(it))->Update(worldState);
			}

			worldState.mWorld = nullptr;
		}
	}
}