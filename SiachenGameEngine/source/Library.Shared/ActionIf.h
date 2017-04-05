#pragma once
#include "Action.h"
#include "Factory.h"

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
		class ActionIf : public Action
		{
			RTTI_DECLARATIONS(ActionIf, Action)
		private:
			/**
			* A pointer to the datum containing pointers to the action which is executed if condition is true.
			*/
			Containers::Datum* mThenDatum;
			/**
			* A pointer to the datum containing pointers to the action which is executed if condition is false.
			*/
			Containers::Datum* mElseDatum;
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
			const static std::string sThen;
			const static std::string sElse;
			const static std::string sCondition;
		};
		// TODO Test
		ActionFactory(ActionIf)
	}
}