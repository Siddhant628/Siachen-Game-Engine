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

		void XmlSharedDataTable::Initialize()
		{
			// TODO Check
			Parent::Initialize();
			delete mScope;
			mScope = nullptr;
		}

		XmlParseMaster::SharedData* XmlSharedDataTable::Clone()
		{
			return nullptr;
		}
	}
}