#include "pch.h"
#include "EnqueueSubscriber.h"
#include "Foo.h"
#include "Event.h"
#include "GameTime.h"

#include <chrono>

namespace SiachenGameEngine
{
	namespace HelperClasses
	{
		EnqueueSubscriber::EnqueueSubscriber(Events::EventQueue& eventQueue, Library::GameTime& gameTime) : mInteger(0), mEventQueue(&eventQueue), mGameTime(&gameTime)
		{

		}

		void EnqueueSubscriber::Notify(const Events::EventPublisher& eventObject)
		{
			Events::Event<Foo>* object = eventObject.As<Events::Event<Foo>>();
			if (object)
			{
				Library::GameTime time;
				Events::Event<Foo>* fooEvent = new Events::Event<Foo>(Foo(1000), true);
				mEventQueue->Enqueue(*fooEvent, *mGameTime, std::chrono::milliseconds(0));
				mInteger = object->Message().GetValue();
			}
		}
	}
}