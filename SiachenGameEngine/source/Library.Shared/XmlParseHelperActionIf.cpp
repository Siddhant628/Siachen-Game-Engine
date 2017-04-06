#include "pch.h"
#include "XmlParseHelperActionIf.h"

#include "ActionList.h"
#include "ActionIf.h"

#include "World.h"
#include "Entity.h"
#include "Sector.h"

using namespace SiachenGameEngine::Containers;
using namespace SiachenGameEngine::GameplayFramework;

namespace SiachenGameEngine
{
	namespace Parsers
	{
		XmlParseHelperActionIf::XmlParseHelperActionIf() : mSharedData(nullptr)
		{

		}

		void XmlParseHelperActionIf::Initialize(XmlParseMaster::SharedData& sharedData)
		{
			mSharedData = sharedData.As<XmlSharedDataWorld>();
			if (!mSharedData)
			{
				throw std::runtime_error("Parser helper cannot use the provided type of shared data.");
			}
		}

		bool XmlParseHelperActionIf::StartElementHandler(const std::string& elementName, const HashMap<std::string, std::string>& attributeHashmap)
		{
			if (elementName == "if")
			{
				assert(attributeHashmap.ContainsKey("condition") && attributeHashmap.ContainsKey("name"));
				Action* action = nullptr;
				if (mSharedData->mCurrentScope->Is(Entity::TypeIdClass()))
				{
					action = static_cast<Entity*>(mSharedData->mCurrentScope)->CreateAction("ActionIf", attributeHashmap["name"]);
				}
				else if (mSharedData->mCurrentScope->Is(Sector::TypeIdClass()))
				{
					action = static_cast<Sector*>(mSharedData->mCurrentScope)->CreateAction("ActionIf", attributeHashmap["name"]);
				}
				else if (mSharedData->mCurrentScope->Is(World::TypeIdClass()))
				{
					action = static_cast<World*>(mSharedData->mCurrentScope)->CreateAction("ActionIf", attributeHashmap["name"]);
				}
				else if (mSharedData->mCurrentScope->Is(ActionList::TypeIdClass()))
				{
					action = static_cast<ActionList*>(mSharedData->mCurrentScope)->CreateAction("ActionIf", attributeHashmap["name"]);
				}
				assert(action != nullptr);
				static_cast<ActionIf*>(action)->Append("condition").Set(std::stoi(attributeHashmap["condition"]));

				mSharedData->mCurrentScope = action;
				return true;
			}
			else if (elementName == "then" || elementName == "else")
			{
				assert(attributeHashmap.ContainsKey("class") && attributeHashmap.ContainsKey("name"));
				assert(mSharedData->mCurrentScope->Is(ActionIf::TypeIdClass()));
				
				Action* action = static_cast<ActionIf*>(mSharedData->mCurrentScope)->CreateAction(attributeHashmap["class"], attributeHashmap["name"]);
				assert(action != nullptr);
				
				mSharedData->mCurrentScope = action;
				return true;
			}

			return false;
		}

		bool XmlParseHelperActionIf::EndElementHandler(const std::string& elementName)
		{
			if (elementName == "if" || elementName == "then" || elementName == "else")
			{
				Attributed* parent = static_cast<Attributed*>(mSharedData->mCurrentScope->GetParent());
				if (parent)
				{
					mSharedData->mCurrentScope = parent;
				}
				return true;
			}
			return false;
		}

		void XmlParseHelperActionIf::CharDataHandler(const char* characterData, std::uint32_t size)
		{
			UNREFERENCED_PARAMETER(characterData);
			UNREFERENCED_PARAMETER(size);
		}

		IXmlParseHelper* XmlParseHelperActionIf::Clone()
		{
			XmlParseHelperActionIf* parseHelper = new XmlParseHelperActionIf();
			return parseHelper;
		}
	}
}
