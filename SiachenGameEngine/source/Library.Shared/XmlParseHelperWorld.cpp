#include "pch.h"
#include "XmlParseHelperWorld.h"
#include "World.h"
#include "ActionList.h"
#include <string>

using namespace SiachenGameEngine::Containers;
using namespace SiachenGameEngine::GameplayFramework;


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
				assert(mSharedData->mCurrentScope == nullptr);
				assert(attributeHashmap.ContainsKey("name"));

				World* world = new World(attributeHashmap["name"]);
				mSharedData->mCurrentScope = world;
				return true;

			}
			else if (elementName == "sector")
			{
				assert(mSharedData->mCurrentScope->Is(World::TypeIdClass()));
				assert(attributeHashmap.ContainsKey("name"));

				Sector* sector = static_cast<World*>(mSharedData->mCurrentScope)->CreateSector(attributeHashmap["name"]);
				assert(sector != nullptr);
				mSharedData->mCurrentScope = sector;
				return true;
			}
			else if (elementName == "entity")
			{
				assert(mSharedData->mCurrentScope->Is(Sector::TypeIdClass()));
				assert(attributeHashmap.ContainsKey("name") && attributeHashmap.ContainsKey("class"));

				Entity* entity = static_cast<Sector*>(mSharedData->mCurrentScope)->CreateEntity(attributeHashmap["class"], attributeHashmap["name"]);
				assert(entity != nullptr);
				mSharedData->mCurrentScope = entity;
				return true;
			}

			else if (elementName == "action")
			{
				assert(attributeHashmap.ContainsKey("name") && attributeHashmap.ContainsKey("class"));
				Action* action = nullptr;
				if (mSharedData->mCurrentScope->Is(Entity::TypeIdClass()))
				{
					action = static_cast<Entity*>(mSharedData->mCurrentScope)->CreateAction(attributeHashmap["class"], attributeHashmap["name"]);
				}
				else if (mSharedData->mCurrentScope->Is(Sector::TypeIdClass()))
				{
					action = static_cast<Sector*>(mSharedData->mCurrentScope)->CreateAction(attributeHashmap["class"], attributeHashmap["name"]);
				}
				else if (mSharedData->mCurrentScope->Is(World::TypeIdClass()))
				{
					action = static_cast<World*>(mSharedData->mCurrentScope)->CreateAction(attributeHashmap["class"], attributeHashmap["name"]);
				}
				else if (mSharedData->mCurrentScope->Is(ActionList::TypeIdClass()))
				{
					action = static_cast<ActionList*>(mSharedData->mCurrentScope)->CreateAction(attributeHashmap["class"], attributeHashmap["name"]);
				}
				mSharedData->mCurrentScope = action;
				return true;
			}

			return false;
		}

		bool XmlParseHelperWorld::EndElementHandler(const std::string& elementName)
		{
			if (elementName == "entity" || elementName == "sector" || elementName == "world" || elementName == "action")
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
