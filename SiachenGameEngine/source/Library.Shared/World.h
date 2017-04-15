#pragma once
#include "Attributed.h"
#include "Sector.h"
#include "Vector.h"
#include "EventQueue.h"
#include "WorldState.h"

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
		/**
		* A container for an interactive simulation. It defines the global scope and contains everything (sectors, which contain entities, etc.)
		*/
		class World final : public Attributed
		{
			RTTI_DECLARATIONS(World, Attributed)
		private:
			/**
			* The name of the world.
			*/
			std::string mWorldName;
			/**
			* Pointer to the datum which contains pointers to all the sectors contained within this world.
			*/
			Containers::Datum* mSectorDatum;
			/**
			* A pointer to actions contained within this World.
			*/
			Containers::Datum* mActionDatum;
			/**
			* Actions queued for deletion at the end of update.
			*/
			Containers::Vector<Action*> mActionDeleteQueue;
			/**
			* A queue of events for the world.
			*/
			Events::EventQueue mWorldEventQueue;
			/**
			* A pointer to the current world state.
			*/
			WorldState* mWorldState;
			/**
			* Delete all the actions waiting in the queue for deletion.
			*/
			void HandleActionDestroyQueue();
		public:
			/**
			* Default constructor - Populates the prescribed attributes.
			* @param worldName The name that the world would take.
			*/
			World(const std::string& worldName);
			/**
			* Destructor.
			*/
			virtual ~World() = default;
			/**
			* Populate the scope with prescribed attributes of this class.
			*/
			virtual void Populate() override;
			/**
			* Get the name of the World.
			* @return The name of the world as a string.
			*/
			const std::string& Name() const;
			/**
			* Set the name of the world.
			* @param worldName The name (string) which has to be set as the name of the world.
			*/
			void SetName(const std::string& worldName);
			/**
			* Adopt a sector into this world's scope.
			* @param sector The sector which has to be adopted.
			*/
			void AdoptSector(Sector& sector);
			/**
			* Get the datum containing pointers to sectors.
			* @return A reference to the sectors datum.
			*/
			Containers::Datum& Sectors();
			/**
			* Create a sector and add it the this world.
			* @param sectorName The name which the created sector has to be given.
			*/
			Sector* CreateSector(const std::string& sectorName);
			/**
			* Iterates through the contained sectors and calls their update methods.
			* @param worldState A reference to the current world state.
			*/
			void Update(WorldState& worldState);
			/**
			* Get the datum containing pointers to actions.
			* @return A reference to the actions datum.
			*/
			Containers::Datum& Actions();
			/**
			* Create an Action using the Action factory and adopts it into this World.
			* @param className The name of the Action class which has to be instantiated.
			* @param instanceName The name that the new Action class object will take.
			* @return A pointer to the created Action.
			*/
			Action* CreateAction(const std::string& className, const std::string& instanceName);
			/**
			* Adopt a Action into this World's scope.
			* @param action The Action which has to be adopted.
			*/
			void AdoptAction(Action& action);
			/**
			* Add an action for deletion to the delete queue.
			* @param action The action which has to be deleted.
			*/
			void AddToActionDestroyQueue(Action& action);
			/**
			* Get the event queue contained in the world.
			* @return A reference the event queue contained in this world.
			*/
			Events::EventQueue& GetQueue();
			/**
			* Get a pointer to the world state object.
			* @return A pointer to the world state object.
			*/
			WorldState& GetWorldState();
		private:
			const static std::string sActions;
		};
	}
}