#pragma once
#include "Action.h"
#include "Factory.h"

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
		class ActionEvent : public Action
		{
		private:
			/**
			* The subtype of event which has to be generated.
			*/
			std::string mSubtype;
			/**
			* The delay associated with this generated event.
			*/
			std::int32_t mDelay;
			// TODO Implement
			/**
			* Create an Action using the Action factory and adopts it into the parents scope.
			* @param className The name of the Action class which has to be instantiated.
			* @param instanceName The name that the new Action class object will take.
			* @return A pointer to the created Action.
			*/
			Action* CreateAction(const std::string& className, const std::string& instanceName);
		protected:
			/**
			* Populate the scope with prescribed attributes of this class.
			*/
			virtual void Populate() override;
		public:
			/**
			* Default constructor - Populates the prescribed attributes.
			*/
			ActionEvent();
			/**
			* Destructor.
			*/
			~ActionEvent() = default;
			// TODO Implement
			/**
			* Updates the Action.
			* @param worldState A reference to the current world state.
			*/
			virtual void Update(WorldState& worldState) override;
		};
		ConcreteFactory(SiachenGameEngine::GameplayFramework::Action, ActionEvent)
	}
}
