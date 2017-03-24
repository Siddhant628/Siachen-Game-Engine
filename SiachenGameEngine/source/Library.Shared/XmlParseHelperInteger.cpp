#include "XmlParseHelperInteger.h"
#include <string>

using namespace SiachenGameEngine::Containers;

namespace SiachenGameEngine
{
	namespace Parsers
	{
		XmlParseHelperInteger::XmlParseHelperInteger() : mSharedData(nullptr)
		{

		}

		void XmlParseHelperInteger::Initialize(XmlParseMaster::SharedData& sharedData)
		{
			mSharedData = sharedData.As<XmlSharedDataTable>();
			if (!mSharedData)
			{
				throw std::runtime_error("Parser helper cannot use the provided type of shared data.");
			}
		}

		bool XmlParseHelperInteger::StartElementHandler(const std::string& elementName, const HashMap<std::string, std::string>& attributeHashmap)
		{
			if (elementName == "Integer")
			{
				ValidateAttributeHashmap(attributeHashmap);
				// Extract data from the start element tag
				std::string name;
				std::int32_t value;

				HashMap<std::string, std::string>::Iterator it = attributeHashmap.Find("Name");
				name = (*it).second;
				
				it = attributeHashmap.Find("Value");
				if (it == attributeHashmap.end())
				{
					throw std::runtime_error("The integer must have a value.");
				}
				value = std::stoi((*it).second);
				// Update the shared data scope
				(*mSharedData->mScope)[name].PushBack(value);
				return true;
			}
			return false;
		}

		bool XmlParseHelperInteger::EndElementHandler(const std::string & elementName)
		{
			return (elementName == "Integer");
		}

		void XmlParseHelperInteger::CharDataHandler(const char* characterData, std::uint32_t size)
		{
			UNREFERENCED_PARAMETER(characterData);
			UNREFERENCED_PARAMETER(size);
		}

		IXmlParseHelper* XmlParseHelperInteger::Clone()
		{
			XmlParseHelperInteger* parseHelper = new XmlParseHelperInteger();
			parseHelper->mSharedData = mSharedData;

			return parseHelper;
		}
	}
}
