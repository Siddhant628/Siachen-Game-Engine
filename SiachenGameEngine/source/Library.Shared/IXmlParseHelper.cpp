#include "IXmlParseHelper.h"

namespace SiachenGameEngine
{
	namespace Parsers
	{
		IXmlParseHelper::IXmlParseHelper() : mSharedData(nullptr)
		{

		}

		void IXmlParseHelper::Initialize(XmlParseMaster::SharedData* sharedData)
		{
			mSharedData = sharedData;
		}
		XmlParseMaster::SharedData * IXmlParseHelper::GetSharedData() const
		{
			return mSharedData;
		}
	}
}