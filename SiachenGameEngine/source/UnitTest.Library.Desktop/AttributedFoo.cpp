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
			UpdatePrescribedAttributeInfo();
		}

		void AttributedFoo::Populate()
		{
			AddExternalAttribute("mInteger", &mInteger, 1U);
		}

		std::int32_t AttributedFoo::GetInteger() const
		{
			return mInteger;
		}

		void AttributedFoo::SetInteger(std::int32_t value)
		{
			mInteger = value;
		}
	}
}
