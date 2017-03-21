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

			void SetCurrentElement(const std::string& elementName);

			const std::string& GetCurrentElement() const;

			Containers::Vector<std::pair<std::string, std::string>>& GetStringPairVector();
		private:
			Containers::Vector<std::pair<std::string,std::string>> mStringPairVector;

			std::string mCurrentElement;
		};
	}
}