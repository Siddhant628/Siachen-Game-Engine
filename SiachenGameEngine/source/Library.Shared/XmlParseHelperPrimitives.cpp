#include "XmlParseHelperPrimitives.h"
#include <string>

using namespace SiachenGameEngine::Containers;

namespace SiachenGameEngine
{
	namespace Parsers
	{
		XmlParseHelperPrimitives::XmlParseHelperPrimitives() : mSharedData(nullptr)
		{

		}

		void XmlParseHelperPrimitives::Initialize(XmlParseMaster::SharedData& sharedData)
		{
			mSharedData = sharedData.As<XmlSharedDataTable>();
			if (!mSharedData)
			{
				throw std::runtime_error("Parser helper cannot use the provided type of shared data.");
			}
		}

		bool XmlParseHelperPrimitives::StartElementHandler(const std::string& elementName, const HashMap<std::string, std::string>& attributeHashmap)
		{
			if (elementName == "integer")
			{
				if (attributeHashmap.ContainsKey("name") && attributeHashmap.ContainsKey("value"))
				{
					std::int32_t value = std::stoi(attributeHashmap["value"]);
					std::string name = attributeHashmap["name"];
					// Update the shared data scope
					(*mSharedData->mScope)[name].PushBack(value);
					return true;
				}
			}
			else if (elementName == "float")
			{
				if (attributeHashmap.ContainsKey("name") && attributeHashmap.ContainsKey("value"))
				{
					std::float_t value = std::stof(attributeHashmap["value"]);
					std::string name = attributeHashmap["name"];
					// Update the shared data scope
					(*mSharedData->mScope)[name].PushBack(value);
					return true;
				}
			}
			else if (elementName == "string")
			{
				if (attributeHashmap.ContainsKey("name") && attributeHashmap.ContainsKey("value"))
				{
					std::string value = attributeHashmap["value"];
					std::string name = attributeHashmap["name"];
					// Update the shared data scope
					(*mSharedData->mScope)[name].PushBack(value);
					return true;
				}
			}
			return false;
		}

		bool XmlParseHelperPrimitives::EndElementHandler(const std::string& elementName)
		{
			return (elementName == "integer" || elementName == "float" || elementName == "string");
		}

		void XmlParseHelperPrimitives::CharDataHandler(const char* characterData, std::uint32_t size)
		{
			UNREFERENCED_PARAMETER(characterData);
			UNREFERENCED_PARAMETER(size);
		}

		IXmlParseHelper* XmlParseHelperPrimitives::Clone()
		{
			XmlParseHelperPrimitives* parseHelper = new XmlParseHelperPrimitives();
			parseHelper->mSharedData = mSharedData;
			return parseHelper;
		}
	}
}
