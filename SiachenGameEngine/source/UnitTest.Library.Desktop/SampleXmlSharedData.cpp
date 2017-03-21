#include "pch.h"
#include "SampleXmlSharedData.h"
#include "XmlParseMaster.h"

using namespace SiachenGameEngine::Parsers;

namespace SiachenGameEngine
{
	namespace HelperClasses
	{
		RTTI_DEFINITIONS(SampleXmlSharedData);

		SampleXmlSharedData::SampleXmlSharedData()
		{

		}
		
		void SampleXmlSharedData::Initialize()
		{
			XmlParseMaster::SharedData::Initialize();
			mStringPairVector.Clear();
			mCurrentElement = "";
		}

		XmlParseMaster::SharedData* SampleXmlSharedData::Clone()
		{
			SampleXmlSharedData* sharedDataClone = new SampleXmlSharedData();
			// Clone the state
			sharedDataClone->mStringPairVector = mStringPairVector;
			sharedDataClone->mCurrentElement = mCurrentElement;
			while (sharedDataClone->Depth() != Depth())
			{
				sharedDataClone->IncrementDepth();
			}
			sharedDataClone->SetXmlParseMaster(*GetXmlParseMaster());

			return sharedDataClone;
		}

		void SampleXmlSharedData::SetCurrentElement(const std::string& elementName)
		{
			mCurrentElement = elementName;
		}
		
		const std::string & SampleXmlSharedData::GetCurrentElement() const
		{
			return mCurrentElement;
		}

		Containers::Vector<std::pair<std::string, std::string>>& SampleXmlSharedData::GetStringPairVector()
		{
			return mStringPairVector;
		}
	}
}