#include "pch.h"
#include "UnsubscribeAllSubscriber.h"
#include "Foo.h"
#include "Event.h"

namespace SiachenGameEngine
{
	namespace HelperClasses
	{
		UnsubscribeAllSubscriber::UnsubscribeAllSubscriber() : mInteger(0)
		{

		}

		void UnsubscribeAllSubscriber::Notify(const Events::EventPublisher& eventObject)
		{
			Events::Event<Foo>* object = eventObject.As<Events::Event<Foo>>();
			if (object)
			{
				Events::Event<Foo>::UnsubscribeAll();
				mInteger = object->Message().GetValue();
			}
		}
	}
}