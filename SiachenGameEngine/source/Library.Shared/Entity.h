#pragma once
#include "Attributed.h"
#include "WorldState.h"

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
		// TODO Check if forward declare is enough.
		class Sector;

		class Entity : public Attributed
		{
			RTTI_DECLARATIONS(Entity, Attributed)

		public:
			Entity();

			virtual ~Entity() = default;
		
			void Populate() override;

			const std::string& Name() const;

			void SetName(const std::string& entityName);
			// TODO Implement, check if type cast is required
			Sector* GetSector() const;
			// TODO Implement
			void SetSector(Sector& sector);

			void Update(const WorldState& worldState);
		private:
			std::string mEntityName;
		};
	}
}