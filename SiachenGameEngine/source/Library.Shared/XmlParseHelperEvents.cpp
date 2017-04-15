#include "pch.h"
#include "XmlParseHelperEvents.h"

#include "ActionList.h"
#include "ActionEvent.h"
#include "Reaction.h"
#include "ReactionAttributed.h"

#include "World.h"
#include "Entity.h"
#include "Sector.h"

using namespace SiachenGameEngine::Containers;
using namespace SiachenGameEngine::GameplayFramework;

namespace SiachenGameEngine
{
	namespace Parsers
	{
		XmlParseHelperEvents::XmlParseHelperEvents() : mSharedData(nullptr)
		{

		}

		void XmlParseHelperEvents::Initialize(XmlParseMaster::SharedData& sharedData)
		{
			mSharedData = sharedData.As<XmlSharedDataWorld>();
			if (!mSharedData)
			{
				throw std::runtime_error("Parser helper cannot use the provided type of shared data.");
			}
		}

		bool XmlParseHelperEvents::StartElementHandler(const std::string& elementName, const Containers::HashMap<std::string, std::string>& attributeHashmap)
		{
			if (elementName == "actionevent")
			{
				assert(attributeHashmap.ContainsKey("name") && attributeHashmap.ContainsKey("subtype") && attributeHashmap.ContainsKey("delay"));
				
				ActionEvent* event = nullptr;
				event = static_cast<ActionEvent*>(GetActionObject("ActionEvent", attributeHashmap["name"]));
				assert(event != nullptr);
				mSharedData->mCurrentScope = event;

				event->Append("subtype").Set(attributeHashmap["subtype"]);
				event->Append("delay").Set(std::stoi(attributeHashmap["delay"]));
				return true;
			}
			else if (elementName == "reaction")
			{
				assert(attributeHashmap.ContainsKey("name") && attributeHashmap.ContainsKey("subtypes") && attributeHashmap.ContainsKey("class"));
				assert(mSharedData->mCurrentScope->Is(World::TypeIdClass()));
				
				Reaction* reaction = Factory<Reaction>::Create(attributeHashmap["class"]);
				mSharedData->mCurrentScope->Adopt(*reaction, attributeHashmap["name"]);
				mSharedData->mCurrentScope = reaction;
				
				reaction->Append("subtypes").PushBack(attributeHashmap["subtypes"]);
				reaction->SetName(attributeHashmap["name"]);
				return true;
			}
			return false;
		}

		bool XmlParseHelperEvents::EndElementHandler(const std::string& elementName)
		{
			if (elementName == "actionevent" || elementName == "reaction")
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

		void XmlParseHelperEvents::CharDataHandler(const char* characterData, std::uint32_t size)
		{
			UNREFERENCED_PARAMETER(characterData);
			UNREFERENCED_PARAMETER(size);
		}

		IXmlParseHelper* XmlParseHelperEvents::Clone()
		{
			XmlParseHelperEvents* parseHelper = new XmlParseHelperEvents();
			return parseHelper;
		}

		Action* XmlParseHelperEvents::GetActionObject(const std::string& className, const std::string& instanceName)
		{
			Action* action = nullptr;
			if (mSharedData->mCurrentScope->Is(Entity::TypeIdClass()))
			{
				action = static_cast<Entity*>(mSharedData->mCurrentScope)->CreateAction(className, instanceName);
			}
			else if (mSharedData->mCurrentScope->Is(Sector::TypeIdClass()))
			{
				action = static_cast<Sector*>(mSharedData->mCurrentScope)->CreateAction(className, instanceName);
			}
			else if (mSharedData->mCurrentScope->Is(World::TypeIdClass()))
			{
				action = static_cast<World*>(mSharedData->mCurrentScope)->CreateAction(className, instanceName);
			}
			else if (mSharedData->mCurrentScope->Is(ActionList::TypeIdClass()))
			{
				action = static_cast<ActionList*>(mSharedData->mCurrentScope)->CreateAction(className, instanceName);
			}
			return action;
		}
	}
}