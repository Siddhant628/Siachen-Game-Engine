#pragma once
#include "XmlParseMaster.h"
#include "Vector.h"

namespace SiachenGameEngine
{
	namespace HelperClasses
	{
		class SampleXmlSharedData final : public Parsers::XmlParseMaster::SharedData
		{
			RTTI_DECLARATIONS(SampleXmlSharedData, Parsers::XmlParseMaster::SharedData)
		public:
			SampleXmlSharedData() = default;

			~SampleXmlSharedData() = default;
			/**
			* Initializes the shared memory object for use/reuse.
			*/
			virtual void Initialize() override;

			virtual SharedData* Clone() override;
			/**
			* Set current element.
			* @param elementName The name to set.
			*/
			void SetCurrentElement(const std::string& elementName);
			/**
			* Get the current element name.
			* @return The current element name.
			*/
			const std::string& GetCurrentElement() const;
			/**
			* Get the array of string pairs.
			* @return A reference to the array of string pairs.
			*/
			Containers::Vector<std::pair<std::string, std::string>>& GetStringPairVector();
		private:
			/**
			* An array of string pairs. Used to store names for testing.
			*/
			Containers::Vector<std::pair<std::string,std::string>> mStringPairVector;
			/**
			* The current element name which is being parsed.
			*/
			std::string mCurrentElement;
		};
	}
}