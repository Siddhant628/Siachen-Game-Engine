#include "pch.h"
#include "ActionEvent.h"
#include "EventMessageAttributed.h"
#include "Event.h"

using namespace SiachenGameEngine::Events;

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
		Action* ActionEvent::CreateAction(const std::string& className, const std::string& instanceName)
		{
			instanceName;
			className;
			return nullptr;
		}

		void ActionEvent::Populate()
		{
			AddExternalAttribute("subtype", &mSubtype, 1U);
			AddExternalAttribute("delay", &mDelay, 1U);
		}

		ActionEvent::ActionEvent()
		{
			Populate();
			UpdatePrescribedAttributeInfo();
		}

		void ActionEvent::Update(WorldState& worldState)
		{
			World& world = *worldState.mWorld;
			// Create the message object for the event.
			EventMessageAttributed message;
			message.SetSubtype(mSubtype);
			message.SetWorld(world);
			// Create and enqueue the event.
			Event<EventMessageAttributed>* event = new Event<EventMessageAttributed>(message, true);
			world.GetQueue().Enqueue(*event, worldState.mGameTime, std::chrono::milliseconds(mDelay));
			
		}
	}
}