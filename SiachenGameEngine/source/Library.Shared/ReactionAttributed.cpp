#include "pch.h"
#include "ReactionAttributed.h"

#include "Event.h"
#include "EventMessageAttributed.h"

using namespace SiachenGameEngine::Containers;
using namespace SiachenGameEngine::Events;

namespace SiachenGameEngine
{
	namespace GameplayFramework
	{
		const std::string ReactionAttributed::sSubtypes = "subtypes";

		bool ReactionAttributed::SubtypeCheck(const Events::EventPublisher& eventObject)
		{
			const Event<EventMessageAttributed>* event = static_cast<const Event<EventMessageAttributed>*>(&eventObject);
			Containers::Datum& datum = Append(sSubtypes);
			std::uint32_t size = datum.Size();

			for (std::uint32_t it = 0; it < size; ++it)
			{
				if (datum.Get<std::string>(it) == event->Message().GetSubtype())
				{
					return true;
				}
			}
			return false;
		}

		void ReactionAttributed::Populate()
		{
			mSubtypes = &AddInternalAttribute(sSubtypes, DatumType::StringType);
		}

		ReactionAttributed::ReactionAttributed()
		{
			Populate();
			UpdatePrescribedAttributeInfo();
			Event<EventMessageAttributed>::Subscribe(*this);
		}

		ReactionAttributed::~ReactionAttributed()
		{
			Event<EventMessageAttributed>::Unsubscribe(*this);
		}

		void ReactionAttributed::Notify(const Events::EventPublisher& eventObject)
		{
			assert(eventObject.Is(Event<EventMessageAttributed>::TypeIdClass()));
			const Event<EventMessageAttributed>* event = static_cast<const Event<EventMessageAttributed>*>(&eventObject);
			if (SubtypeCheck(*event))
			{
				const EventMessageAttributed attributedMessage = event->Message();

				Vector<std::string> keys;
				attributedMessage.GetKeys(keys);

				Vector<std::string>::Iterator end = keys.end();
				for (Vector<std::string>::Iterator it = keys.begin(); it != end; ++it)
				{
					std::string key = *it;
					// Copy over the attribute if it is an auxiliary attribute.
					if (attributedMessage.IsAuxiliaryAttribute(key))
					{
						Datum* source = attributedMessage.Find(key);
						Datum& destination = Append(key);

						if (source->Type() != DatumType::TableType)
						{
							destination = *source;
						}
						else
						{
							// Call destructors on all the scopes.
							// Create copies of all the scopes and push them into this datum.
						}
					}
				}
				//Update(attributedMessage.GetWorld().);
			}
		}

		RTTI_DEFINITIONS(ReactionAttributed)
	}
}