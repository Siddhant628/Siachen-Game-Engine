#include "pch.h"
#include "QueueClearSubscriber.h"
#include "Foo.h"
#include "Event.h"
#include "GameTime.h"

#include <chrono>

namespace SiachenGameEngine
{
	namespace HelperClasses
	{
		QueueClearSubscriber::QueueClearSubscriber(Events::EventQueue& eventQueue) : mInteger(0), mEventQueue(&eventQueue)
		{

		}

		void QueueClearSubscriber::Notify(const Events::EventPublisher& eventObject)
		{
			Events::Event<Foo>* object = eventObject.As<Events::Event<Foo>>();
			if (object)
			{
				mEventQueue->Clear();
				mInteger = object->Message().GetValue();
			}
		}
	}
}