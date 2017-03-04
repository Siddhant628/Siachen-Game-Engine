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
			// TODO Confirm if I can populate here 
			Parent::Populate();
			AddExternalAttribute("mInteger", &mInteger, 1U, true);
		}
	}
}
