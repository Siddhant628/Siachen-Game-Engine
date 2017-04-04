#pragma once
#include "Attributed.h"
#include "WorldState.h"
#include "Action.h"

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
			/**
			* A pointer to actions contained within this entity.
			*/
			Containers::Datum* mActionDatum;
		protected:
			/**
			* Populate the scope with prescribed attributes of this class.
			*/
			virtual void Populate() override;
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
			* Get the name of the Entity.
			* @return The name of the Entity as a string.
			*/
			const std::string& Name() const;
			/**
			* Set the name of the Entity.
			* @param entityName The name (string) which has to be set as the name of the Entity.
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
			virtual void Update(WorldState& worldState);
			/**
			* Get the datum containing pointers to actions.
			* @return A reference to the actions datum.
			*/
			Containers::Datum& Actions();
			/**
			* Create an Action using the Action factory and adopts it into this Entity.
			* @param className The name of the Action class which has to be instantiated.
			* @param instanceName The name that the new Action class object will take.
			* @return A pointer to the created Action.
			*/
			Action* CreateAction(const std::string& className, const std::string& instanceName);
			/**
			* Adopt a Action into this Entity's scope.
			* @param action The Action which has to be adopted.
			*/
			void AdoptAction(Action& action);
		private:
			const static std::string sActions;
		};
	}
}