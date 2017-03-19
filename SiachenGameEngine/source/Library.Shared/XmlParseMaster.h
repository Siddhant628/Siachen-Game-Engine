#pragma once
#include "RTTI.h"
#include "IXmlParseHelper.h"
#include"Vector.h"

namespace SiachenGameEngine
{
	namespace Parsers
	{
		/**
		* An XML parser class which wraps Expat functionality for parsing it.
		*/
		class XmlParseMaster
		{
		public:
			/**
			* Data shared between helper classes and with the master parser. 
			*/
			class SharedData : public GameplayFramework::RTTI
			{
				RTTI_DECLARATIONS(SharedData, RTTI)
			private:
				/**
				* The parse master associated with this object.
				*/
				XmlParseMaster* mParseMaster;
				/**
				* The depth due to nesting of elements.
				*/
				std::uint32_t mDepth;
			public:
				/**
				* Default Constructor - Initializes values.
				*/
				SharedData();
				/**
				* Get a SharedData object with the same internal state as this one, but ready for a fresh file.
				* @return Address of the cloned SharedData object.
				*/
				virtual SharedData* Clone() = 0;
				/**
				* Set the address of the mParseMaster.
				* @param The address of the XmlParseMaster to set.
				*/
				void SetXmlParseMaster(const XmlParseMaster* xmlParseMaster);
				/**
				* Get the address of the mParseMaster.
				* @return The address of the mParseMaster.
				*/
				XmlParseMaster* GetXmlParseMaster() const;
				/**
				* Increment the nesting depth counter.
				*/
				void IncrementDepth();
				/**
				* Decrement the nesting depth counter.
				*/
				void DecrementDepth();
				/**
				* Get the nested depth counter.
				* @return The nesting depth counter.
				*/
				std::uint32_t Depth() const;
			};
			// TODO Implement
			XmlParseMaster(SharedData* sharedData);
			// TODO Implement. Delete the helpers of the clones since they own them.
			~XmlParseMaster();
			// TODO Implement. How would copying work for the XML Parser object since it doesn't have support for it. Making a new one with identical handlers, etc?
			/**
			* Make a duplicate of this object which is ready to parse a fresh file. 
			* @return Address of the duplicate of this object.
			*/
			XmlParseMaster* Clone();
			/**
			* Add the parsing helper to the helper list.
			* @param helper A reference to the parsing helper which has to be added to the helper list.
			*/
			void AddHelper(const IXmlParseHelper& helper);
			/**
			* Remove the parsing helper from the helper list.
			* @param helper A reference to the parsing helper which has to be removed from the helper list.
			* @return True if the helper was successfully removed from the list.
			*/
			bool RemoveHelper(const IXmlParseHelper& helper);
			// TODO Implement 
			void Parse(const char* buffer, std::uint32_t length);
			// TODO Implement
			void ParseFromFile(const std::string& fileName);
			// TODO Implement
			const std::string& GetFileName() const;
			/**
			* Get the address of associated shared data.
			* @return Address of the shared data.
			*/
			SharedData* GetSharedData() const;
			/**
			* Set the address of the associated shared data.
			* @param sharedData The address of the shared data to associate with this object.
			*/
			void SetSharedData(const SharedData* sharedData);
		private:
			// TODO Check Needed?
			bool mIsClone;
			/**
			* Shared data associated with this object.
			*/
			SharedData* mSharedData;
			/**
			* The name of the file being parsed.
			*/
			std::string mFileName;
			/**
			* A vector of parsing helpers associated with this object.
			*/
			SiachenGameEngine::Containers::Vector<IXmlParseHelper*> mHelperList;

			/**
			* Handles the start of an element in XML.
			* @param userData  A value to be passed to each handler during the parse.
			* @param element The name of the element in XML.
			* @param attribute An array of attribute name-value pairs.
			*/
			static void StartElementHandler(void* userData, const char* element, const char** attribute);
			/**
			* Handles the end of an element in XML.
			* @param userData  A value to be passed to each handler during the parse.
			* @param element The name of the element in XML.
			*/
			static void EndElementHandler(void* userData, const char* element);
			/**
			* Handles the character data in XML.
			* @param userData  A value to be passed to each handler during the parse.
			* @param length The number of bytes in the data.
			*/
			static void CharElementHandler(void* userData, const char* str, std::int32_t length);
		};
	}
}