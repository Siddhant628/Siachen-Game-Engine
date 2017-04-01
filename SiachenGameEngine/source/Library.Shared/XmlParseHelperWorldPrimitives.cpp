#include "pch.h"
#include "XmlParseHelperWorldPrimitives.h"
#include <string>
#include "World.h"

using namespace SiachenGameEngine::Containers;
using namespace SiachenGameEngine::GameplayFramework;


namespace SiachenGameEngine
{
	namespace Parsers
	{
		XmlParseHelperWorldPrimitives::XmlParseHelperWorldPrimitives() : mSharedData(nullptr)
		{

		}

		void XmlParseHelperWorldPrimitives::Initialize(XmlParseMaster::SharedData& sharedData)
		{
			mSharedData = sharedData.As<XmlSharedDataWorld>();
			if (!mSharedData)
			{
				throw std::runtime_error("Parser helper cannot use the provided type of shared data.");
			}
		}

		bool XmlParseHelperWorldPrimitives::StartElementHandler(const std::string& elementName, const HashMap<std::string, std::string>& attributeHashmap)
		{
			if (elementName == "integer")
			{
				if (attributeHashmap.ContainsKey("name") && attributeHashmap.ContainsKey("value"))
				{
					std::string name = attributeHashmap["name"];
					Datum& datum = mSharedData->mCurrentScope->Append(name);
					if (datum.IsExternal())
					{
						datum.Set(std::stoi(attributeHashmap["value"]));
					}
					else
					{
						datum.PushBack(std::stoi(attributeHashmap["value"]));
					}
					return true;
				}
			}
			else if (elementName == "float")
			{
				if (attributeHashmap.ContainsKey("name") && attributeHashmap.ContainsKey("value"))
				{
					std::string name = attributeHashmap["name"];
					Datum& datum = mSharedData->mCurrentScope->Append(name);
					if (datum.IsExternal())
					{ 
						datum.Set(std::stof(attributeHashmap["value"]));
					}
					else
					{
						datum.PushBack(std::stof(attributeHashmap["value"]));
					}
					return true;
				}
			}
			return false;
		}

		bool XmlParseHelperWorldPrimitives::EndElementHandler(const std::string& elementName)
		{
			return (elementName == "integer" || elementName == "float");
		}

		void XmlParseHelperWorldPrimitives::CharDataHandler(const char* characterData, std::uint32_t size)
		{
			UNREFERENCED_PARAMETER(characterData);
			UNREFERENCED_PARAMETER(size);
		}

		IXmlParseHelper* XmlParseHelperWorldPrimitives::Clone()
		{
			XmlParseHelperWorldPrimitives* parseHelper = new XmlParseHelperWorldPrimitives();
			parseHelper->mSharedData = mSharedData;
			return parseHelper;
		}
	}
}
