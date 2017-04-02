#include "pch.h"
#include "XmlParseHelperWorldMath.h"
#include <string>
#include "World.h"

using namespace SiachenGameEngine::Containers;
using namespace SiachenGameEngine::GameplayFramework;


namespace SiachenGameEngine
{
	namespace Parsers
	{
		XmlParseHelperWorldMath::XmlParseHelperWorldMath() : mSharedData(nullptr)
		{

		}

		void XmlParseHelperWorldMath::Initialize(XmlParseMaster::SharedData& sharedData)
		{
			mSharedData = sharedData.As<XmlSharedDataWorld>();
			if (!mSharedData)
			{
				throw std::runtime_error("Parser helper cannot use the provided type of shared data.");
			}
		}

		bool XmlParseHelperWorldMath::StartElementHandler(const std::string& elementName, const HashMap<std::string, std::string>& attributeHashmap)
		{
			if (elementName == "vector")
			{
				assert(attributeHashmap.ContainsKey("name") && attributeHashmap.ContainsKey("value"));
				Datum& datum = mSharedData->mCurrentScope->Append(attributeHashmap["name"]);
				// Transform vector into a parsable string
				std::string value = attributeHashmap["value"];
				value = "vec4" + value;
				// In case user passes an index to set at
				if (attributeHashmap.ContainsKey("index"))
				{
					datum.SetFromString(value, std::stoi(attributeHashmap["index"]));
				}
				// In case user doesn't pass any index for insert
				else
				{
					if (datum.IsExternal())
					{
						datum.SetFromString(value);
					}
					else
					{
						std::uint32_t index = datum.Size();
						datum.PushBack(glm::vec4());
						if (!datum.SetFromString(value, index))
						{
							datum.PopBack();
							return false;
						}
					}
				}
				return true;
			}
			return false;
		}

		bool XmlParseHelperWorldMath::EndElementHandler(const std::string& elementName)
		{
			return (elementName == "vector" || elementName == "matrix");
		}

		void XmlParseHelperWorldMath::CharDataHandler(const char* characterData, std::uint32_t size)
		{
			UNREFERENCED_PARAMETER(characterData);
			UNREFERENCED_PARAMETER(size);
		}

		IXmlParseHelper* XmlParseHelperWorldMath::Clone()
		{
			XmlParseHelperWorldMath* parseHelper = new XmlParseHelperWorldMath();
			parseHelper->mSharedData = mSharedData;
			return parseHelper;
		}
	}
}
