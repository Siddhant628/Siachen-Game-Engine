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

		// TODO Confirm
		XmlParseMaster::SharedData* SampleXmlSharedData::Clone()
		{
			SampleXmlSharedData* sharedDataClone = new SampleXmlSharedData();
			// TODO Should data be cloned
			sharedDataClone->mStringPairVector = mStringPairVector;
			sharedDataClone->mCurrentElement = mCurrentElement;
			// TODO Set mParseMaster and Depth values
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