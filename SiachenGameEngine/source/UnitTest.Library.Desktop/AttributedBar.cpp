#include "pch.h"

#include "AttributedBar.h"
#include "AttributedFoo.h"
#include "RTTI.h"

namespace SiachenGameEngine
{
	namespace HelperClasses
	{
		RTTI_DEFINITIONS(AttributedBar)

		AttributedBar::AttributedBar()
		{
			Populate();
			UpdatePrescribedAttributeInfo();
		}

		void AttributedBar::Populate()
		{
			AddExternalAttribute("mFloat", &mFloat, 1U);
		}

		std::float_t AttributedBar::GetFloat()
		{
			return mFloat;
		}

		void AttributedBar::SetFloat(std::float_t value)
		{
			mFloat = value;
		}
	}
}
