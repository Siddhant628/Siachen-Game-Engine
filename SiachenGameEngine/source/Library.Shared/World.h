#pragma once
#include "Attributed.h"
#include "Sector.h"

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
		class World : public Attributed
		{
			RTTI_DECLARATIONS(World, Attributed)
		private:
			std::string mWorldName;

			Containers::Datum* mSectorDatum;
		public:
			World();

			~World() = default;

			virtual void Populate() override;

			const std::string& Name() const;

			void SetName(const std::string& worldName);

			void AdoptSector(Sector& sector);

			Containers::Datum& Sectors();
			// TODO Confirm
			Sector* CreateSector();

			void Update(WorldState& worldState);
		};
	}
}