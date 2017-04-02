#include "XmlParseHelperMath.h"

using namespace SiachenGameEngine::Containers;

namespace SiachenGameEngine
{
	namespace Parsers
	{
		XmlParseHelperMath::XmlParseHelperMath() : mSharedData(nullptr)
		{

		}

		void XmlParseHelperMath::Initialize(XmlParseMaster::SharedData& sharedData)
		{
			mSharedData = sharedData.As<XmlSharedDataTable>();
			if (!mSharedData)
			{
				throw std::runtime_error("Parser helper cannot use the provided type of shared data.");
			}
		}

		bool XmlParseHelperMath::StartElementHandler(const std::string& elementName, const Containers::HashMap<std::string, std::string>& attributeHashmap)
		{
			if (elementName == "vector")
			{
				if (attributeHashmap.ContainsKey("name") && attributeHashmap.ContainsKey("value"))
				{
					std::string name = attributeHashmap["name"];
					
					std::string value = attributeHashmap["value"];
					value = "vec4" + value;

					Datum& datum = (*mSharedData->mScope)[name];
					std::uint32_t index = datum.Size();
					datum.PushBack(glm::vec4());

					if (!datum.SetFromString(value, index))
					{
						datum.PopBack();
					}
					return true;
				}
			}
			else if (elementName == "matrix")
			{
				if (attributeHashmap.ContainsKey("name") && attributeHashmap.ContainsKey("value"))
				{
					std::string name = attributeHashmap["name"];

					std::string value = attributeHashmap["value"];
					value = "mat4x4" + value;

					Datum& datum = (*mSharedData->mScope)[name];
					std::uint32_t index = datum.Size();
					datum.PushBack(glm::mat4x4());

					if (!datum.SetFromString(value, index))
					{
						datum.PopBack();
					}
					return true;
				}
			}
			
			return false;
		}

		bool XmlParseHelperMath::EndElementHandler(const std::string & elementName)
		{
			return (elementName == "vector" || elementName == "matrix");
		}

		void XmlParseHelperMath::CharDataHandler(const char* characterData, std::uint32_t size)
		{
			UNREFERENCED_PARAMETER(characterData);
			UNREFERENCED_PARAMETER(size);
		}

		IXmlParseHelper* XmlParseHelperMath::Clone()
		{
			XmlParseHelperMath* parseHelper = new XmlParseHelperMath();
			parseHelper->mSharedData = mSharedData;
			return parseHelper;
		}
	}
}