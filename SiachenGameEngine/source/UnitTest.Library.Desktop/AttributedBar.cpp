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
		}

		void AttributedBar::Populate()
		{
			AddExternalAttribute("mFloat", &mFloat, 1U);
			UpdatePrescribedAttributeCache();
		}
	}
}
