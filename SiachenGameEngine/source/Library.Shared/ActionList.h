#pragma once
#include "Action.h"

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
		/**
		* A concrete action which contains a list of actions.
		*/
		class ActionList : public Action
		{
			RTTI_DECLARATIONS(ActionList, Action)
		protected:
			/**
			* Populate the scope with prescribed attributes of this class.
			*/
			virtual void Populate() override;
		public:
			/**
			* Default constructor - Populates the prescribed attributes.
			*/
			ActionList();
			/**
			* Destructor.
			*/
			virtual ~ActionList() = default;
			/**
			* Updates the ActionList (Calls update on each contained action).
			* @param worldState A reference to the current world state.
			*/
			virtual void Update(WorldState& worldState) override;
		};
	}
}