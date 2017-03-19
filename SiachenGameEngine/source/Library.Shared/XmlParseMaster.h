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
				XmlParseMaster* parseMaster;
				/**
				* The depth due to nesting of elements.
				*/
				std::uint32_t depth;
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
				* Set the value of the parseMaster.
				* @param The address of the XmlParseMaster to set.
				*/
				void SetXmlParseMaster(const XmlParseMaster* xmlParseMaster);
				/**
				* Get the value of the parseMaster.
				* @return The address of the parseMaster.
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
			// TODO Understand
			XmlParseMaster(SharedData* sharedData);
			// TODO Understand
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
			*/
			void RemoveHelper(const IXmlParseHelper& helper);
			// TODO Understand 
			void Parse();
			// TODO Understand
			void ParseFromFile();
			// TODO Understand
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
			// TODO Check Is it needed? Comment.
			bool isClone;
			/**
			* Shared data associated with this object.
			*/
			SharedData* sharedData;
			/**
			* A vector of parsing helpers associated with this object.
			*/
			SiachenGameEngine::Containers::Vector<IXmlParseHelper*> helperList;
			// TODO Understand
			void StartElementHandler();
			void EndElementHandler();
			void CharElementHandler();
		};
	}
}