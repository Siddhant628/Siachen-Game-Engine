#pragma once
#include "Action.h"
#include "Factory.h"

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
		class ActionEvent final : public Action
		{
			RTTI_DECLARATIONS(ActionEvent, Action)
		private:
			/**
			* The subtype of event which has to be generated.
			*/
			std::string mSubtype;
			/**
			* The delay associated with this generated event.
			*/
			std::int32_t mDelay;
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
			/**
			* Updates the Action.
			* @param worldState A reference to the current world state.
			*/
			virtual void Update(WorldState& worldState) override;
		};
		ConcreteFactory(SiachenGameEngine::GameplayFramework::Action, ActionEvent)
	}
}
