#include "pch.h"
#include "XmlParseHelperActionObjects.h"
#include "XmlSharedDataWorld.h"

#include "ActionList.h"
#include "ActionIf.h"
#include "ActionCreateAction.h"

#include "World.h"
#include "Entity.h"
#include "Sector.h"

using namespace SiachenGameEngine::Containers;
using namespace SiachenGameEngine::GameplayFramework;

namespace SiachenGameEngine
{
	namespace Parsers
	{
		XmlParseHelperActionObjects::XmlParseHelperActionObjects() : mSharedData(nullptr)
		{

		}

		void XmlParseHelperActionObjects::Initialize(XmlParseMaster::SharedData& sharedData)
		{
			mSharedData = sharedData.As<XmlSharedDataWorld>();
			if (!mSharedData)
			{
				throw std::runtime_error("Parser helper cannot use the provided type of shared data.");
			}
		}

		bool XmlParseHelperActionObjects::StartElementHandler(const std::string& elementName, const HashMap<std::string, std::string>& attributeHashmap)
		{
			if (elementName == "actioncreate")
			{
				assert(attributeHashmap.ContainsKey("name") && attributeHashmap.ContainsKey("class") && attributeHashmap.ContainsKey("instance"));
				Action* action = nullptr;
				if (mSharedData->mCurrentScope->Is(Entity::TypeIdClass()))
				{
					action = static_cast<Entity*>(mSharedData->mCurrentScope)->CreateAction("ActionCreateAction", attributeHashmap["name"]);
				}
				else if (mSharedData->mCurrentScope->Is(Sector::TypeIdClass()))
				{
					action = static_cast<Sector*>(mSharedData->mCurrentScope)->CreateAction("ActionCreateAction", attributeHashmap["name"]);
				}
				else if (mSharedData->mCurrentScope->Is(World::TypeIdClass()))
				{
					action = static_cast<World*>(mSharedData->mCurrentScope)->CreateAction("ActionCreateAction", attributeHashmap["name"]);
				}
				else if (mSharedData->mCurrentScope->Is(ActionList::TypeIdClass()))
				{
					action = static_cast<ActionList*>(mSharedData->mCurrentScope)->CreateAction("ActionCreateAction", attributeHashmap["name"]);
				}
				assert(action != nullptr);
				mSharedData->mCurrentScope = action;
				static_cast<ActionCreateAction*>(action)->Append("className").Set(attributeHashmap["class"]);
				static_cast<ActionCreateAction*>(action)->Append("instanceName").Set(attributeHashmap["instance"]);

				return true;
			}
			return false;
		}

		bool XmlParseHelperActionObjects::EndElementHandler(const std::string& elementName)
		{
			if (elementName == "actioncreate")
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

		void XmlParseHelperActionObjects::CharDataHandler(const char* characterData, std::uint32_t size)
		{
			UNREFERENCED_PARAMETER(characterData);
			UNREFERENCED_PARAMETER(size);
		}

		IXmlParseHelper* XmlParseHelperActionObjects::Clone()
		{
			XmlParseHelperActionObjects* parseHelper = new XmlParseHelperActionObjects();
			return parseHelper;
		}
	}
}
