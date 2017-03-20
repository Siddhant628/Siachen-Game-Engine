#pragma once
#include "XmlParseMaster.h"
#include "Vector.h"

namespace SiachenGameEngine
{
	namespace HelperClasses
	{
		class SampleXmlSharedData final : public Parsers::XmlParseMaster::SharedData
		{
			RTTI_DECLARATIONS(SampleXmlSharedData, Parsers::XmlParseMaster::SharedData)
		public:
			SampleXmlSharedData() = default;

			~SampleXmlSharedData() = default;
			/**
			* Initializes the shared memory object for use/reuse.
			*/
			virtual void Initialize() override;

			Containers::Vector<std::pair<std::string, std::string>>& GetStringPairVector();
		private:
			Containers::Vector<std::pair<std::string,std::string>> mStringPairVector;
		};
	}
}