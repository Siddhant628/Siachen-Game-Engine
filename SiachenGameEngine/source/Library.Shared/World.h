#pragma once
#include "Attributed.h"
#include "Sector.h"

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
		class World final : public Attributed
		{
			RTTI_DECLARATIONS(World, Attributed)
		private:
			std::string mWorldName;

			Containers::Datum* mSectorDatum;
		public:
			World(const std::string& worldName);

			virtual ~World() = default;

			virtual void Populate() override;

			const std::string& Name() const;

			void SetName(const std::string& worldName);

			void AdoptSector(Sector& sector);

			Containers::Datum& Sectors();
			// TODO Confirm
			Sector* CreateSector(const std::string& sectorName);

			void Update(WorldState& worldState);
		};
	}
}