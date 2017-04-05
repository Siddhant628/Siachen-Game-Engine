#include "pch.h"
#include "ActionFoo.h"

namespace SiachenGameEngine
{
	namespace HelperClasses
	{
		RTTI_DEFINITIONS(ActionFoo)

		void ActionFoo::Populate()
		{
			AddExternalAttribute("String", &mString, 1U);
		}

		ActionFoo::ActionFoo()
		{
			Populate();
			UpdatePrescribedAttributeInfo();
		}

		void ActionFoo::Update(GameplayFramework::WorldState& worldState)
		{
			worldState.mAction = this;
			OutputDebugString((LPCWSTR)mString.c_str());
			worldState.mAction = GetParent()->As<Action>();
		}
	}
}