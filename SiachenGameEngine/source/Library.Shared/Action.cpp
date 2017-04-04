#include "Action.h"

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
		RTTI_DEFINITIONS(Action)

		void Action::Populate()
		{
			AddExternalAttribute("name", &mActionName, 1U);
		}

		Action::Action()
		{
			Populate();
			UpdatePrescribedAttributeInfo();
		}

		const std::string& Action::Name() const
		{
			return mActionName;
		}

		void Action::SetName(const std::string& actionName)
		{
			mActionName = actionName;
		}
	}
}