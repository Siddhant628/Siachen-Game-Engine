#include "pch.h"
#include "FooSubscriber.h"
#include "Foo.h"
#include "Event.h"

namespace SiachenGameEngine
{
	namespace HelperClasses
	{
		FooSubscriber::FooSubscriber() : mInteger(0)
		{

		}

		void FooSubscriber::Notify(const Events::EventPublisher& eventObject)
		{
			Events::Event<Foo>* object = eventObject.As<Events::Event<Foo>>();
			if (object)
			{
				mInteger = object->Message().GetValue();
			}
		}
	}
}