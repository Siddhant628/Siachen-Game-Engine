#pragma once
#include "GameTime.h"

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
		class WorldState final
		{
		private:
			Library::GameTime mGameTime;
		public:
			/**
			* Address of the World being processed.
			*/
			class World* mWorld;
			/**
			* Address of the Sector being processed.
			*/
			class Sector* mSector;
			/**
			* Address of the Entity being processed.
			*/
			class Entity* mEntity;
			/**
			* Address of the Action being processed.
			*/
			class Action* mAction;
		public:
			/**
			* Default constructor initializes values.
			*/
			WorldState();
			/**
			* Set the game time.
			* @param gameTime The game time to be set in the world state.
			*/
			void SetGameTime(const Library::GameTime& gameTime);
			/**
			* Get the game time.
			* @return The game time object for the current world state.
			*/
			const Library::GameTime& GetGameTime() const;
		};
	}
}