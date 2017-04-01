#pragma once
#include "XmlParseMaster.h"
#include "Scope.h"
#include "World.h"
#include "Sector.h"
#include "Entity.h"

namespace SiachenGameEngine
{
	namespace Parsers
	{
		/**
		* A concrete shared data class, used for parsing of worlds ( and their internal content) from XML.
		*/
		class XmlSharedDataWorld final : public XmlParseMaster::SharedData
		{
			RTTI_DECLARATIONS(XmlSharedDataWorld, XmlParseMaster::SharedData)
		public:
			/**
			* Default constructor initializes values.
			*/
			XmlSharedDataWorld();
			/**
			* Destructor.
			*/
			~XmlSharedDataWorld();
			/**
			* Initializes the shared memory object for use/reuse.
			*/
			virtual void Initialize() override;
			/**
			* Get a SharedData object with the same internal state as this one, but ready for a fresh file.
			* @return Address of the cloned SharedData object.
			*/
			virtual SharedData* Clone() override;
		public:
			/**
			* A pointer to the current world which is being processed.
			*/
			GameplayFramework::World* mCurrentWorld;
			/**
			* A pointer to the current sector which is being processed.
			*/
			GameplayFramework::Sector* mCurrentSector;
			/**
			* A pointer to the current entity which is being processed.
			*/
			GameplayFramework::Entity* mCurrentEntity;
		};
	}
}