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
			if (elementName == "Vector")
			{
				if (attributeHashmap.ContainsKey("Name") && attributeHashmap.ContainsKey("Value"))
				{
					std::string name = attributeHashmap["Name"];
					
					std::string value = attributeHashmap["Value"];
					value = "vec4" + value;

					Datum& datum = (*mSharedData->mScope)[name];
					std::uint32_t index = datum.Size();
					datum.PushBack(glm::vec4());

					if (!datum.SetFromString(value, index))
					{
						datum.PopBack();
						return false;
					}
					return true;
				}
			}
			else if (elementName == "Matrix")
			{
				if (attributeHashmap.ContainsKey("Name") && attributeHashmap.ContainsKey("Value"))
				{
					std::string name = attributeHashmap["Name"];

					std::string value = attributeHashmap["Value"];
					value = "mat4x4" + value;

					Datum& datum = (*mSharedData->mScope)[name];
					std::uint32_t index = datum.Size();
					datum.PushBack(glm::mat4x4());

					if (!datum.SetFromString(value, index))
					{
						datum.PopBack();
						return false;
					}
					return true;
				}
			}
			
			return false;
		}

		bool XmlParseHelperMath::EndElementHandler(const std::string & elementName)
		{
			return (elementName == "Vector" || elementName == "Matrix");
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
