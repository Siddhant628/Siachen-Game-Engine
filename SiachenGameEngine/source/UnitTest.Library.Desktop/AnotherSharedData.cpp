#include "pch.h"
#include "AnotherSharedData.h"
#include "XmlParseMaster.h"

using namespace SiachenGameEngine::Parsers;

namespace SiachenGameEngine
{
	namespace HelperClasses
	{
		RTTI_DEFINITIONS(AnotherSharedData)
		void AnotherSharedData::Initialize()
		{
			XmlParseMaster::SharedData::Initialize();
		}

		XmlParseMaster::SharedData* AnotherSharedData::Clone()
		{
			return nullptr;
		}
	}
}