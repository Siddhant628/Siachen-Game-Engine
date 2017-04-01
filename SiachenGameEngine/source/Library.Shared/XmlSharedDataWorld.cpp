#include "XmlSharedDataWorld.h"
#include "World.h"
#include "Sector.h"
#include "Entity.h"

using namespace SiachenGameEngine::Parsers;
using namespace SiachenGameEngine::GameplayFramework;

namespace SiachenGameEngine
{
	namespace Parsers
	{
		RTTI_DEFINITIONS(XmlSharedDataWorld)

		XmlSharedDataWorld::XmlSharedDataWorld() : mCurrentWorld(nullptr), mCurrentSector(nullptr), mCurrentEntity(nullptr)
		{

		}

		XmlSharedDataWorld::~XmlSharedDataWorld()
		{
			delete mCurrentWorld;
		}

		void XmlSharedDataWorld::Initialize()
		{
			Parent::Initialize();
			delete mCurrentWorld;
			mCurrentWorld = nullptr;
		}

		XmlParseMaster::SharedData* XmlSharedDataWorld::Clone()
		{
			XmlSharedDataWorld* clonedSharedData = new XmlSharedDataWorld();;
			return clonedSharedData;
		}
	}
}