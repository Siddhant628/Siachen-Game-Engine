#include "pch.h"
#include "SampleXmlSharedData.h"
#include "XmlParseMaster.h"

using namespace SiachenGameEngine::Parsers;

namespace SiachenGameEngine
{
	namespace HelperClasses
	{
		RTTI_DEFINITIONS(SampleXmlSharedData);
		
		void SampleXmlSharedData::Initialize()
		{
			XmlParseMaster::SharedData::Initialize();
			mStringPairVector.Clear();
		}
		
		Containers::Vector<std::pair<std::string, std::string>>& SampleXmlSharedData::GetStringPairVector()
		{
			return mStringPairVector;
		}
	}
}