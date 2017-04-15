#pragma once

#include "Reaction.h"
#include "Factory.h"

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
		class ReactionAttributed final : public Reaction
		{
			RTTI_DECLARATIONS(ReactionAttributed, Reaction)
		private:
			/**
			* A datum with event subtypes to which this reaction can react.
			*/
			Containers::Datum* mSubtypes;
			/**
			* String constants.
			*/
			const static std::string sSubtypes;
			/**
			* Check whether an event has the same subtype as supported by this subscriber.
			* @param eventObject The event whose subtype has to be compared to this reactions supported subtype.
			*/
			bool SubtypeCheck(const Events::EventPublisher& eventObject);
		protected:
			/**
			* Populate the scope with prescribed attributes of this class.
			*/
			virtual void Populate() override;
		public:
			/**
			* Populate the scope with prescribed attributes.
			*/
			ReactionAttributed();
			/**
			* Destructor.
			*/
			~ReactionAttributed();
			// TODO Make a copy of scope types?
			/**
			* The receiver of the event which takes the event object as a parameter.
			*/
			virtual void Notify(const Events::EventPublisher& eventObject) override;
		};
		ConcreteFactory(Reaction, ReactionAttributed)
	}
}