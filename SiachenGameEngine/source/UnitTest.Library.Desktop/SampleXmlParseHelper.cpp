#include "pch.h"
#include "SampleXmlParseHelper.h"


namespace SiachenGameEngine
{
	namespace HelperClasses
	{
		void SampleXmlParseHelper::Initialize(Parsers::XmlParseMaster::SharedData* sharedData)
		{
			IXmlParseHelper::Initialize(sharedData);
		}

		bool SampleXmlParseHelper::StartElementHandler(const std::string& elementName, Containers::HashMap<std::string, std::string> attributeHashmap)
		{
			if (elementName == "Students")
			{
				return true;
			}
			else if (elementName == "Student")
			{

				return true;
			}
			return false;
		}

		bool SampleXmlParseHelper::EndElementHandler(const std::string& elementName)
		{
			elementName;
			return false;
		}

		void SampleXmlParseHelper::CharDataHandler(const char* characterData, std::uint32_t size)
		{
			characterData;
			size;
		}

		Parsers::IXmlParseHelper* SampleXmlParseHelper::Clone()
		{
			return nullptr;
		}
	}
}