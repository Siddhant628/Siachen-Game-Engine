#pragma once
#include "Action.h"

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
		class ActionCreateAction : public Action
		{
			RTTI_DECLARATIONS(ActionCreateAction, Action)
		private:
			/**
			* A pointer to the contained scalar datum which has the name of the Action to create.
			*/
			Containers::Datum* mClassDatum;
			/**
			* A pointer to the contained scalar datum which has the name of the instance to create.
			*/
			Containers::Datum* mNameDatum;
			/**
			* Creates the action. 
			*/
			Action* CreateAction();
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
			* Creates the appropriate Action.
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
	}
}