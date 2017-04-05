#pragma once
#include "Action.h"
#include "Factory.h"

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
		private:
			/**
			* A pointer to actions contained within this entity.
			*/
			Containers::Datum* mActionDatum;
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
			/**
			* Get a reference to the datum containing the actions.
			*/
			Containers::Datum& Actions() const;
			/**
			* Adopt a Action into this ActionList.
			* @param action The Action which has to be adopted.
			*/
			void AdoptAction(Action& action);
			/**
			* Create an Action using the Action factory and adopts it into this Entity.
			* @param className The name of the Action class which has to be instantiated.
			* @param instanceName The name that the new Action class object will take.
			* @return A pointer to the created Action.
			*/
			Action* CreateAction(const std::string& className, const std::string& instanceName);
		private:
			static const std::string sActionList;
		};
		ConcreteFactory(SiachenGameEngine::GameplayFramework::Action, ActionList)
	}
}