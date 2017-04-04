#include "Action.h"

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
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