#pragma once
#include "Attributed.h"
#include "Entity.h"

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
		class World;

		class Sector final : public Attributed
		{
			RTTI_DECLARATIONS(Sector, Attributed)
		private:
			std::string mSectorName;

			Containers::Datum* mEntityDatum;
		public:
			Sector();

			~Sector() = default;

			virtual void Populate() override;

			const std::string& Name() const;

			void SetName(const std::string& sectorName);

			Containers::Datum& Entities();

			Entity* CreateEntity(const std::string& className, const std::string& instanceName);

			World* GetWorld() const;

			void AdoptEntity(Entity& entity);

			void Update(WorldState& worldState);
		};
	}
}