#pragma once

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
		class WorldState final
		{
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
			// TODO Implement
			void SetGameTime();
			// TODO Implement
			void GetGameTime();
			// TODO Confirm if the state is public
		};
	}
}