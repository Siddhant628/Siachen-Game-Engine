#include "pch.h"
#include "SampleXmlParseHelper.h"


namespace SiachenGameEngine
{
	namespace HelperClasses
	{
		SampleXmlParseHelper::SampleXmlParseHelper() : mSharedData(nullptr)
		{

		}

		void SampleXmlParseHelper::Initialize(Parsers::XmlParseMaster::SharedData* sharedData)
		{
			mSharedData = sharedData->As<SampleXmlSharedData>();
			if (!mSharedData)
			{
				throw std::runtime_error("Helper cannot use the provided shared data.");
			}
		}

		bool SampleXmlParseHelper::StartElementHandler(const std::string& elementName, Containers::HashMap<std::string, std::string> attributeHashmap)
		{
			if (elementName == "Class")
			{
				mSharedData->IncrementDepth();
				return true;
			}
			else if (elementName == "Student")
			{
				mSharedData->IncrementDepth();
				std::string firstName = attributeHashmap["FirstName"];
				std::string lastName = attributeHashmap["LastName"];
				mSharedData->GetStringPairVector().PushBack(std::make_pair(firstName, lastName));
				return true;
			}
			return false;
		}

		bool SampleXmlParseHelper::EndElementHandler(const std::string& elementName)
		{
			if (elementName == "Class" || elementName == "Student")
			{
				mSharedData->DecrementDepth();
				return true;
			}
			return false;
		}

		// TODO Implement
		void SampleXmlParseHelper::CharDataHandler(const char* characterData, std::uint32_t size)
		{
			UNREFERENCED_PARAMETER(characterData);
			UNREFERENCED_PARAMETER(size);
		}

		// TODO Implement
		Parsers::IXmlParseHelper* SampleXmlParseHelper::Clone()
		{
			return nullptr;
		}
	}
}