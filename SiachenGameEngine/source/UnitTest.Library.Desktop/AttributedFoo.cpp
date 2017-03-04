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
			SetPrescribedAttributesAssigned();
		}

		void AttributedFoo::Populate()
		{
			Parent::Populate();
			AddInternalAttribute("this", static_cast<RTTI*>(this), true);
			AddExternalAttribute("mInteger", &mInteger, 1U, true);
		}
	}
}
