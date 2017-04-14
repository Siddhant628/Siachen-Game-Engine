#pragma once
#include "Attributed.h"
#include "World.h"

namespace SiachenGameEngine
{
	namespace Events
	{
		/**
		* A generic event message which is used across the engine.
		*/
		class EventMessageAttributed final: public GameplayFramework::Attributed
		{
			RTTI_DECLARATIONS(EventMessageAttributed, Attributed)
		private:
			/**
			* A string representing the subtype of this event.
			*/
			std::string mSubtype;
			/**
			* A pointer to the world which processes this message.
			*/
			const GameplayFramework::World* mWorld;
		protected:
			/**
			* Populate the scope with prescribed attributes of this class.
			*/
			virtual void Populate() override;
		public:
			/**
			* Populate the scope with prescribed attributes.
			*/
			EventMessageAttributed();
			/**
			* Destructor.
			*/
			~EventMessageAttributed() = default;
			/**
			* Set the string indicating the subtype of this event.
			* @param subtype A string representing the subtype of this event.
			*/
			void SetSubtype(const std::string& subtype);
			/**
			* Get the string indicating the subtype of this event.
			* @return A string representing the subtype of this event.
			*/
			const std::string& GetSubtype() const;
			/**
			* Set the world that processes this message.
			* @param world A reference to the world which processes this message.
			*/
			void SetWorld(const GameplayFramework::World& world);
			/**
			* Get the world that processes this message.
			* @return A reference to the world which processes this message.
			*/
			const GameplayFramework::World& GetWorld() const;
		};
	}
}