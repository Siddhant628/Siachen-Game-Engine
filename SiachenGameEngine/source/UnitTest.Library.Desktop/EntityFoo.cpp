#include "pch.h"
#include "EntityFoo.h"
#include "WorldState.h"

namespace SiachenGameEngine
{
	namespace HelperClasses
	{
		RTTI_DEFINITIONS(EntityFoo)
		EntityFoo::EntityFoo() : mInt(0), mFloat(0.0f), mString()
		{
			Populate();
			UpdatePrescribedAttributeInfo();
		}

		void EntityFoo::Populate()
		{
			AddExternalAttribute("integer", &mInt, 1U);
			AddExternalAttribute("float", &mFloat, 1U);
			AddExternalAttribute("string", &mString, 1U);
			AddExternalAttribute("vector", &mVector, 1U);
			AddExternalAttribute("matrix", &mMatrix, 1U);
		}

		void EntityFoo::Update(GameplayFramework::WorldState& worldState)
		{
			Entity::Update(worldState);
		}
	}
}
