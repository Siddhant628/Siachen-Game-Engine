#include "XmlParseHelperTable.h"
#include "Scope.h"

using namespace SiachenGameEngine::GameplayFramework;

namespace SiachenGameEngine
{
	namespace Parsers
	{
		XmlParseHelperTable::XmlParseHelperTable() : mSharedData(nullptr)
		{

		}

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
			if (elementName == "scope")
			{
				// Return if there is no attribute name
				if (!attributeHashmap.ContainsKey("name"))
				{
					return false;
				}
				// In case a scope has to be appended
				if (!mSharedData->mScope)
				{
					mSharedData->mScope = new Scope();
				}
				else
				{
					Scope& appendedScope = mSharedData->mScope->AppendScope(attributeHashmap["name"]);
					mSharedData->mScope = &appendedScope;
				}
				return true;
			}
			return false;
		}
		
		bool XmlParseHelperTable::EndElementHandler(const std::string& elementName)
		{
			if (elementName == "scope")
			{
				Scope* parent = mSharedData->mScope->GetParent();
				if (parent)
				{
					mSharedData->mScope = parent;
				}
				return true;
			}
			return false;
		}

		void XmlParseHelperTable::CharDataHandler(const char* characterData, std::uint32_t size)
		{
			UNREFERENCED_PARAMETER(characterData);
			UNREFERENCED_PARAMETER(size);
		}

		IXmlParseHelper* XmlParseHelperTable::Clone()
		{
			XmlParseHelperTable* parseHelper = new XmlParseHelperTable();
			parseHelper->mSharedData = mSharedData;
			return parseHelper;
		}
	}
}