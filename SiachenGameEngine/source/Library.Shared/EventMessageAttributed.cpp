#include "pch.h"
#include "EventMessageAttributed.h"

namespace SiachenGameEngine
{
	namespace Events
	{
		void EventMessageAttributed::Populate()
		{
			AddExternalAttribute("subtype", &mSubtype, 1U);
		}

		EventMessageAttributed::EventMessageAttributed()
		{
			Populate();
			UpdatePrescribedAttributeInfo();
		}

		void EventMessageAttributed::SetSubtype(const std::string& subtype)
		{
			mSubtype = subtype;
		}
		
		const std::string& EventMessageAttributed::GetSubtype() const
		{
			return mSubtype;
		}

		void EventMessageAttributed::SetWorld(const GameplayFramework::World& world)
		{
			mWorld = &world;
		}

		const GameplayFramework::World& EventMessageAttributed::GetWorld() const
		{
			return *mWorld;
		}
	
		RTTI_DEFINITIONS(EventMessageAttributed)
	}
}