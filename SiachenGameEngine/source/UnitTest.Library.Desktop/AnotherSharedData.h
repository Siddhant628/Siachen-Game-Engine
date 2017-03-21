#pragma once
#include "XmlParseMaster.h"


namespace SiachenGameEngine
{
	namespace HelperClasses
	{
		/**
		* A concrete shared data class implemented for testing purposes only.
		*/
		class AnotherSharedData final : public Parsers::XmlParseMaster::SharedData
		{
			RTTI_DECLARATIONS(AnotherSharedData, Parsers::XmlParseMaster::SharedData)
		public:
			/**
			* Default constructor.
			*/
			AnotherSharedData() = default;
			/**
			* Destructor does nothing.
			*/
			~AnotherSharedData() = default;
			/**
			* Initializes the shared memory object for use/reuse.
			*/
			virtual void Initialize() override;
			/**
			* Get a SharedData object with the same internal state as this one, but ready for a fresh file.
			* @return Address of the cloned SharedData object.
			*/
			virtual SharedData* Clone() override;
		private:
		};
	}
}