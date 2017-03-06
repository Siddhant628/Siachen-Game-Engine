#include "pch.h"

#include "AttributedFoo.h"
#include "RTTI.h"

namespace SiachenGameEngine
{
	namespace HelperClasses
	{
		RTTI_DEFINITIONS(AttributedFoo)

		AttributedFoo::AttributedFoo()
		{
			Populate();
			UpdatePrescribedAttributeCache();
		}

		void AttributedFoo::Populate()
		{
			AddExternalAttribute("mInteger", &mInteger, 1U);
		}

		std::int32_t AttributedFoo::GetInteger()
		{
			return mInteger;
		}

		void AttributedFoo::SetInteger(std::int32_t value)
		{
			mInteger = value;
		}
	}
}
