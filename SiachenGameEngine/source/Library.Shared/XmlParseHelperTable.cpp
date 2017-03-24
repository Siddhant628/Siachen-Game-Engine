#include "XmlParseHelperTable.h"
#include "Scope.h"

using namespace SiachenGameEngine::GameplayFramework;

namespace SiachenGameEngine
{
	namespace Parsers
	{
		void XmlParseHelperTable::Initialize(XmlParseMaster::SharedData& sharedData)
		{
			mSharedData = sharedData.As<XmlSharedDataTable>();
			if (!mSharedData)
			{
				throw std::runtime_error("Parser helper cannot use the provided type of shared data.");
			}
		}
		
		bool XmlParseHelperTable::StartElementHandler(const std::string& elementName, const Containers::HashMap<std::string, std::string>& attributeHashmap)
		{
			if (elementName == "Scope")
			{
				if (!mSharedData->mScope)
				{
					mSharedData->mScope = new Scope();
				}
				else
				{
					// TODO In case of a nested scope.
					attributeHashmap;
				}
				return true;
			}
			return false;
		}
		
		bool XmlParseHelperTable::EndElementHandler(const std::string& elementName)
		{
			return (elementName == "Scope");
		}

		void XmlParseHelperTable::CharDataHandler(const char* characterData, std::uint32_t size)
		{
			UNREFERENCED_PARAMETER(characterData);
			UNREFERENCED_PARAMETER(size);
		}

		IXmlParseHelper* XmlParseHelperTable::Clone()
		{
			return nullptr;
		}
	}
}