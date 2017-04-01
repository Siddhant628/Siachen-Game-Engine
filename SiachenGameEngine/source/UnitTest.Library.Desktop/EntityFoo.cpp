#include "pch.h"
#include "EntityFoo.h"

namespace SiachenGameEngine
{
	namespace HelperClasses
	{
		RTTI_DEFINITIONS(EntityFoo)
		EntityFoo::EntityFoo() : mInt(0), mFloat(0.0f)
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
