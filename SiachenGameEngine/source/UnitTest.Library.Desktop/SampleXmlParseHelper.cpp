#include "pch.h"
#include "SampleXmlParseHelper.h"


namespace SiachenGameEngine
{
	namespace HelperClasses
	{
		SampleXmlParseHelper::SampleXmlParseHelper() : mSharedData(nullptr)
		{

		}

		void SampleXmlParseHelper::Initialize(Parsers::XmlParseMaster::SharedData& sharedData)
		{
			mSharedData = (&sharedData)->As<SampleXmlSharedData>();
			if (!mSharedData)
			{
				throw std::runtime_error("Helper cannot use the provided shared data.");
			}
		}

		bool SampleXmlParseHelper::StartElementHandler(const std::string& elementName, const Containers::HashMap<std::string, std::string>& attributeHashmap)
		{
			// In case of elements who don't have attributes, or data isn't being retrieved from attributes
			if (elementName == "Class" || elementName == "FirstName" || elementName == "LastName" || elementName == "Name")
			{
				mSharedData->SetCurrentElement(elementName);
				return true;
			}
			// In case of a Student element tag
			else if (elementName == "Student")
			{
				mSharedData->SetCurrentElement(elementName);
				if (attributeHashmap.Size() == 2)
				{
					std::string firstName = attributeHashmap["FirstName"];
					std::string lastName = attributeHashmap["LastName"];
					mSharedData->GetStringPairVector().PushBack(std::make_pair(firstName, lastName));
				}
				return true;
			}
			return false;
		}

		bool SampleXmlParseHelper::EndElementHandler(const std::string& elementName)
		{
			if (elementName == "Class" || elementName == "Student" || elementName == "FirstName" || elementName == "LastName" || elementName == "Name")
			{
				return true;
			}
			return false;
		}

		void SampleXmlParseHelper::CharDataHandler(const char* characterData, std::uint32_t size)
		{
			std::string currentElement = mSharedData->GetCurrentElement();
			if ( currentElement == "FirstName")
			{
				std::string firstName(characterData, size);
				mSharedData->GetStringPairVector().PushBack(make_pair(firstName, ""));
			}
			else if(currentElement == "LastName")
			{
				std::string lastName(characterData, size);
				std::uint32_t position = mSharedData->GetStringPairVector().Size() - 1;
				mSharedData->GetStringPairVector().At(position).second = lastName;
			}
		}

		Parsers::IXmlParseHelper* SampleXmlParseHelper::Clone()
		{
			SampleXmlParseHelper* parseHelper = new SampleXmlParseHelper();
			parseHelper->mSharedData = mSharedData;
			
			return parseHelper;
		}
	}
}