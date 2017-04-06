#pragma once
#include "Action.h"
#include "Factory.h"

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
		class ActionCreateAction : public Action
		{
			RTTI_DECLARATIONS(ActionCreateAction, Action)
		private:
			/**
			* The name of the class which has to be created.
			*/
			std::string mClassName;
			/**
			* The name to be given to the instance of the Action object created.
			*/
			std::string mInstanceName;
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
			ActionCreateAction();
			/**
			* Destructor.
			*/
			~ActionCreateAction() = default;
			/**
			* Creates the appropriate Action class object.
			* @param worldState A reference to the current world state.
			*/
			virtual void Update(WorldState& worldState) override;
		private:
			/**
			* Strings corresponding to keys in this scope.
			*/
			static const std::string sClassName;
			static const std::string sInstanceName;
		};
		
		ConcreteFactory(SiachenGameEngine::GameplayFramework::Action, ActionCreateAction)
	}
}