#include "pch.h"
#include "ActionFoo.h"
#include <Windows.h>

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

			char str[10];
			sprintf_s(str, "%s", mString.c_str());
			OutputDebugString(str);
			
			worldState.mAction = GetParent()->As<Action>();
		}
	}
}