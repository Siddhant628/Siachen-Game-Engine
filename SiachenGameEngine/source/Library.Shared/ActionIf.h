#pragma once
#include "ActionList.h"
#include "Factory.h"

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
		class ActionIf : public ActionList
		{
			RTTI_DECLARATIONS(ActionIf, ActionList)
		private:
			/**
			* An integer representing the condition which determines which branch to follow.
			*/
			std::int32_t mCondition;
		protected:
			/**
			* Populate the scope with prescribed attributes of this class.
			*/
			virtual void Populate() override;
		public:
			/**
			* Default constructor - Populates the prescribed attributes.
			*/
			ActionIf();
			/**
			* Destructor.
			*/
			~ActionIf() = default;
			/**
			* Updates the appropriate Action.
			* @param worldState A reference to the current world state.
			*/
			virtual void Update(WorldState& worldState);
		private:
			/**
			* Strings corresponding to keys in this scope.
			*/
			const static std::string sCondition;
		};
		ConcreteFactory(SiachenGameEngine::GameplayFramework::Action, ActionIf)
	}
}