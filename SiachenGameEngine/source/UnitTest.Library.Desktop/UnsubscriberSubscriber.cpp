#include "pch.h"
#include "UnsubscriberSubscriber.h"
#include "Foo.h"
#include "Event.h"

namespace SiachenGameEngine
{
	namespace HelperClasses
	{
		UnsubscriberSubscriber::UnsubscriberSubscriber() : mInteger(0)
		{

		}

		void UnsubscriberSubscriber::Notify(const Events::EventPublisher& eventObject)
		{
			Events::Event<Foo>* object = eventObject.As<Events::Event<Foo>>();
			if (object)
			{
				Events::Event<Foo>::Unsubscribe(*this);
				mInteger = object->Message().GetValue();
			}
		}
	}
}