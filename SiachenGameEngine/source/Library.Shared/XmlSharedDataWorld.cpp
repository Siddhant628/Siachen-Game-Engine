#include "pch.h"
#include "XmlSharedDataWorld.h"
#include "Attributed.h"

using namespace SiachenGameEngine::Parsers;
using namespace SiachenGameEngine::GameplayFramework;

namespace SiachenGameEngine
{
	namespace Parsers
	{
		RTTI_DEFINITIONS(XmlSharedDataWorld)

		XmlSharedDataWorld::XmlSharedDataWorld() : mCurrentScope(nullptr)
		{

		}

		XmlSharedDataWorld::~XmlSharedDataWorld()
		{
			delete mCurrentScope;
		}

		void XmlSharedDataWorld::Initialize()
		{
			Parent::Initialize();
			delete mCurrentScope;
			mCurrentScope = nullptr;
		}

		XmlParseMaster::SharedData* XmlSharedDataWorld::Clone()
		{
			XmlSharedDataWorld* clonedSharedData = new XmlSharedDataWorld();;
			return clonedSharedData;
		}
	}
}