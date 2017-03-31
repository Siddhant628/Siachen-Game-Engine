#include "pch.h"
#include "EntityFoo.h"

namespace SiachenGameEngine
{
	namespace HelperClasses
	{
		EntityFoo::EntityFoo()
		{
			Populate();
			UpdatePrescribedAttributeInfo();
		}

		void EntityFoo::Populate()
		{
			AddExternalAttribute("integer", &mInt, 1U);
			AddExternalAttribute("float", &mFloat, 1U);
		}
	}
}
