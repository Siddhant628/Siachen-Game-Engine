#pragma once
#include "XmlParseMaster.h"
#include "Scope.h"

namespace SiachenGameEngine
{
	namespace Parsers
	{
		/**
		* A concrete shared data class, used for parsing of tables (Scopes) from XML.
		*/
		class XmlSharedDataTable final : public XmlParseMaster::SharedData
		{
			// TODO Check if required
			friend class XmlParseHelperTable;
			friend class XmlParseHelperInteger;
			RTTI_DECLARATIONS(XmlSharedDataTable, XmlParseMaster::SharedData)
		public:
			/**
			* Default constructor initializes values.
			*/
			XmlSharedDataTable();
			/**
			* Destructor.
			*/
			~XmlSharedDataTable();
			/**
			* Initializes the shared memory object for use/reuse.
			*/
			virtual void Initialize() override;
			// TODO Implement
			/**
			* Get a SharedData object with the same internal state as this one, but ready for a fresh file.
			* @return Address of the cloned SharedData object.
			*/
			virtual SharedData* Clone() override;
			// TODO Confirm Making the scope public
			/**
			* A scope which will contain all the data parsed from the XML.
			*/
			GameplayFramework::Scope* GetSharedScope() const;
		private:
			// TODO Confirm Private / Public?
			GameplayFramework::Scope* mScope;


		};
	}
}