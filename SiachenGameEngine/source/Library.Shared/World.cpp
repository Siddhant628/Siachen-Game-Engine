#include "pch.h"
#include "World.h"
#include "Sector.h"

using namespace SiachenGameEngine::Containers;

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
		RTTI_DEFINITIONS(World)

		World::World() : mSectorDatum(nullptr)
		{
			Populate();
			UpdatePrescribedAttributeInfo();
			mSectorDatum = Find("sectors");
		}

		void World::Populate()
		{
			AddExternalAttribute("name", &mWorldName, 1U);
			AddInternalAttribute("sectors", DatumType::TableType);
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
			return *mSectorDatum;
		}

		Sector* World::CreateSector()
		{
			Sector* sectorCreated = new Sector();
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