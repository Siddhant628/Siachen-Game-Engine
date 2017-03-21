#pragma once
#include "RTTI.h"
#include"Vector.h"
#include "expat.h"
#include "HashMap.h"

namespace SiachenGameEngine
{
	namespace Parsers
	{
		class IXmlParseHelper;
		/**
		* An XML parser class which wraps Expat functionality for parsing it.
		*/
		class XmlParseMaster final
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
				* Destructor
				*/
				virtual ~SharedData() = default;
				/**
				* Initializes the shared memory object for use/reuse.
				*/
				virtual void Initialize();
				/**
				* Get a SharedData object with the same internal state as this one, but ready for a fresh file.
				* @return Address of the cloned SharedData object.
				*/
				virtual SharedData* Clone() = 0;
				/**
				* Set the address of the mParseMaster.
				* @param The address of the XmlParseMaster to set.
				*/
				void SetXmlParseMaster(XmlParseMaster& xmlParseMaster);
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
			/**
			* Constructor initializes this object and creates an Expat object with registered callbacks.
			* @param sharedData Reference to the shared memory that will be used by 
			*/
			XmlParseMaster(SharedData& sharedData);
			/**
			* Destructor deallocated dynamically allocated memory by parser, and for cloned parse masters.
			*/
			~XmlParseMaster();
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
			/**
			* Parse a character string buffer of a specified length.
			* @param buffer A character array containing the buffer which has to be parsed.
			* @param length The number of bytes in the buffer.
			* @param lastChunk Set to true if this is the last chunk of the data which has to be parsed.
			*/
			void Parse(const char* buffer, std::uint32_t length, bool lastChunk);
			/**
			* Parse the file with the given name.
			* @param fileName Name (with relative path) of the file to be parsed.
			*/
			void ParseFromFile(const std::string& fileName);
			/**
			* Get the path of the file parsed.
			* @return Path of the file being parsed.
			*/
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
			void SetSharedData(const SharedData& sharedData);
		private:
			/**
			* The central data structure for the Expat API.
			*/
			XML_Parser mParser;
			/**
			* Whether the master parser is a cloned one.
			*/
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
			* A pointer to the helper which is just handled the start of an element, used to call the appropriate character data handler.
			*/
			IXmlParseHelper* mCurrentHelper;

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
			static void CharDataHandler(void* userData, const char* str, std::int32_t length);
			/**
			* Get the hashmap of attribute name-value pairs from the array of name-value pairs. 
			* attributePairs An array of name-value pairs, terminated by 0s; names and values are 0 terminated.
			* attributeMap Output parameter. A hashmap containing all the name value pairs in attributePairs.
			*/
			void GetAttributePairHashmap(const char** attributePairs, Containers::HashMap<std::string, std::string>& attributeMap);
		};
	}
}