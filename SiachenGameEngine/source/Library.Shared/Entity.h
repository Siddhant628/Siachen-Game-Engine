#pragma once
#include "Attributed.h"
#include "WorldState.h"

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
		class Sector;
		
		/**
		* Entity is an attributed scope which gets populated at compile time.
		*/
		class Entity : public Attributed
		{
			RTTI_DECLARATIONS(Entity, Attributed)
		private:
			/**
			* Name of this entity.
			*/
			std::string mEntityName;
		public:
			/**
			* Default constructor - Populates the prescribed attributes.
			*/
			Entity();
			/**
			* Destructor.
			*/
			virtual ~Entity() = default;
			/**
			* Populate the scope with prescribed attributes of this class.
			*/
			virtual void Populate() override;
			/**
			* Get the name of the Entity.
			* @return The name of the Entity as a string.
			*/
			const std::string& Name() const;
			/**
			* Set the name of the Entity.
			* @param worldName The name (string) which has to be set as the name of the Entity.
			*/
			void SetName(const std::string& entityName);
			/**
			* Get the sector in which this entity is contained.
			* @return A pointer to the sector in which this entity is contained.
			*/
			Sector* GetSector() const;
			/**
			* Updates the entity.
			* @param worldState A reference to the current world state.
			*/
			void Update(WorldState& worldState);
		};
	}
}