#include "pch.h"
#include "SampleXmlParseHelper.h"

namespace SiachenGameEngine
{
	namespace HelperClasses
	{
		void SampleXmlParseHelper::Initialize()
		{

		}

		bool SampleXmlParseHelper::StartElementHandler(const char* elementName, Containers::HashMap<std::string, std::string> attributeHashmap)
		{
			if (!strcmp(elementName, "Students"))
			{
				return true;
			}
			else if (!strcmp(elementName, "Student"))
			{
				return true;
			}
			return false;
		}

		bool SampleXmlParseHelper::EndElementHandler(const char* elementName)
		{
			elementName;
			return false;
		}

		bool SampleXmlParseHelper::CharDataHandler(const char* characterData, std::int32_t size)
		{
			characterData;
			size;
			return false;
		}

		Parsers::IXmlParseHelper* SampleXmlParseHelper::Clone()
		{
			return nullptr;
		}
	}
}