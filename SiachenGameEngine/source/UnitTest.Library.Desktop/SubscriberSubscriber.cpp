#include "pch.h"
#include "SubscriberSubscriber.h"
#include "Foo.h"
#include "Event.h"
#include "FooSubscriber.h"

namespace SiachenGameEngine
{
	namespace HelperClasses
	{
		SubscriberSubscriber::SubscriberSubscriber() : mInteger(0), fooSub(nullptr)
		{

		}

		SubscriberSubscriber::~SubscriberSubscriber()
		{
			delete fooSub;
		}

		void SubscriberSubscriber::Notify(const Events::EventPublisher& eventObject)
		{
			Events::Event<Foo>* object = eventObject.As<Events::Event<Foo>>();
			if (object)
			{
				fooSub = new FooSubscriber();
				Events::Event<Foo>::Subscribe(*fooSub);
				mInteger = object->Message().GetValue();
			}
		}
	}
}