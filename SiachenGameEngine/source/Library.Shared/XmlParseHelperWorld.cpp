#include "pch.h"
#include "XmlParseHelperWorld.h"
#include <string>
#include "World.h"

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
				if (attributeHashmap.ContainsKey("name"))
				{
					World* world = new World(attributeHashmap["name"]);
					mSharedData->mCurrentScope = world;
					return true;
				}
			}
			else if (elementName == "sector")
			{
				assert(mSharedData->mCurrentScope->Is(World::TypeIdClass()));
				if (attributeHashmap.ContainsKey("name"))
				{
					Sector* sector = static_cast<World*>(mSharedData->mCurrentScope)->CreateSector(attributeHashmap["name"]);
					assert(sector != nullptr);
					mSharedData->mCurrentScope = sector;
					return true;
				}
			}
			else if (elementName == "entity")
			{
				assert(mSharedData->mCurrentScope->Is(Sector::TypeIdClass()));
				if (attributeHashmap.ContainsKey("name") && attributeHashmap.ContainsKey("class"))
				{
					Entity* entity = static_cast<Sector*>(mSharedData->mCurrentScope)->CreateEntity(attributeHashmap["class"], attributeHashmap["name"]);
					assert(entity != nullptr);
					mSharedData->mCurrentScope = entity;
					return true;
				}
			}
			return false;
		}

		bool XmlParseHelperWorld::EndElementHandler(const std::string& elementName)
		{
			if (elementName == "entity" || elementName == "sector" || elementName == "world")
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
