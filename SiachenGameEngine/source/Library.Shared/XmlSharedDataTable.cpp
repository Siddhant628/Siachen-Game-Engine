#include "XmlSharedDataTable.h"

using namespace SiachenGameEngine::Parsers;
using namespace SiachenGameEngine::GameplayFramework;

namespace SiachenGameEngine
{
	namespace Parsers
	{
		RTTI_DEFINITIONS(XmlSharedDataTable)

		XmlSharedDataTable::XmlSharedDataTable() : mScope(nullptr)
		{

		}

		XmlSharedDataTable::~XmlSharedDataTable()
		{
			delete mScope;
		}

		void XmlSharedDataTable::Initialize()
		{
			Parent::Initialize();
			delete mScope;
			mScope = nullptr;
		}

		XmlParseMaster::SharedData* XmlSharedDataTable::Clone()
		{
			XmlSharedDataTable* clonedSharedData = new XmlSharedDataTable();;
			if (mScope)
			{				
				clonedSharedData->mScope = new Scope(*mScope);
			}
			return clonedSharedData;
		}
	}
}