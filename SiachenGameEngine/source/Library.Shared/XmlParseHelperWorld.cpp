#include "XmlParseHelperWorld.h"
#include <string>

using namespace SiachenGameEngine::Containers;


namespace SiachenGameEngine
{
	namespace Parsers
	{
		XmlParseHelperWorld::XmlParseHelperWorld() : mSharedData(nullptr)
		{

		}

		void XmlParseHelperWorld::Initialize(XmlParseMaster::SharedData& sharedData)
		{
			mSharedData = sharedData.As<XmlSharedDataWorld>();
			if (!mSharedData)
			{
				throw std::runtime_error("Parser helper cannot use the provided type of shared data.");
			}
		}

		bool XmlParseHelperWorld::StartElementHandler(const std::string& elementName, const HashMap<std::string, std::string>& attributeHashmap)
		{
			if (elementName == "world")
			{
				if (attributeHashmap.ContainsKey("name"))
				{

				}
			}
			else if (elementName == "sector")
			{
				if (attributeHashmap.ContainsKey("name"))
				{

				}
			}
			else if (elementName == "entity")
			{
				if (attributeHashmap.ContainsKey("name"))
				{

				}
			}
			return false;
		}

		bool XmlParseHelperWorld::EndElementHandler(const std::string& elementName)
		{
			return (elementName == "world" || elementName == "sector" || elementName == "entity");
		}

		void XmlParseHelperWorld::CharDataHandler(const char* characterData, std::uint32_t size)
		{
			UNREFERENCED_PARAMETER(characterData);
			UNREFERENCED_PARAMETER(size);
		}

		IXmlParseHelper* XmlParseHelperWorld::Clone()
		{
			XmlParseHelperWorld* parseHelper = new XmlParseHelperWorld();
			parseHelper->mSharedData = mSharedData;
			return parseHelper;
		}
	}
}
