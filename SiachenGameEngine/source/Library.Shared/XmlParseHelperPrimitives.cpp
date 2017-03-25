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
			if (elementName == "Integer")
			{
				if (attributeHashmap.ContainsKey("Name") && attributeHashmap.ContainsKey("Value"))
				{
					std::int32_t value = std::stoi(attributeHashmap["Value"]);
					std::string name = attributeHashmap["Name"];
					// Update the shared data scope
					(*mSharedData->mScope)[name].PushBack(value);
					return true;
				}
			}
			else if (elementName == "Float")
			{
				if (attributeHashmap.ContainsKey("Name") && attributeHashmap.ContainsKey("Value"))
				{
					std::float_t value = std::stof(attributeHashmap["Value"]);
					std::string name = attributeHashmap["Name"];
					// Update the shared data scope
					(*mSharedData->mScope)[name].PushBack(value);
					return true;
				}
			}
			else if (elementName == "String")
			{
				if (attributeHashmap.ContainsKey("Name") && attributeHashmap.ContainsKey("Value"))
				{
					std::string value = attributeHashmap["Value"];
					std::string name = attributeHashmap["Name"];
					// Update the shared data scope
					(*mSharedData->mScope)[name].PushBack(value);
					return true;
				}
			}
			return false;
		}

		bool XmlParseHelperPrimitives::EndElementHandler(const std::string& elementName)
		{
			return (elementName == "Integer" || elementName == "Float" || elementName == "String");
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
