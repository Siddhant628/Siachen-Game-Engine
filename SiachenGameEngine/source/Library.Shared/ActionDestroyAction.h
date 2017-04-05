#pragma once
#include "Action.h"
#include "Factory.h"

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
		class ActionDestroyAction : public Action
		{
			RTTI_DECLARATIONS(ActionDestroyAction, Action)
		private:
			/**
			* The name of the action to delete.
			*/
			std::string mActionName;
		protected:
			/**
			* Populate the scope with prescribed attributes of this class.
			*/
			virtual void Populate() override;
		public:
			/**
			* Default constructor - Populates the prescribed attributes.
			*/
			ActionDestroyAction();
			/**
			* Destructor.
			*/
			~ActionDestroyAction() = default;
			/**
			* Destroys the appropriate Action.
			* @param worldState A reference to the current world state.
			*/
			virtual void Update(WorldState& worldState) override;
		private:
			/**
			* Strings corresponding to keys in this scope.
			*/
			static const std::string sActionName;
			static const std::string sActions;
		};
		ConcreteFactory(SiachenGameEngine::GameplayFramework::Action, ActionDestroyAction)
	}
}