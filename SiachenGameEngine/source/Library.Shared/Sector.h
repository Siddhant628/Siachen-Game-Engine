#pragma once
#include "Attributed.h"
#include "Entity.h"

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
		class World;
		/**
		* Sector is a class used to segment the world into chunks for managing assets.
		*/
		class Sector final : public Attributed
		{
			RTTI_DECLARATIONS(Sector, Attributed)
		private:
			/**
			* Name of this sector.
			*/
			std::string mSectorName;
			/**
			* A pointer to the datum containing pointers to the entities within this sector.
			*/
			Containers::Datum* mEntityDatum;
		public:
			/**
			* Default constructor - Populates the prescribed attributes.
			*/
			Sector();
			/**
			* Destructor.
			*/
			virtual ~Sector() = default;
			/**
			* Populate the scope with prescribed attributes of this class.
			*/
			virtual void Populate() override;
			/**
			* Get the name of the Sector.
			* @return The name of the sector as a string.
			*/
			const std::string& Name() const;
			/**
			* Set the name of the Sector.
			* @param worldName The name (string) which has to be set as the name of the Sector.
			*/
			void SetName(const std::string& sectorName);
			/**
			* Get the datum containing pointers to entities.
			* @return A reference to the entities datum.
			*/
			Containers::Datum& Entities();
			/**
			* Create an entity using the entity factory and adopt it into this sector.
			* @param className The name of the entity class which has to be instantiated.
			* @param instanceName The name that the new entity class object will take.
			* @return A pointer to the created entity.
			*/
			Entity* CreateEntity(const std::string& className, const std::string& instanceName);
			/**
			* Get the world in which this sector is contained.
			* @return A pointer to the world in which this sector is contained.
			*/
			World* GetWorld() const;
			/**
			* Adopt a entity into this sector's scope.
			* @param entity The entity which has to be adopted.
			*/
			void AdoptEntity(Entity& entity);
			/**
			* Iterates through the contained entities and calls their update methods.
			* @param worldState A reference to the current world state.
			*/
			void Update(WorldState& worldState);
		};
	}
}