#include "pch.h"
#include "ActionEvent.h"
#include "EventMessageAttributed.h"
#include "Event.h"
#include "Vector.h"

using namespace SiachenGameEngine::Events;
using namespace SiachenGameEngine::Containers;

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
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
			worldState.mAction = this;

			World& world = *worldState.mWorld;
			// Create the message object for the event
			EventMessageAttributed attributedMessage;
			attributedMessage.SetSubtype(mSubtype);
			attributedMessage.SetWorld(world);
			// Copy over the auxiliary attributes
			Vector<std::string> keys;
			GetKeys(keys);

			Vector<std::string>::Iterator end = keys.end();
			for (Vector<std::string>::Iterator it = keys.begin(); it != end; ++it)
			{
				std::string key = *it;
				if (IsAuxiliaryAttribute(key))
				{
					Datum* source = Find(key);
					Datum& destination = attributedMessage.Append(key);

					if (source->Type() != DatumType::TableType)
					{
						destination = *source;
					}
				}
			}
			// Create and enqueue the event
			Event<EventMessageAttributed>* event = new Event<EventMessageAttributed>(attributedMessage, true);
			world.GetQueue().Enqueue(*event, worldState.mGameTime, std::chrono::milliseconds(mDelay));
		
			worldState.mAction = GetParent()->As<Action>();
		}

		RTTI_DEFINITIONS(ActionEvent)
	}
}