#pragma once
#include "Attributed.h"
#include "WorldState.h"

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
		/**
		* Actions affect the state of the attributed scopes containing them. They are the verbs corresponding to nouns such as entities, sectors or world.
		*/
		class Action : public Attributed
		{
			RTTI_DECLARATIONS(Action, Attributed)
		private:
			/**
			* Name of this Action.
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
			Action();
			/**
			* Destructor.
			*/
			virtual ~Action() = default;
			/**
			* Get the name of the Action.
			* @return The name of the Action as a string.
			*/
			const std::string& Name() const;
			/**
			* Set the name of the Action.
			* @param actionName The name (string) which has to be set as the name of the Entity.
			*/
			void SetName(const std::string& actionName);
			/**
			* Updates the Action.
			* @param worldState A reference to the current world state.
			*/
			virtual void Update(WorldState& worldState) = 0;
		};
	}
}

// TODO Test
#define ActionFactory(ConcreteActionT) ConcreteFactory(SiachenGameEngine::GameplayFramework::Action, ConcreteActionT)