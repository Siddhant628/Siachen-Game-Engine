#pragma once
#include "Attributed.h"
#include "WorldState.h"

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
		class Sector;

		class Entity : public Attributed
		{
			RTTI_DECLARATIONS(Entity, Attributed)
		private:
			std::string mEntityName;
		public:
			Entity();

			virtual ~Entity() = default;
		
			virtual void Populate() override;

			const std::string& Name() const;

			void SetName(const std::string& entityName);
			// TODO Confirm assert
			Sector* GetSector() const;

			void Update(WorldState& worldState);
		};
	}
}